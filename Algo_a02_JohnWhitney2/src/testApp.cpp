#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	
	ofBackground(0,0,0);
	
	ofSetCircleResolution(100);
	
	ofEnableAlphaBlending();
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	
	ofSetLineWidth(1.5);
	
	direction = true; 
	pause = true;
	timer = 0.0;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(!pause){
		if(direction){
			timer += 0.03;
		}
		else{
			timer -= 0.03;	
		}
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	float xorig = ofGetWidth()/2;
	float yorig = ofGetHeight()/2;
	float x,y,radius,angle;
	
	for(float a=0.0;a<2.0*PI;a+=PI/2.0){
		for(int i=0;i<30;i++){
			radius = abs(sin(timer/5.0)) * 100 + 11 * i;
			angle = timer * (i/20.0);
			x = xorig + radius * cos(angle+a);
			y = yorig + radius * -sin(angle+a);
			ofPoint pt = ofPoint(x,y);
			ptsArrayA[i] = pt;
			float dist = ofDist(xorig,yorig,x,y);
			ofSetColor(200,200,200,(1-dist/500.0)*255);
			ofCircle(x,y,2.0);
		}
		
		for(int i=1;i<30;i++){
			ofPoint pt1 = ptsArrayA[i];
			ofPoint pt2 = ptsArrayA[i-1];
			cout << pt1 << endl;
			float dist = ofDist(xorig,yorig,pt1.x,pt2.x);
			ofSetColor(200,200,200,(1-dist/500.0)*255);
			ofLine(pt1.x, pt1.y, pt2.x, pt2.y);
		}
	}
		
	ofSetColor(100);
	ofDrawBitmapString("[p] to play, click to switch direction", 5,10);
	
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

