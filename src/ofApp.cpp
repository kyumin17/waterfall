#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.setVerbose(true);
    video.setup(320 * 4, 240 * 4);
	gray_image.allocate(320 * 4, 240 * 4);

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
	harrFinder.findHaarObjects(pixels);

	ofRectangle head(0, 0, 0, 0);
	head = harrFinder.blobs.size() > 0 ? harrFinder.blobs[0].boundingRect : head;

	// detect skin color
	for (int i = 0; i < pixels.getWidth(); i++) {
		for (int j = 0; j < pixels.getHeight(); j++) {
			ofColor color = pixels.getColor(i, j);
			if (!(head.x <= i && i <= head.x + head.width) && isSkinColor(color.r, color.g, color.b)) {
				pixels.setColor(i, j, ofColor(255));
			}
			else {
				pixels.setColor(i, j, ofColor(0));
			}
		}
	}

	pixels.setImageType(OF_IMAGE_GRAYSCALE);

	// ofxCvGrayscaleImage gray_image;
	gray_image.setFromPixels(pixels);

	contourFinder.findContours(gray_image, 5000, 320 * 4 * 240 * 4 / 2, 5, true);

	for (int i = 0; i < water_width; i++) {
		waterfall.push_back(new Water(ofGetWidth() / 2 - offset * water_width / 2 + i * offset, -1 * offset, offset, opacity[i]));
		waterfall.push_back(new Water(ofGetWidth() / 2 - offset * water_width / 2 + i * offset, -1 * offset / 2, offset, opacity[i]));
	}

	for (size_t i = 0; i < waterfall.size(); i++) {
		waterfall[i]->y += offset;

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

	ofSetColor(0, 255, 0);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw(0, 0);
	}

	for (size_t i = 0; i < waterfall.size(); i++) {
		ofSetColor(230, 230, 255, waterfall[i]->a);
		// ofDrawRectangle(waterfall[i]->x, waterfall[i]->y, waterfall[i]->w, waterfall[i]->w);
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
