#pragma once
#include <algorithm>
#include <vector>
#include <ofxOpenCv.h>
#include "water.h"

bool isSkinColor(int r, int g, int b);

void simplifyLine(vector<vector<cv::Point>>& line);