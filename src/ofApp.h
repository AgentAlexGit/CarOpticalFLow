#pragma once



#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

#include "opencv2/core.hpp"

#include "iostream"

#include "OptFlowHandler.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

	private:

		void setUpButtons();

		OptFlowHandler flowHandler;
		cv::Mat img_color_temp ,img_thresh;
		ofxPanel panel;
		ofxLabel curVideoName;
		ofxFloatSlider errode;
		ofxFloatSlider dialate;
		ofxGuiGroup Videogroup;
		vector<ofxButton> videos;
		ofDirectory dir;
		string path = "videos";



};

