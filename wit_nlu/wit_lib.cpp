/*
* wit_lib.cpp
* Copyright (C) 2016 truong-d <truong-d@truongd-ThinkPad-X1-Carbon-3rd>
*
* Distributed under terms of the MIT license.
*/

#include "stdafx.h"
#include "wit_lib.h"

static int writer(char *data, size_t size, size_t nmemb,
	std::string *writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);
	return size * nmemb;
}


std::string url_encode(std::string text) {
	return text;
}

WitLib::WitLib() {
	BASE_URL = "https://api.wit.ai/message?v=20160203&q=";
	curl_global_init(CURL_GLOBAL_DEFAULT);
	//std::string authentication = "4RRCPZH2XV3IXQSJPSHYSNRETMZORZIP";
	//char* contenttype = (char*)malloc(23 + authentication.length());
	//sprintf(contenttype, "Authorization: Bearer %s", authentication.c_str());

	char* contenttype = "Authorization: Bearer 4RRCPZH2XV3IXQSJPSHYSNRETMZORZIP";
	headers = curl_slist_append(headers, contenttype);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	}
}

std::string WitLib::requestWitAi(std::string text) {
	std::string request_url = BASE_URL + url_encode(text);
	curl_easy_setopt(curl, CURLOPT_URL, request_url.c_str());

	/* Perform the request, res will get the return code */
	code = curl_easy_perform(curl);
	/* Check for errors */ 
	if (code != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(code));
	return buffer;
	/* always cleanup */
	curl_easy_cleanup(curl);
}

std::string WitLib::extractInformation(size_t p, std::string key, std::string mark, std::string& text)
{
	std::string s = "\"" + key + "\"";
	auto p1 = text.find(s);
	if (std::string::npos != p1)
		p1 += s.size();
	auto p2 = text.find_first_of(mark, p1);
	if (std::string::npos != p2)
		return text.substr(p1, p2 - p1);
	return "";
}

std::string WitLib::analyze(std::string text) {
	std::string output = requestWitAi(text);
	return output;
}

fbskeleton WitLib::getJoints(std::string text) {
	std::string skel = requestWitAi(text);

	// get the entities from the string
	// body_parts = {arms, legs, posture}
	std::string body_part = WitLib::extractInformation(0, "body_parts", "]", skel);
	std::string body = WitLib::extractInformation(0, " : ", "\"", body_part);

	// position = {left, right, both}
	std::string position = WitLib::extractInformation(0, "position", "]", skel);
	std::string pos = WitLib::extractInformation(0, " : ", "\"", position);

	// based on body and pos, activate the joints
	fbskeleton sk;
	if (body == "arms") {
		if (pos == "left")
		{
			sk.needsCheck[LSHOULDER] = true;
			sk.needsCheck[LELBOW] = true;
			sk.needsCheck[LHAND] = true;
		}
		else if (pos == "right") {
			sk.needsCheck[RSHOULDER] = true;
			sk.needsCheck[RELBOW] = true;
			sk.needsCheck[RHAND] = true;
		}
		else {
			sk.needsCheck[LSHOULDER] = true;
			sk.needsCheck[LELBOW] = true;
			sk.needsCheck[LHAND] = true;
			sk.needsCheck[RSHOULDER] = true;
			sk.needsCheck[RELBOW] = true;
			sk.needsCheck[RHAND] = true;
		}
	}
	else if (body == "legs") {
		if (pos == "left")
		{
			sk.needsCheck[LHIP] = true;
			sk.needsCheck[LKNEE] = true;
			sk.needsCheck[LFOOT] = true;
		}
		else if (pos == "right") {
			sk.needsCheck[RHIP] = true;
			sk.needsCheck[RKNEE] = true;
			sk.needsCheck[RFOOT] = true;
		}
		else {
			sk.needsCheck[LHIP] = true;
			sk.needsCheck[LKNEE] = true;
			sk.needsCheck[LFOOT] = true;
			sk.needsCheck[RHIP] = true;
			sk.needsCheck[RKNEE] = true;
			sk.needsCheck[RFOOT] = true;
		}
	}
	else {
		for (int i = 0; i < 14; i++)
		{
			sk.needsCheck[i] = true;
		}
	}

	return sk;
}
