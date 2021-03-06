#pragma once
#include "stdafx.h"
#include "asr_native.h"
const ULONGLONG grammarId = 0;
const wchar_t* ruleName1 = L"ruleName1";
// This function exits when the word passed as parameter is said by the user
int start_listening(const std::string& word)
{
	std::cout << "Starting ..." << std::endl;
	// Initialize COM library
	if (FAILED(::CoInitialize(nullptr))) {
		return EXIT_FAILURE;
	}

	std::cout << "You should start Windows Recognition" << std::endl;
	std::cout << "Just say \"" << word << "\"" << std::endl;

	HRESULT hr;

	ISpRecognizer* recognizer;
	hr = CoCreateInstance(CLSID_SpSharedRecognizer,
		nullptr, CLSCTX_ALL, IID_ISpRecognizer,
		reinterpret_cast<void**>(&recognizer));
	check_result(hr);

	ISpRecoContext* recoContext;
	hr = recognizer->CreateRecoContext(&recoContext);
	check_result(hr);

	// Disable context
	hr = recoContext->Pause(0);
	check_result(hr);

	ISpRecoGrammar* recoGrammar = init_grammar(recoContext, word);

	hr = recoContext->SetNotifyWin32Event();
	check_result(hr);

	HANDLE handleEvent;
	handleEvent = recoContext->GetNotifyEventHandle();
	if (handleEvent == INVALID_HANDLE_VALUE) {
		check_result(E_FAIL);
	}

	ULONGLONG interest;
	interest = SPFEI(SPEI_RECOGNITION);
	hr = recoContext->SetInterest(interest, interest);
	check_result(hr);

	// Activate Grammar
	hr = recoGrammar->SetRuleState(ruleName1, 0, SPRS_ACTIVE);
	check_result(hr);

	// Enable context
	hr = recoContext->Resume(0);
	check_result(hr);

	// Wait for reco
	HANDLE handles[1];
	handles[0] = handleEvent;
	WaitForMultipleObjects(1, handles, FALSE, INFINITE);
	get_text(recoContext);

	std::cout << "Hello user" << std::endl;

	recoGrammar->Release();
	::CoUninitialize();

	system("PAUSE");
	return EXIT_SUCCESS;
}

/**
* Create and initialize the Grammar.
* Create a rule for the grammar.
* Add word to the grammar.
*/
ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext, const std::string& command)
{
	HRESULT hr;
	SPSTATEHANDLE sate;

	ISpRecoGrammar* recoGrammar;
	hr = recoContext->CreateGrammar(grammarId, &recoGrammar);
	check_result(hr);

	WORD langId = MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH);
	hr = recoGrammar->ResetGrammar(langId);
	check_result(hr);
	// TODO: Catch error and use default langId => GetUserDefaultUILanguage()

	// Create rules
	hr = recoGrammar->GetRule(ruleName1, 0, SPRAF_TopLevel | SPRAF_Active, true, &sate);
	check_result(hr);

	// Add a word
	const std::wstring commandWstr = std::wstring(command.begin(), command.end());
	hr = recoGrammar->AddWordTransition(sate, NULL, commandWstr.c_str(), L" ", SPWT_LEXICAL, 1, nullptr);
	check_result(hr);

	// Commit changes
	hr = recoGrammar->Commit(0);
	check_result(hr);

	return recoGrammar;
}

void get_text(ISpRecoContext* reco_context)
{
	const ULONG maxEvents = 10;
	SPEVENT events[maxEvents];

	ULONG eventCount;
	HRESULT hr;
	hr = reco_context->GetEvents(maxEvents, events, &eventCount);

	// Warning hr equal S_FALSE if everything is OK 
	// but eventCount < requestedEventCount
	if (!(hr == S_OK || hr == S_FALSE)) {
		check_result(hr);
	}

	ISpRecoResult* recoResult;
	recoResult = reinterpret_cast<ISpRecoResult*>(events[0].lParam);

	wchar_t* text;
	hr = recoResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &text, NULL);
	check_result(hr);

	CoTaskMemFree(text);
}

void check_result(const HRESULT& result)
{
	if (result == S_OK) {
		return;
	}

	std::string message;

	switch (result) {

	case E_INVALIDARG:
		message = "One or more arguments are invalids.";

	case E_ACCESSDENIED:
		message = "Acces Denied.";

	case E_NOINTERFACE:
		message = "Interface does not exist.";

	case E_NOTIMPL:
		message = "Not implemented method.";

	case E_OUTOFMEMORY:
		message = "Out of memory.";

	case E_POINTER:
		message = "Invalid pointer.";

	case E_UNEXPECTED:
		message = "Unexpecter error.";

	case E_FAIL:
		message = "Failure";

	default:
		message = "Unknown : " + std::to_string(result);
	}

	throw std::exception(message.c_str());
}
