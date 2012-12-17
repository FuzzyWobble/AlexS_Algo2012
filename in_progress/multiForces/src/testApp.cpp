#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(0,0,0);
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	
	for (int i = 0; i < int(ofRandom(10,50)); i++){
		particle myParticle;
		myParticle.setInitialCondition(100+(5*i),300,0,0);
		particles.push_back(myParticle);
	}
	
	//particles[0].bFixed = true;
	
	for (int i = 1; i < particles.size(); i++){
		spring mySpring;
		mySpring.distance		= ofRandom(5,15);
		mySpring.springiness	= ofRandom(0.05,0.15);
		int rr = int(ofRandom(0,particles.size()));
		int ss = int(ofRandom(0,particles.size()));
		if(ss==rr){
			ss=rr+1;
		}
		mySpring.particleA = & (particles[rr-1]);
		mySpring.particleB = & (particles[ss]);
		springs.push_back(mySpring);
	}
	
		
	ofNoFill();
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	for (int i = 0; i < particles.size(); i++){
		
		particles[i].addRepulsionForce(mouseX, mouseY, 60, 0.7);
		
		for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j], 40, 0.07);
		}
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].bounceOffWalls();
		particles[i].addDampingForce();
		particles[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetLineWidth(1);
	ofSetColor(0xffffff);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].draw();
	}
	
	ofSetLineWidth(20);
	ofSetColor(0,255,0);
	
	ofBeginShape();
	for (int i = 0; i < particles.size(); i++){
		//ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
	}
	ofEndShape();

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':
			// reposition everything: 
			for (int i = 0; i < particles.size(); i++){
				particles[i].setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}
			break;
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	particles[0].pos.set(mouseX, mouseY);
	/*particles.erase(particles.begin());
	particle myParticle;
	myParticle.setInitialCondition(x,y,0,0);
	particles.push_back(myParticle);*/
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	//particles[0].bFixed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
	//particles[0].bFixed = false;
}

