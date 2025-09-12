#include "waterfall.h"

void Waterfall::update(int window_width, vector<vector<cv::Point>> contours) {
	is_collide = false;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis_x(-2, 2);
	uniform_int_distribution<int> dis_y(-5, 5);
	uniform_int_distribution<int> dis_r(0, 2);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < speed * 2; j++) {
			v.push_back(new Water(window_width / 2 - offset * width / 2 + i * offset + dis_x(gen), offset * (j - speed * 2) / 2 + dis_y(gen), offset + dis_r(gen), 50, speed));
		}
	}

	for (size_t i = 0; i < v.size(); i++) {
		bool is_water_collide = v[i]->moveWater(contours);
		if (!is_collide) is_collide = is_water_collide;

		if (v[i]->y >= 240 * 4) {
			v.erase(v.begin() + i);
		}
	}
}

void Waterfall::draw() {
	for (size_t i = 0; i < v.size(); i++) {
		ofSetColor(230, 230, 255, v[i]->a);
		ofDrawCircle(v[i]->x + v[i]->w/2, v[i]->y + v[i]->w/2, v[i]->w / 2);
	}
}