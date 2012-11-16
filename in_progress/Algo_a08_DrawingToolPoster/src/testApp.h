#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	
		ofTrueTypeFont font;
		float pct;
		int stringWidth, stringHeight;

		vector<ofPolyline> letterLines; //holds a polyline for each letter
		vector<ofPolyline> letterLinesAdj; //correct position to center of screen
	
		vector <particle *> myParticles;
		
		//1 - attraction to mouse with xeno
		//2 - attraction to mouse without xeno
		//3 - vector field at pt
		//4 - reset with xeno
		int mode;
	
		vectorField VF;
	
		//long holdTimer;
		vector <ofPoint> hole;
		vector <long> heldDuration;
		ofPoint hit;
	
		float mouse_vx, mouse_vy, px, py;
		long holdTimer; 
	
		ofImage img;
		unsigned char * pix;
	
};

#endif

