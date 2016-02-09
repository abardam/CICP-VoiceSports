#pragma once
#include "stdafx.h"

HBITMAP rgbquad_to_hbitmap(RGBQUAD * rgbquad, int width, int height);
void resize_rgbquad(RGBQUAD * in, int in_w, int in_h, RGBQUAD * out, int out_w, int out_h);