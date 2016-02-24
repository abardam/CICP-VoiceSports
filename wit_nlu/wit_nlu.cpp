// wit_nlu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
* main.cpp
* Copyright (C) 2016 truong-d <truong-d@truongd-ThinkPad-X1-Carbon-3rd>
*
* Distributed under terms of the MIT license.
*/

#include "wit_lib.h"
#include "dict.h"
#include <iostream>
int main(int argc, char *argv[])
{
	//initialize the japanese-english map
	dict *d = new dict();

	//get the english mapping of a japanese sentence
	std::string en = d->getEn(u8"私 の 足 は 今 大丈夫 です か");
	//std::cout << en << std::endl;
	
	//initialize the NLU component
	WitLib *witlib = new WitLib();

	//get the skeleton joints given an english sentence
	fbskeleton sk = witlib->getJoints(en);
	
	//print the joints to check
	for (int i = 0; i < 14; i++) {
		std::cout << sk.needsCheck[i] << std::endl;
	}
	
	std::getchar();
	return 0;
}
