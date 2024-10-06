#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->len = 15;
	for (float x = this->len; x <= ofGetWidth() - this->len; x += this->len) {

		for (float y = this->len; y <= ofGetHeight() - this->len; y += this->len) {

			this->start_location_list.push_back(glm::vec3(x, y, 0));
		}
	}

	for (int i = 0; i < 64; i++) {

		int r = ofRandom(this->start_location_list.size());

		auto log_list = vector<glm::vec2>();
		log_list.push_back(this->start_location_list[r]);
		this->location_list.push_back(log_list);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 1 == 0) {

		for (auto& log_list : this->location_list) {

			int r = ofRandom(4);
			int deg_start = r * 90;
			for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

				auto tmp_location = log_list.back() + glm::vec2(this->len * cos(deg * DEG_TO_RAD), this->len * sin(deg * DEG_TO_RAD));
				if (tmp_location.x < this->len || tmp_location.x > ofGetWidth() - this->len  
					|| tmp_location.y < this->len || tmp_location.y > ofGetHeight() - this->len) {

					continue;
				}

				bool flag = false;
				for (int i = 0; i < log_list.size(); i++) {

					if (tmp_location == log_list[i] && deg_start != deg && deg_start % 360 == deg % 360) {

						flag = true;
						break;
					}
				}
				if (flag) { continue; }

				log_list.push_back(tmp_location);
				break;
			}

			while (log_list.size() > 20) {

				log_list.erase(log_list.begin());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	int index = 0;
	for (auto& log_list : this->location_list) {

		for (int i = 0; i < log_list.size(); i++) {

			ofFill();
			color.setHsb(ofMap(index, 0, 64, 0, 255), 255, 255);
			ofSetColor(color);
			ofDrawCircle(log_list[i], this->len * 0.25);
		}
		index++;
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}