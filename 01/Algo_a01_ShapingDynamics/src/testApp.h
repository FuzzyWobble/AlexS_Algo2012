#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "rectangle.h"

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

		rectangle myRectangles[100]; //must match loopSize
	
		float pct;
	
		int current_x, current_y, prev_x, prev_y;
	
		float dist_between_points, pct_between_points;
	
		int loopSize;
	
};

#endif

