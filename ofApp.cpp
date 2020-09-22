#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };

	for (int x = -210; x <= 210; x += 210) {

		for (int y = -210; y <= 210; y += 210) {

			for (int i = 0; i < 3; i++) {

				auto radius = 25 + i * 25;
				auto walker_location = glm::vec2(x, y) + glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -100, 100), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -100, 100));

				for (int k = 0; k < color_list.size(); k++) {

					auto noise_seed = ofRandom(1000);

					ofSetColor(color_list[k]);
					ofBeginShape();
					for (int deg = 0; deg < 360; deg += 1) {

						auto location = glm::vec2(x, y) + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
						auto distance = glm::distance(location, walker_location);
						if (distance < radius) {

							auto noise_radius = ofMap(ofNoise(noise_seed, location.x * 0.035, location.y * 0.035, ofGetFrameNum() * 0.005), 0, 1, radius - 45, radius + 45);
							auto noise_location = glm::vec2(x, y) + glm::vec2(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD));
							auto gap = location - noise_location;
							ofVertex(location + gap * ofMap(distance, 0, radius * 0.75, 1, 0));
						}
						else {

							ofVertex(location);
						}
					}
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}