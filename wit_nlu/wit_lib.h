/*
* wit_lib.h
* Copyright (C) 2016 truong-d <truong-d@truongd-ThinkPad-X1-Carbon-3rd>
*
* Distributed under terms of the MIT license.
*/

#ifndef WIT_LIB_H
#define WIT_LIB_H
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include "../CICP-ActionTemplates/UtilsHAR.h"

class WitLib {

private:
	CURL * curl;
	CURLcode code;
	std::string buffer;
	std::string BASE_URL;
	struct curl_slist * headers;
public:
	WitLib();
	std::string analyze(std::string text);
	std::string requestWitAi(std::string text);
	std::string extractInformation(size_t p, std::string key, std::string mark, std::string& text);
	fbskeleton getJoints(std::string text);
};

#endif /* !WIT_LIB_H */
