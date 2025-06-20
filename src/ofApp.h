#pragma once

#include "ofMain.h"
#include "water.h"
#include "ofxOpenCv.h"
#include "utils.h"

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

	random_device rd;

	ofVideoGrabber video;

	ofxCvHaarFinder harrFinder;
	ofxCvContourFinder contourFinder;

	vector<vector<cv::Point>> contour;

	vector<Water*> waterfall;

	int water_width = 51;
	int offset = 20;

	int opacity[51];
};
