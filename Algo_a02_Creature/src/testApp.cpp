#include "testApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	// macs by default run on non vertical sync, which can make animation very, very fast
	// this fixes that: 
	
	ofSetVerticalSync(true);
	
	// set background: 
	
	ofEnableAlphaBlending();
	ofBackground(0,0,0);

	for(int i=0;i<25;i++){
		myRecs[i].pos.x = i*15;
		myRecs[i].pos.y = 50;	
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
	for(int i=0;i<25;i++){
		if(i>0){
			if(ofDist(myRecs[i].pos.x,myRecs[i].pos.y,myRecs[i-1].pos.x,myRecs[i-1].pos.y)>10.0){
				myRecs[i].xenoToPoint(myRecs[i-1].pos.x, myRecs[i-1].pos.y);
			}
		}
		else{
			if(ofDist(myRecs[i].pos.x,myRecs[i].pos.y,mouseX,mouseY)>10.0){
				myRecs[i].xenoToPoint(mouseX, mouseY);
			}			
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	float dist;
	for(int i =0;i<25;i++){
		if(i>0){
			dist = ofDist(myRecs[i].pos.x,myRecs[i].pos.y,myRecs[i-1].pos.x,myRecs[i-1].pos.y);
		}
		else{
			dist = ofDist(myRecs[i].pos.x,myRecs[i].pos.y,mouseX,mouseY);
		}
		myRecs[i].draw(i,dist);
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
