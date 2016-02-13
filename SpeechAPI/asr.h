#ifndef ASR_H
#define ASR_H

#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_
#pragma once
#include <assert.h>
#include <stdio.h>
#include <thread>         // std::thread
#include <memory>
#include "callback.h"
#include <string>
#include <functional>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define DEFAULT_BUFLEN 1024

namespace voicesport {
	class SpeechKit {
	public:
		void Speechkit();
		bool connectServer();
		void setLanguage(std::string lang);
		bool startASR();
		void stopASR();
		void recevingData();  // Receving data from socket
		void connectOnFinalResult(const CBFunctor1<std::string> &listener);
		void connectOnPartialResult(const CBFunctor1<std::string> &listener);
		void connectOnError(const CBFunctor1<int> &listener);

	private:
		CBFunctor1<std::string> onFinalResult = NULL;
		CBFunctor1<int> onError = NULL;
		CBFunctor1<std::string> onPartialResult = NULL;

		CBFunctor1<std::string> onFinalResultCtx = NULL;
		CBFunctor1<int> onErrorCtx = NULL;
		CBFunctor1<std::string> onPartialResultCtx = NULL;

		SOCKET sock;

		// Server information
		std::string language = "en";
		std::string server_host = "127.0.0.1";

		bool is_stop = false;
		int server_port = 8888;
	};
}
#endif