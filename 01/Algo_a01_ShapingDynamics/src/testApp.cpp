#include "testApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void testApp::setup(){

	// macs by default run on non vertical sync, which can make animation very, very fast
	// this fixes that: 
	
	ofSetVerticalSync(true);
	
	// set background: 
	
	ofBackground(30,30,30);
	
	pct = 0;							// a variable we can alter...
	current_x = current_y = prev_x = prev_y = 0;
	loopSize = 100;
} 

//--------------------------------------------------------------
void testApp::update(){
	
	pct += 0.01;
	if (pct > 1){ 
		//do nothing
	}
	else{
		for (int i = 0; i < loopSize; i++){
			myRectangles[i].interpolateByPct(pct);		// go between pta and ptb
		}
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	for (int i = 0; i < loopSize; i++){ 
		ofSetColor(2*i+25);
		float size_c = 2000.0/i - 19; //range 1981-1
		myRectangles[i].draw(size_c);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	pct = 0;
	
	prev_x = current_x;
	prev_y = current_y;
	current_x = x;
	current_y = y;
	
	dist_between_points =  ofDist(prev_x, prev_y, current_y, current_y);
	pct_between_points = dist_between_points / ofDist(0,0,ofGetWidth(),ofGetHeight());
	//didnt use these values yet
	
	for (int i = 0; i < loopSize; i++){
		myRectangles[i].posa.x = prev_x;
		myRectangles[i].posa.y = prev_y;
		myRectangles[i].posb.x = current_x;
		myRectangles[i].posb.y = current_y;
		myRectangles[i].shaper = 0.5 + 0.2 * i;
		myRectangles[i].interpolateByPct(0);	// start at 0 pct
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
