#pragma once
#ifndef UTILS_HAR_H
#define UTILS_HAR_H
#include <vector>
#include <array>

#define HAR_PATH "D:\\Notes\\IPGP\\CICP2015\\Database\\"

#define NUM_JOINTS 15	// Number of joints in the skeleton model

enum BODY_PART {HEAD, NECK, LSHOULDER, LELBOW, LHAND,
				RSHOULDER, RELBOW, RHAND, TORSO, LHIP,
				LKNEE, LFOOT, RHIP, RKNEE, RFOOT};

struct fbskeleton {
	bool needsCheck[NUM_JOINTS] = { false };
};

struct position {
	double rightleft;
	double updown;
	double fwdbwd;
};

struct posskeleton {
	position positions[NUM_JOINTS];
	bool confidences[NUM_JOINTS];
};

struct actskeleton {
	std::vector<std::array<position, NUM_JOINTS> > positions_a;
	std::vector<std::array<bool, NUM_JOINTS> > confidences_a;
};
#endif