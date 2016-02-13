#pragma once
#include <iostream>
#include <string>



int start_listening(const std::string& word);
ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext, const std::string& command);
void get_text(ISpRecoContext* reco_context);
void check_result(const HRESULT& result);

