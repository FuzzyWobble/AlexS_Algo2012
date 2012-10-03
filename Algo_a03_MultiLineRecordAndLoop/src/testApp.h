#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "timePoint.h"


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

		
		vector < timePoint > currentPts; //points we are currently drawing
		vector < vector < timePoint > > lines; //holds all lines 
		
		float startTime;
		bool bRecording;
		ofPoint getPosition(int lineNum, float durationPass);
		ofPoint getVelocity(int lineNum);
	
		float zero;
		float duration;

		float dragTimer;
	
		float loopDuration;
	
		vector <ofSoundPlayer> samples;
		ofSoundPlayer currentSound;
	
};

#endif
