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
	explodeDuration = ofRandom(2.0,4.0);
	color = ofColor(ofRandom(100,225),ofRandom(100,225),ofRandom(100,225));
	numParticles = ofRandom(10,50);
	explodeVelocity = numParticles/6.0;
	
}
void firework::drawStreak(){
	if(streak.size()>3){
		ofFill();
		//ofSetColor(color.r*ofRandom(1.0,1.6),color.g*ofRandom(1.0,1.2),color.b*ofRandom(1.0,1.2));
		ofSetColor(255,255,255,255);
		ofCircle(streakX,streakY,sin(ofGetElapsedTimef()*5)*4.0);
		int lng;
		if(streak.size()>20){
			lng = 20;
		}
		else{
			lng = streak.size();
		}
		for(int i=0;i<lng;i++){
			ofSetColor(color.r-30,color.g-30,color.b-30,150*(1.0-(i/(float)lng)));
			ofCircle(streak[streak.size()-i-1].x,streak[streak.size()-i-1].y,3.0*(1.0-(i/(float)lng)));
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
	for (int i = 0; i < numParticles; i++){
		particle myParticle;
		float angle = ofRandom(0,2.0*PI);
		float velX = cos(angle)*explodeVelocity;
		float velY = sin(angle)*explodeVelocity;
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
		ofSetColor(color.r*ofRandom(0.5,1.5),color.g*ofRandom(0.5,1.5),color.b*ofRandom(0.5,1.5),255 * (1.0-(ofGetElapsedTimef()-explodeStart)/explodeDuration));
		for (int i = 0; i < particles.size(); i++){
			particles[i].draw();
		}
		for (int i=0;i<particlePath.size();i++){
			
			if(particlePath[i].size()>5){
				int lng;
				if(particlePath[i].size()>30){
					lng = 30;
				}
				else{
					lng = particlePath[i].size();
				}
				for (int j=0;j<lng-1;j++){
					ofSetColor(color.r*ofRandom(0.5,1.5),color.g*ofRandom(0.5,1.5),color.b*ofRandom(0.5,1.5), 255*(1.0-(j/(float)lng))*((1.0-(ofGetElapsedTimef()-explodeStart)/explodeDuration)) );
					ofSetLineWidth(3.0*((1.0-(ofGetElapsedTimef()-explodeStart)/explodeDuration)));
					ofLine(particlePath[i][particlePath[i].size()-j-1].x, particlePath[i][particlePath[i].size()-j-1].y,particlePath[i][particlePath[i].size()-j-2].x, particlePath[i][particlePath[i].size()-j-2].y);
				}
			}
		}
	}
}
bool firework::updateExplode(){
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
		return 1;
	}
	else{
		return 0;
	}
	
}
