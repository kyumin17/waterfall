#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.setVerbose(true);
    video.setup(WIDTH, HEIGHT);

	ofSetFrameRate(30);

	waterfall.width = 51;
	waterfall.offset = 10;
	waterfall.speed = 3;

	water_sound.load("water.mp3");
	water_collide_sound.load("water_collide.mp3");
	water_sound.play();
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

	contourFinder.findContours(gray_image, 6000, WIDTH * HEIGHT / 2, 3, true);

	contours.clear();

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		vector<cv::Point> pts;
		for (auto j : contourFinder.blobs[i].pts) {
			pts.push_back(cv::Point(j.x, j.y));
		}

		contours.push_back(pts);
	}

	simplifyLine(contours);

	waterfall.update(ofGetWidth(), contours);

	if (waterfall.is_collide) water_collide_sound.play();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);

	ofPushMatrix();
	ofTranslate(video.getWidth(), 0);
	ofScale(-1, 1);
	video.draw(0, 0);
	ofPopMatrix();

	waterfall.draw();
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
