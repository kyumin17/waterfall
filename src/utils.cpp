#include "utils.h"

bool isSkinColor(int r, int g, int b) {
	bool cond1 = r > 95 && g > 40 && b > 20;
	bool cond2 = __max(r, __max(g, b)) - __min(r, __min(g, b)) > 15;
	bool cond3 = abs(r - g) > 15 && r > g && r > b;

	return cond1 && cond2 && cond3;
}

int isCollide(vector<vector<cv::Point>> contour, Water* water) {
	/*
	* return collide line index
	* if water isnt collide, return -1
	*/

	double wx = water->x;
	double wy = water->y;
	double ww = water->w;

	for (vector<cv::Point> area : contour) {
		for (size_t i = 0; i < area.size() - 1; i++) {
			auto [x1, y1] = area[i];
			auto [x2, y2] = area[i + 1];

			if (x1  <= wx && wx <= x2) {
				double a = y1 - y2;
				double b = x2 - x1;
				double c = x1 * y2 - x2 * y1;
				double dist = abs(a * wx + b * wy + c) / sqrt(a * a + b * b);

				if (dist < ww) {
					water->a = 255;
					return i;
				}
			}
		}
	}

	return -1;
}

void simplifyLine(vector<vector<cv::Point>>& line) {
	for (size_t i = 0; i < line.size(); i++) {
		vector<cv::Point> temp;
		cv::approxPolyDP(line[i], temp, cv::arcLength(line[i], true) * 0.02, true);
		line[i] = temp;
	}
}