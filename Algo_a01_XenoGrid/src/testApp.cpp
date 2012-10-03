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
	
	for(int i=0;i<16;i++){ //x
		for(int j=0;j<16;j++){ //y
			myRectangles[i*16+j].pos.x = ((800.0/16.0)*i)+((800.0/16.0)/2.0);
			myRectangles[i*16+j].pos.y = ((800.0/16.0)*j)+((800.0/16.0)/2.0);
			//set original position 
			myRectanglesOriginal[i*16+j].pos.x = myRectangles[i*16+j].pos.x;
			myRectanglesOriginal[i*16+j].pos.y = myRectangles[i*16+j].pos.y;
		}
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
		for(int i=0;i<16;i++){ //x
			for(int j=0;j<16;j++){ //y
				
				float dist = ofDist(myRectanglesOriginal[i*16+j].pos.x, myRectanglesOriginal[i*16+j].pos.y, mouseX, mouseY);
				if(dist<200){
					myRectangles[i*16+j].xenoToPoint(mouseX, mouseY, 0.015+(1-(dist/200.0))*0.025);
				}
				else{
					myRectangles[i*16+j].xenoToPoint(myRectanglesOriginal[i*16+j].pos.x, myRectanglesOriginal[i*16+j].pos.y, 0.04);
				}
				
			}
		}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			myRectangles[i*16+j].draw(10, 1);
		}
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
