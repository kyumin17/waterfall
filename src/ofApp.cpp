#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.setVerbose(true);
    video.setup(320 * 4, 240 * 4);

	ofSetFrameRate(30);

	harrFinder.setup("haarcascade_frontalface_default.xml");

	mt19937 gen(rd());
	uniform_int_distribution<int> dis(35, 50);

	for (int i = 0; i < water_width; i++) {
		opacity[i] = 30;
	}

	for (int i = 0; i < water_width; i++) {
		int rand = dis(gen);
		if (rand % 5 == 0) opacity[i] = rand;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

	ofPixels pixels = video.getPixels();
	pixels.mirror(false, true);

	// find head
	// harrFinder.findHaarObjects(pixels);

	// ofRectangle head = harrFinder.blobs.size() > 0 ? harrFinder.blobs[0].boundingRect : ofRectangle(0, 0, 0, 0);

	unsigned char* data = pixels.getData();

	for (int i = 0; i < pixels.getWidth() * pixels.getHeight() * 3; i+=3) {
		unsigned char r = data[i];
		unsigned char g = data[i + 1];
		unsigned char b = data[i + 2];

		unsigned char v = isSkinColor(r, g, b) ? 255 : 0;
		data[i] = data[i + 1] = data[i + 2] = v;
	}
	
	pixels.setImageType(OF_IMAGE_GRAYSCALE);

	ofxCvGrayscaleImage gray_image;
	gray_image.setFromPixels(pixels);

	contourFinder.findContours(gray_image, 6000, 320 * 4 * 240 * 4 / 3, 3, false);

	contour.clear();

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		vector<cv::Point> pts;
		for (auto j : contourFinder.blobs[i].pts) {
			pts.push_back(cv::Point(j.x, j.y));
		}

		contour.push_back(pts);
	}

	simplifyLine(contour);

	for (int i = 0; i < water_width; i++) {
		for (int j = 0; j < 4; j++) {
			waterfall.push_back(new Water(ofGetWidth() / 2 - offset * water_width / 2 + i * offset, offset * j, offset, opacity[i]));
		}
	}

	for (size_t i = 0; i < waterfall.size(); i++) {
		waterfall[i]->y += offset * 4;

		if (waterfall[i]->y >= 240 * 4) {
			waterfall.erase(waterfall.begin() + i);
		}

		isCollide(contour, waterfall[i]);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);

	ofPushMatrix();
	ofTranslate(video.getWidth(), 0);
	ofScale(-1, 1);
	video.draw(0, 0);
	ofPopMatrix();

	ofSetColor(0, 255, 0);
	for (auto points : contour) {
		for (auto point : points) {
			ofDrawCircle(point.x, point.y, 4);
		}
	}

	for (size_t i = 0; i < waterfall.size(); i++) {
		ofSetColor(230, 230, 255, waterfall[i]->a);
		ofDrawRectangle(waterfall[i]->x, waterfall[i]->y, waterfall[i]->w, waterfall[i]->w);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
