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
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(!pause){
		if(direction){
			timer += 0.04;
		}
		else{
			timer -= 0.04;	
		}
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	float xorig = ofGetWidth()/2;
	float yorig = ofGetHeight()/2;
	float x,y,dist,opac,sz,radius,angle;
	
	for (int i = 0; i < 50; i++){
	
		radius = abs(cos(timer)*100) + (i * 5); //radius is oscillating, but only with positive values
		angle = sin(timer*(i/50.0)); //angle is oscilating, the oscillation changes for each circle as i increases
		
		for(float j=0.0;j<2.0*PI;j=j+PI/2.0){
			x = xorig + radius * cos(angle+j);
			y = yorig + radius * -sin(angle+j);
			dist = ofDist(xorig,yorig,x,y);
			opac = (1 - dist/400.0)*250.0;
			ofSetColor(255,255,255,opac);
			ofCircle(x,y,3.0);
		}
	
	}	
	ofSetColor(100);
	ofDrawBitmapString("time:"+ofToString(int(ofGetElapsedTimef()))+", repeats after ~130sec, click to change direction", 5,10);
	
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

