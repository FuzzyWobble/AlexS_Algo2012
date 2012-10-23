#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(0,0,0);
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	
	movingJelly.setInitialCondition(ofRandom(200,800),ofRandom(200,500),3,3);
	movingJelly.setDamping(0.15);
	
	//tdfSmall.loadImage("images/tdf_1972_poster.jpg");
	
	f1.loadImage("f1.png");
	f2.loadImage("f2.png");
	f3.loadImage("f3.png");
	f4.loadImage("f4.png");
	pf1 = &f1;
	pf2 = &f2;
	pf3 = &f3;
	pf4 = &f4;
	
	for (int i = 0; i < 600; i++){
		particle myParticle;
		int randInt = (int)ofRandom(1,5);
		if(randInt==1){
			myParticle.fish = &f1;
		}
		if(randInt==2){
			myParticle.fish = &f2;
		}
		if(randInt==3){
			myParticle.fish = &f3;
		}
		if(randInt==4){
			myParticle.fish = &f4;
		}
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
	
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
		
		//global forcers
		particles[i].addAttractionForce(movingJelly.pos.x, movingJelly.pos.y, 1200, 1.0);
		
		//particle-to-particle forces
		for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j],30,2.0);
			particles[i].addRepulsionForce(mouseX,mouseY,100,0.05);
		}
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
		//particles[i].bounceOffWalls();
		particles[i].update();
	}
	
	movingJelly.resetForce();
	movingJelly.addRepulsionForce(mouseX, mouseY, 300, 5.0);
	movingJelly.addDampingForce();
	movingJelly.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	//ofSetColor(0xffffff);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw(movingJelly.pos.x,movingJelly.pos.y);
	}
	
	
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
//	particles.erase(particles.begin());
//	particle myParticle;
//	myParticle.setInitialCondition(x,y,0,0);
//	particles.push_back(myParticle);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
