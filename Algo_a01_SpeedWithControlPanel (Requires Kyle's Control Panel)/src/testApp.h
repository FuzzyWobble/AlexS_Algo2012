#pragma once

#include "ofMain.h"
#include "ofxControlPanel.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	ofxControlPanel  panel;
	
	float xpos;
	
	float xpos_start;
	int dist_timer;
	float calc_cm_per_sec;

		
};
