#pragma once
#include "stdafx.h"
#include "tts.h"
#include "ja_text.h"
#include "../CICP-ActionTemplates/UtilsHAR.h"
#include <random>
#include <iostream>
#include <iterator>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}

void tts(std::wstring &text) {
	// Japanese
	std::wstring newtext = L"<LANG LANGID=\"411\">";
	// English
	//std::wstring newtext = L"<LANG LANGID=\"409\">";
	newtext.append(text);
	newtext.append(L"</LANG>");
	LPCWSTR stext = (LPCWSTR)newtext.c_str();
	ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

	if (SUCCEEDED(hr))
	{
		hr = pVoice->Speak(stext, 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}

	::CoUninitialize();
}

bool perfect_pos(BODY_PART bp, const posskeleton& posskel) {
	if (posskel.positions[bp].rightleft == 0 && posskel.positions[bp].updown == 0
		&& posskel.positions[bp].fwdbwd == 0)
		return true;
	else
		return false;
}

std::wstring get_name(BODY_PART bp) {
	switch (bp)
	{
	case HEAD:
		return HEAD_NAME;
		break;
	case NECK:
		return NECK_NAME;
		break;
	case LSHOULDER:
		return LSHOULDER_NAME;
		break;
	case LELBOW:
		return LELBOW_NAME;
		break;
	case LHAND:
		return LHAND_NAME;
		break;
	case RSHOULDER:
		return RSHOULDER_NAME;
		break;
	case RELBOW:
		return RELBOW_NAME;
		break;
	case RHAND:
		return RHAND_NAME;
		break;
	case TORSO:
		return TORSO_NAME;
		break;
	case LHIP:
		return LHIP_NAME;
		break;
	case LKNEE:
		return LKNEE_NAME;
		break;
	case LFOOT:
		return LFOOT_NAME;
		break;
	case RHIP:
		return RHIP_NAME;
		break;
	case RKNEE:
		return RKNEE_NAME;
		break;
	case RFOOT:
		return RFOOT_NAME;
		break;
	default:
		return L"";
		break;
	}
}

std::wstring double2ws(double a) {
	std::wostringstream ws;
	double num = abs(a);
	ws << num;
	std::wstring s(ws.str());
	s.append(L"cm");
	return s;
}

std::wstring int2ws(int a) {
	std::wostringstream ws;
	int num = abs(a);
	ws << num;
	std::wstring s(ws.str());
	s.append(L"cm");
	return s;
}

void feedback_body_part(BODY_PART bp, const fbskeleton& fbskel, const posskeleton& posskel) {
	if (!fbskel.needsCheck[bp]) {
		return;
	}
	std::wstring res = L"";
	if (perfect_pos(bp, posskel)) {
		res = *select_randomly(FB_GOOD_POS.begin(), FB_GOOD_POS.end());
	}
	else {
		res = *select_randomly(FB_WRONG_BEGIN.begin(), FB_WRONG_BEGIN.end());
		res.append(get_name(bp));

		double fwdbwd = posskel.positions[bp].fwdbwd;
		double rightleft = posskel.positions[bp].rightleft;
		double updown = posskel.positions[bp].updown;
		
		if (fwdbwd != 0) {
			res.append(double2ws(fwdbwd));
			if (fwdbwd > 0)
				res.append(BACKWARD);
			else
				res.append(FORWARD);
		}
			
		if (rightleft != 0) {
			res.append(double2ws(rightleft));
			if (rightleft > 0)
				res.append(TO_THE_RIGHT);
			else 
				res.append(TO_THE_LEFT);
		}

		if (updown != 0) {
			res.append(double2ws(updown));
			if (updown > 0)
				res.append(DOWN);
			else
				res.append(UP);
		} 

		std::wstring res_end = *select_randomly(FB_WRONG_END.begin(), FB_WRONG_END.end());
		res.append(res_end);
	}

	if (!res.empty()) {
		tts(res);
	}
}

void speech_feedback(const fbskeleton fbskel, const posskeleton posskel) {
	feedback_body_part(HEAD, fbskel, posskel);
	feedback_body_part(NECK, fbskel, posskel);
	feedback_body_part(LSHOULDER, fbskel, posskel);
	feedback_body_part(LELBOW, fbskel, posskel);
	feedback_body_part(LHAND, fbskel, posskel);
	feedback_body_part(RSHOULDER, fbskel, posskel);
	feedback_body_part(RELBOW, fbskel, posskel);
	feedback_body_part(RHAND, fbskel, posskel);
	feedback_body_part(TORSO, fbskel, posskel);
	feedback_body_part(LHIP, fbskel, posskel);
	feedback_body_part(LKNEE, fbskel, posskel);
	feedback_body_part(LFOOT, fbskel, posskel);
	feedback_body_part(RHIP, fbskel, posskel);
	feedback_body_part(RKNEE, fbskel, posskel);
	feedback_body_part(RFOOT, fbskel, posskel);
}