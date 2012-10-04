/*
 *  line.h
 *  2_drawingWithTime_2
 *
 *  Created by Alex S on 10/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef TIME_POINT_RECORDER_H
#define TIME_POINT_RECORDER_H

#include "ofMain.h"
#include "timePoint.h"

class line {
	
	public:

	vector < timePoint > pts; 
	float startTime;
	float endTime;
	ofSoundPlayer sample;
	void loadSample(int count);
	bool isActive(float atTime);
	void draw();
	ofPoint getPosition(float atTime);
	ofPoint getVelocity(float atTime);
	
};

#endif