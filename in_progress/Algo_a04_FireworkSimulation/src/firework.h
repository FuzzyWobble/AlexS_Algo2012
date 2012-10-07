/*
 *  firework.h
 *  multiParticles
 *
 *  Created by Alex S on 10/7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FIREWORK_H
#define FIREWORK_H

#include "ofMain.h"
#include "particle.h"

class firework{
public: 
	bool bExploding;
	int numParticles;
	float explodeVelocity;
	vector <particle> particles;
	vector <ofPoint> streak;
	vector < vector < ofPoint > > particlePath;
	float streakX, streakY, streakVX, streakVY, curveX;
	int streakLength;
	int explodeHeight;
	float explodeDuration, explodeStart;
	ofColor color;
	void init();
	void drawStreak(); 
	void updateStreak();
	void explode();
	void drawExplode(); 
	bool updateExplode();
};

#endif 
