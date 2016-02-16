// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tts.h"
#include "asr.h"
#include "../CICP-ActionTemplates/UtilsHAR.h"
void onFinalResult(std::string text)
{
	std::cout << "ASR RESULT: " << text;
}

int main()
{

	/* Text-to-speech synthesis
	std::wstring text = L"今日は暑いです";
	tts(text);
	*/


	/*Uncomment the below codes to start ASR service. You can add these code to a button onclick event.
	voicesport::SpeechKit speechkit = voicesport::SpeechKit();
	speechkit.connectOnFinalResult(makeFunctor((CBFunctor1<std::string> *)0, onFinalResult));
	
	if (!speechkit.startASR()) {
		std::cout << "ASR not available";
	}
	speechkit.stopASR();
	*/
	fbskeleton fbs;
	posskeleton posskel;
	fbs.needsCheck[LSHOULDER] = true;
	posskel.positions[LSHOULDER].fwdbwd = 1;
	posskel.positions[LSHOULDER].rightleft = 0;
	posskel.positions[LSHOULDER].updown = 0;
	speech_feedback(fbs, posskel);
	char a = getchar();
	
	return 0;
}

