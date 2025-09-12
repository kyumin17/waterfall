
#pragma once
#include "water.h"
#include "ofMain.h"
#include <vector>
#include "ofxOpenCv.h"
#include <random>

using namespace std;

class Waterfall {
public:
	vector<Water*> v;
	int width;
	int offset;
	int speed;
	bool is_collide;

	void update(int window_width, vector<vector<cv::Point>> contours);
	void draw();
};