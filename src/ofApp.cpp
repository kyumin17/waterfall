#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.setVerbose(true);
    video.setup(320 * 4, 240 * 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();

	ofPixelsRef pixels = video.getPixels();

	for (int i = 0; i < video.getHeight(); i++) {
		for (int j = 0; j < video.getWidth(); j++) {

		}
	}

	for (int i = 0; i < water_width; i++) {
		waterfall.push_back(new Water(ofGetWidth()/2 - offset * water_width/2 + i * offset, 20, 5));
	}

	for (size_t i = 0; i < waterfall.size(); i++) {
		waterfall[i]->y += 20;

		if (waterfall[i]->y >= 240 * 4) {
			waterfall.erase(waterfall.begin() + i);
		}
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

	ofSetColor(230, 230, 255, 100);

	for (size_t i = 0; i < waterfall.size(); i++) {
		ofDrawCircle(waterfall[i]->x, waterfall[i]->y, waterfall[i]->r);
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
