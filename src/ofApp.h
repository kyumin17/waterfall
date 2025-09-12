#pragma once

#include "ofMain.h"
#include "waterfall.h"
#include "ofxOpenCv.h"
#include "utils.h"

#define WIDTH 320 * 4
#define HEIGHT 240 * 4

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofVideoGrabber video;

	ofxCvContourFinder contourFinder;

	vector<vector<cv::Point>> contours;

	Waterfall waterfall;

	ofSoundPlayer water_sound;
	ofSoundPlayer water_collide_sound;
};
