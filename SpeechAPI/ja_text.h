#pragma once
#ifndef BODY_PART_JA_H
#define BODY_PART_JA_H
#include <vector>

#define HEAD_NAME L" head "
#define NECK_NAME L" neck "
#define LSHOULDER_NAME L" left shoulder "
#define LELBOW_NAME L" left elbow "
#define LHAND_NAME L" left hand "
#define RSHOULDER_NAME L" right shoulder "
#define RELBOW_NAME L" right elbow "
#define RHAND_NAME L" right hand "
#define TORSO_NAME L" torso "
#define LHIP_NAME L" left hip "
#define LKNEE_NAME L" left knee "
#define LFOOT_NAME L" left foot "
#define RHIP_NAME L" right hip "
#define RKNEE_NAME L" right knee "
#define RFOOT_NAME L" right foot "
#define BACKWARD L" backward "
#define FORWARD L" forward "
#define TO_THE_LEFT L" to the left "
#define TO_THE_RIGHT L" to the right "
#define UP L" up "
#define DOWN L" down "
std::vector<std::wstring> FB_GOOD_POS = { L"You have perfect position", L"You've done a great job",
L"That's perfect" };
std::vector<std::wstring> FB_WRONG_BEGIN = { L"You need to move your" };
#endif
