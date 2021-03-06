#pragma once

#ifndef UTILS_HAR_H
#define UTILS_HAR_H

/*Useful variables for human action recognition*/
#include <vector>
#include <array>

#define HAR_PATH "..\\Database\\"

#define NUM_JOINTS 15	// Number of joints in the skeleton model

#define NUM_COORD 3	// Number of coordinates in each joint position (3D: x-y-z)

/*// The order of the joints in the array is:
#define HEAD 0
#define NECK 1
#define LSHOULDER 2
#define LELBOW 3
#define LHAND 4
#define RSHOULDER 5
#define RELBOW 6
#define RHAND 7
#define TORSO 8
#define LHIP 9
#define LKNEE 10
#define LFOOT 11
#define RHIP 12
#define RKNEE 13
#define RFOOT 14
*/
enum BODY_PART {
	HEAD, NECK, LSHOULDER, LELBOW, LHAND,
	RSHOULDER, RELBOW, RHAND, TORSO, LHIP,
	LKNEE, LFOOT, RHIP, RKNEE, RFOOT
};

struct fbskeleton {
	bool needsCheck[NUM_JOINTS];
};

struct position {
	double rightleft;
	double updown;
	double fwdbwd;
};

struct posskeleton {
	position positions[NUM_JOINTS];
	int confidences[NUM_JOINTS];
};

struct actskeleton {
	//std::vector<std::array<position, NUM_JOINTS> > positions_a;
	//std::vector<std::array<bool, NUM_JOINTS> > confidences_a;
	std::vector < posskeleton > poses;
};

#endif
