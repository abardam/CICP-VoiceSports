#include "stdafx.h"
#include "asr.h"
#include <WS2tcpip.h>

void voicesport::SpeechKit::Speechkit()
{

}

bool voicesport::SpeechKit::connectServer()
{
	WSADATA wsadata;
	int error = WSAStartup(0x0202, &wsadata);
	if (error) {
		return false;
	}
	if (wsadata.wVersion != 0x0202) {
		WSACleanup(); //Clean up Winsock
		return false;
	}

	SOCKADDR_IN target;
	target.sin_family = AF_INET;
	target.sin_port = htons(server_port);
	target.sin_addr.s_addr = inet_addr(server_host.c_str()); //<-- deprecated
	//inet_pton(AF_INET, server_host.c_str(), &target.sin_addr.s_addr);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET) {
		return false;
	}
	if (connect(sock, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR) {
		closesocket(sock);
		return false;
	}
	else
		return true;

}

void voicesport::SpeechKit::setLanguage(std::string lang)
{
	language = lang;
}

void voicesport::SpeechKit::recevingData() {
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	// Receive data until the server closes the connection
	do {
		if (is_stop)
			break;
		try
		{
			iResult = recv(sock, recvbuf, recvbuflen, 0);
		}
		catch (const std::exception&)
		{
			break;
		}

		recvbuf[iResult] = 0;
		std::string text(recvbuf);
		if (iResult > 0) {
			if (onFinalResult)
				onFinalResult(text);
			if (onFinalResultCtx)
				onFinalResultCtx(text, ctx);
		}
		else if (iResult == 0) {
			//Connection closed\n
			if (onError)
				onError(0);
			if (onErrorCtx)
				onErrorCtx(0, ctx);
		}
		else {
			//printf("recv failed: %d\n", WSAGetLastError());
			if (onError)
				onError(1);
			if (onErrorCtx)
				onErrorCtx(1, ctx);
		}
	} while (iResult > 0);
}

bool voicesport::SpeechKit::startASR()
{
	is_stop = false;
	if (sock){
		int result = send(sock, "start", 5, 0);
		return true;
	}
	else
		connectServer();
	
	int result = send(sock, "start", 5, 0);
	if (result == SOCKET_ERROR) {
		return false;
	}
	else {
		std::thread runThread(&voicesport::SpeechKit::recevingData, this);
		runThread.detach();
		return true;
	}

}

void voicesport::SpeechKit::setCtx(CWnd * ctx)
{
	this->ctx = ctx;
}

void voicesport::SpeechKit::stopASR()
{
	//is_stop = true;
	if (sock) {
		int result = send(sock, "stop", 5, 0);
		//closesocket(sock);
	}
	//if (sock) {
	//	closesocket(sock);
	//	WSACleanup();
	//}
		
}

void voicesport::SpeechKit::connectOnFinalResult(const CBFunctor1<std::string>& listener)
{
	onFinalResult = listener;
}

void voicesport::SpeechKit::connectOnPartialResult(const CBFunctor1<std::string>& listener)
{
	onPartialResult = listener;
}

void voicesport::SpeechKit::connectOnError(const CBFunctor1<int>& listener)
{
	onError = listener;
}


void voicesport::SpeechKit::connectOnFinalResult(const CBFunctor2<std::string, CWnd* >& listener)
{
	onFinalResultCtx = listener;
}

void voicesport::SpeechKit::connectOnPartialResult(const CBFunctor2<std::string, CWnd* >& listener)
{
	onPartialResultCtx = listener;
}

void voicesport::SpeechKit::connectOnError(const CBFunctor2<int, CWnd* >& listener)
{
	onErrorCtx = listener;
}
