#include "testApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	// macs by default run on non vertical sync, which can make animation very, very fast
	// this fixes that: 
	
	ofSetVerticalSync(true);
	
	// set background: 
	
	ofEnableAlphaBlending();
	ofBackground(0);
	
	
	// set the position of the rectangle:
	
	xeno_circles = 50;
	
	for(int i=0;i<xeno_circles;i++){
		myRectangles[i].pos.x = 50;
		myRectangles[i].pos.y = 50;
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
	float spd = 0.001;
	
	for(int i=0;i<xeno_circles;i++){
		spd += 0.003;
		
		myRectangles[i].xenoToPoint(mouseX, mouseY, spd);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	float sz = 1.0;
	float opc = 0.0;
	for(int i=0;i<xeno_circles;i++){
		opc = i/60.0;
		sz = pow(log(i*2),2.0); //exp size growth
		myRectangles[i].draw(sz, opc);
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
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
