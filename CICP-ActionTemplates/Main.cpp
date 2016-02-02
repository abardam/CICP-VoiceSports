#include "PoseMatcher.h"
#include <iostream>	// std::cout

int main(int argc, char *argv)
{
	PoseMatcher matcher;
	posskeleton inskel;
	fbskeleton fbjoints;
	int action;

	for (int j = 0; j < NUM_JOINTS; ++j)
	{
		inskel.positions[j].rightleft = 0;
		inskel.positions[j].updown = 0;
		inskel.positions[j].fwdbwd = 0;
		inskel.confidences[j] = 1;

		fbjoints.feedback[j] = true;
	}
	action = 1;

	posskeleton feedback = matcher.weightedPoseMatching(inskel, fbjoints, action);

	for (int j = 0; j < NUM_JOINTS; ++j)
	{
		std::cout << feedback.positions[j].rightleft << ' ';
		std::cout << feedback.positions[j].updown << ' ';
		std::cout << feedback.positions[j].fwdbwd << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//system("\"\"C:\\Program Files\\MPC-HC\\mpc-hc64.exe\" \"D:\\PV_2015_yokoyalab_3.mp4\"\"");

	getchar();

	return 0;
}
