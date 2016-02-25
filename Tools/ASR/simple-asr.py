import logging
import sys
import SocketServer
import json
import re
from speech_lib.speechkit import SpeechKit
import asr_google

logging.basicConfig(level=logging.DEBUG,
                    format='%(name)s: %(message)s',
                    )

import httplib, urllib
conn = httplib.HTTPConnection("ahclab08", 8000)
headers = {"Content-type": "application/x-www-form-urlencoded", "Accept": "text/plain"}

google_asr = asr_google.SpeechRecognition()

class EchoRequestHandler(SocketServer.BaseRequestHandler):

    def __init__(self, request, client_address, server):
        self.logger = logging.getLogger('EchoRequestHandler')
        self.logger.debug('__init__')
        SocketServer.BaseRequestHandler.__init__(self, request, client_address, server)
        return

    def setup(self):
        self.speech_kit = None
        self.trans = []
        self.clean = re.compile("<UNK>\.|<unk>\.|<unk>|<UNK>|power.*")

        self.logger.debug('setup')
        return SocketServer.BaseRequestHandler.setup(self)

    def handle(self):
        self.logger.debug('handle')

        # Echo the back to the client
        while 1:
            data = None
            try:
                data = self.request.recv(1024)
            except:
                self.logger.debug("Client left. Closing")
                self.speech_kit.stop()
                while not self.speech_kit.is_stop:
                    time.sleep(1)
                return

            self.logger.info('recv()->' +  data)
            if data == "start":

                # Using our own asr
                self.speech_kit = SpeechKit.initialize(ip="ws://ahcclp01:11507/",
                                      lang="en_tedtalk", listener=self, fullurl=None)
                if not self.speech_kit:
                    print "Error, cannot initialize"
                    self.sendall("fail")
                    return
                self.speech_kit.connect()
                self.speech_kit.start()

                # Using Google ASR
                result = google_asr.recognize()
                self.on_final(result)
            else:
                self.logger.info("Stop ASR")
                self.speech_kit.stop()
                while not self.speech_kit.is_stop:
                    time.sleep(1)
                # self.sendall("server:stopped")


                # return

    def on_partial(self, text):
        text = self.clean.sub("", text)
        if text:
            print " ".join(self.trans) + " " + text.lower()

    def on_final(self, text):
        # text = self.clean.sub("", text).lower().replace(".", "").replace(" ", "%20")
        text = self.clean.sub("", text)
        params = urllib.urlencode({'text': text})
        conn.request("POST", "/KanjiConverter/default/convert", params, headers)
        response = conn.getresponse()
        text = response.read()
        print "final: ", text
        try:
            self.request.sendall(text)
        except:
            self.speech_kit.stop()

            #print " ".join(self.trans).upper()

    def finish(self):
        self.logger.debug('finish')
        return SocketServer.BaseRequestHandler.finish(self)


class EchoServer(SocketServer.TCPServer):

    def __init__(self, server_address, handler_class=EchoRequestHandler):
        self.logger = logging.getLogger('EchoServer')
        self.logger.debug('__init__')
        SocketServer.TCPServer.__init__(self, server_address, handler_class)
        return

    def server_activate(self):
        self.logger.debug('server_activate')
        SocketServer.TCPServer.server_activate(self)
        return

    def serve_forever(self):
        self.logger.debug('waiting for request')
        self.logger.info('Handling requests, press <Ctrl-C> to quit')
        while True:
            self.handle_request()
        return

    def handle_request(self):
        self.logger.debug('handle_request')
        return SocketServer.TCPServer.handle_request(self)

    def verify_request(self, request, client_address):
        self.logger.debug('verify_request(%s, %s)', request, client_address)
        return SocketServer.TCPServer.verify_request(self, request, client_address)

    def process_request(self, request, client_address):
        self.logger.debug('process_request(%s, %s)', request, client_address)
        return SocketServer.TCPServer.process_request(self, request, client_address)

    def server_close(self):
        self.logger.debug('server_close')
        return SocketServer.TCPServer.server_close(self)

    def finish_request(self, request, client_address):
        self.logger.debug('finish_request(%s, %s)', request, client_address)
        return SocketServer.TCPServer.finish_request(self, request, client_address)

    def close_request(self, request_address):
        self.logger.debug('close_request(%s)', request_address)
        return SocketServer.TCPServer.close_request(self, request_address)


if __name__ == '__main__':
    import socket
    import threading

    address = ('0.0.0.0', 8888) # let the kernel give us a port
    server = EchoServer(address, EchoRequestHandler)
    ip, port = server.server_address # find out what port we were given
    print "Serving on " + ip + " " + str(port)
    server.serve_forever()
    #t = threading.Thread(target=server.serve_forever)
    #t.setDaemon(True) # don't hang on exit
    #t.start()
