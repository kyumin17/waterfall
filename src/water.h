#pragma once
#include "ofxOpenCv.h"

class Water {
public:
	int x;
	int y;
	int w;
	int a;
	int speed;

	Water(int _x, int _y, int _w, int _a, int _speed);

	bool isCollide(cv::Point p1, cv::Point p2);
	bool moveWater(vector<vector<cv::Point>> contours);
};