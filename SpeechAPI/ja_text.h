#pragma once
#ifndef BODY_PART_JA_H
#define BODY_PART_JA_H
#include <vector>

#define HEAD_NAME L"頭"
#define NECK_NAME L"首"
#define LSHOULDER_NAME L"左肩"
#define LELBOW_NAME L"左肘"
#define LHAND_NAME L"左手"
#define RSHOULDER_NAME L"右肩"
#define RELBOW_NAME L"右肘"
#define RHAND_NAME L"右手"
#define TORSO_NAME L"胴体"
#define LHIP_NAME L"左腰"
#define LKNEE_NAME L"左膝"
#define LFOOT_NAME L"左足"
#define RHIP_NAME L"右腰"
#define RKNEE_NAME L"右膝"
#define RFOOT_NAME L"右足"
#define BACKWARD L"前に"
#define FORWARD L"後ろに"
#define TO_THE_LEFT L"左に"
#define TO_THE_RIGHT L"右に"
#define UP L"上に"
#define DOWN L"下に"
std::vector<std::wstring> FB_GOOD_POS = { L"正しい姿勢です", L"素晴らしい", L"そこで完璧", L"グッジョブ", L"上手！"};
std::vector<std::wstring> FB_WRONG_BEGIN = { L""};
std::vector<std::wstring> FB_WRONG_END = { L"を動かしてください" };
#endif
