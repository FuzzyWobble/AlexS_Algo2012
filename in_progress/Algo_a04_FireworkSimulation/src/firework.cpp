/*
 *  firework.cpp
 *  multiParticles
 *
 *  Created by Alex S on 10/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "firework.h"

void firework::init(){
	streakLength = 20;
	bExploding = false;
	streakX = ofRandom(200,ofGetWidth()-200);
	streakY = ofGetHeight();
	streakVX = ofRandom(-1,1);
	streakVY = ofRandom(5,8);
	curveX = ofRandom(-0.05,0.05);
	explodeHeight = ofRandom(0.15,0.45)*ofGetHeight();
	explodeDuration = ofRandom(1.0,3.0);
	
}
void firework::drawStreak(){
	if(streak.size()>3){
		ofFill();
		ofSetColor(200,200,200);
		ofCircle(streakX,streakY,5.0);
		int lng;
		if(streak.size()>20){
			lng = 20;
		}
		else{
			lng = streak.size();
		}
		for(int i=0;i<lng;i++){
			ofSetColor(200,200,200,150*(1.0-(i/(float)lng)));
			ofCircle(streak[streak.size()-(i+1)].x,streak[streak.size()-(i+1)].y,4.0*(1.0-(i/(float)lng)));
		}
	}
}
void firework::updateStreak(){
	streakVX += curveX;
	streakX += streakVX;
	streakY -= streakVY;
	ofPoint pt;
	pt.set(streakX,streakY);
	streak.push_back(pt);
}
void firework::explode(){
	explodeStart = ofGetElapsedTimef();
	for (int i = 0; i < 50; i++){
		particle myParticle;
		float angle = ofRandom(0,2.0*PI);
		float velX = cos(angle)*5.0;
		float velY = sin(angle)*5.0;
		myParticle.setInitialCondition(streakX,streakY,velX,velY);
		particles.push_back(myParticle);
		
		particlePath.push_back(vector<ofPoint>());
		ofPoint st;
		st.set(streakX,streakY);
		particlePath[i].push_back(st);
	}
}
void firework::drawExplode(){
	if(ofGetElapsedTimef()-explodeStart < explodeDuration){
		float alpha = 255 * (1.0-(ofGetElapsedTimef()-explodeStart)/explodeDuration);
		ofSetColor(200,200,200,alpha);
		for (int i = 0; i < particles.size(); i++){
			particles[i].draw();
		}
		ofSetColor(100,100,100);
		ofNoFill();
		ofBeginShape();
		for (int i = 0; i < particlePath.size(); i++){
			for (int j = 0; j < particlePath[i].size(); j++){
				ofCurveVertex(particlePath[i][j].x, particlePath[i][j].y);
			}		
		}
		ofEndShape();
		ofFill();
	}
}
void firework::updateExplode(){
	if(ofGetElapsedTimef()-explodeStart < explodeDuration){
		for (int i = 0; i < particles.size(); i++){
			particles[i].resetForce();
			particles[i].addForce(0,0.08); //gravity
			particles[i].addDampingForce();
			particles[i].update();
			ofPoint st;
			st.set(particles[i].pos.x,particles[i].pos.y);
			particlePath[i].push_back(st);
		}
	}
	
}
