#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "particle.h"

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
	
		//fish images and pointers...
		ofImage f1,f2,f3,f4;
		ofImage *pf1,*pf2,*pf3,*pf4;
		
		// let's make a vector of them
		vector <particle> particles;
	
		particle movingJelly;
	
		//ofPoint movingJelly;
		 
	
};

#endif
	
