#pragma once
#include "stdafx.h"
#include "tts.h"
void tts(LPCWSTR text) {
	ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(hr))
	{
		hr = pVoice->Speak(text, 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}

	::CoUninitialize();
}