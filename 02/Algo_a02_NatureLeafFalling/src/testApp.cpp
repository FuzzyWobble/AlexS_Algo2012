#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	
	ofBackground(0,0,0);
	
	ofSetCircleResolution(100);
	
	ofEnableAlphaBlending();
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	direction = true; 
	pause = true;
	rinc = 0.2;
	radius = 100.0;
}

//--------------------------------------------------------------
void testApp::update(){

	radius += rinc;

}

//--------------------------------------------------------------
void testApp::draw(){
	
	float xorig,yorig,angle,x,y;
	
	if(ofGetElapsedTimef()<16.0){ //run for 16 sec
		xorig = ofGetWidth()/2;
		yorig = 40;
		angle = (cos(ofGetElapsedTimef()*(1.0 - ofGetElapsedTimef()/120.0)))/1.5;
		x = xorig + (radius * cos(angle-PI/2.0)) * (1.0 - ofGetElapsedTimef()/50.0);
		y = yorig + (radius * -sin(angle-PI/2.0)) * (1.0 - ofGetElapsedTimef()/50.0);
		ofSetColor(155,255,155);
		ofCircle(x,y,5.0);
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='p'){
		pause =! pause;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	direction =! direction;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

