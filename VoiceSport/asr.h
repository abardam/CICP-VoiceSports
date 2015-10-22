#pragma once
#define _AFXDLL
#include "string"
#include "functional"
#include "callback.h"
#include <winsock.h>
#include <assert.h>
#include <stdio.h>
#include <thread>         // std::thread
#include <string>
#include <memory>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024

namespace voicesport {
	class SpeechKit {
	public:
		void Speechkit();
		bool connectServer();
		void setLanguage(std::string lang);
		bool startASR();
		void setCtx(CWnd* ctx);
		void stopASR();
		void recevingData();  // Receving data from socket
		void connectOnFinalResult(const CBFunctor1<std::string> &listener);
		void connectOnPartialResult(const CBFunctor1<std::string> &listener);
		void connectOnError(const CBFunctor1<int> &listener);

		void connectOnFinalResult(const CBFunctor2<std::string, CWnd* > &listener);
		void connectOnPartialResult(const CBFunctor2<std::string, CWnd* > &listener);
		void connectOnError(const CBFunctor2<int, CWnd * > &listener);
	private:
		CWnd* ctx = NULL;
		CBFunctor1<std::string> onFinalResult = NULL;
		CBFunctor1<int> onError = NULL;
		CBFunctor1<std::string> onPartialResult = NULL;

		CBFunctor2<std::string, CWnd* > onFinalResultCtx = NULL;
		CBFunctor2<int, CWnd* > onErrorCtx = NULL;
		CBFunctor2<std::string, CWnd* > onPartialResultCtx = NULL;
		
		SOCKET sock;

		// Server information
		std::string language = "en";
		std::string server_host = "127.0.0.1";

		bool is_stop = false;
		int server_port = 8888;
	};
}