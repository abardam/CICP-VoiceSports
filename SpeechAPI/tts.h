#pragma once
#ifndef TTS_H
#define TTS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "../CICP-ActionTemplates/UtilsHAR.h"
void tts(std::wstring &text);
void speech_feedback(const fbskeleton fbskel, const posskeleton posskel);
#endif