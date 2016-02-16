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
#define LHIP_NAME L"左股関節"
#define LKNEE_NAME L"左膝"
#define LFOOT_NAME L"左足"
#define RHIP_NAME L"右股関節"
#define RKNEE_NAME L"右膝"
#define RFOOT_NAME L"右足"
#define BACKWARD L"前へ"
#define FORWARD L"後ろへ"
#define TO_THE_LEFT L"左に"
#define TO_THE_RIGHT L"右に"
#define UP L"上"
#define DOWN L"下"
std::vector<std::wstring> FB_GOOD_POS = { L"あなたは完璧な位置を持っています", L"あなたは素晴らしい仕事をしてきました",
L"それは最高だ"};
std::vector<std::wstring> FB_WRONG_BEGIN = { L"あなたの"};
std::vector<std::wstring> FB_WRONG_END = { L"を動かしてください" };
#endif
