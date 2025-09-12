#include "water.h"

Water::Water(int _x, int _y, int _w, int _a, int _speed) : x(_x), y(_y), w(_w), a(_a), speed(_speed) {

}

bool Water::isCollide(cv::Point p1, cv::Point p2) {
	if (min(p1.x, p2.x) <= x && x <= max(p1.x, p2.x)) {
		double slope = (double)(p1.y - p2.y) / (double)(p1.x - p2.x);
		double diff = y - slope * (x - p1.x) - p1.y;

		return 0 <= diff && diff < w * 3;
	}

	return false;
}

bool Water::moveWater(vector<vector<cv::Point>> contours) {
	for (vector<cv::Point> contour : contours) {
		for (size_t i = 0; i < contour.size(); i++) {
			cv::Point p1 = contour[i];
			cv::Point p2 = i == contour.size() - 1 ? contour[0] : contour[i + 1];
			double dx = p1.x - p2.x;
			double dy = p1.y - p2.y;

			if (isCollide(p1, p2)) {
				a -= 5;
				x += dx * w * speed / sqrt(dx * dx + dy * dy);
				y += dy * w * speed / sqrt(dx * dx + dy * dy);
				return true;
			}
		}
	}

	y += w * speed;

	return false;
}