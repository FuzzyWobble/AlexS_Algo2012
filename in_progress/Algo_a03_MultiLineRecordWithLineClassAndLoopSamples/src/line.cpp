///*
// *  line.cpp
// *  2_drawingWithTime_2
// *
// *  Created by Alex S on 10/2/12.
// *  Copyright 2012 __MyCompanyName__. All rights reserved.
// *
// */

#include "line.h"

//--------------------------------------------------------------
void line::draw(){
	ofNoFill();
	ofBeginShape();
	for(int p=0;p<pts.size();p++){ //loop through points
		ofVertex(pts[p].x, pts[p].y);
	}
	ofEndShape();
}

//--------------------------------------------------------------
ofPoint line::getPosition(float atTime){ //give it a time, and it will return position
	
	ofPoint pos;
	
	for (int i = 0; i < pts.size(); i++){ //loop through all points for this line
		if (atTime >= pts[i].t && atTime < pts[i+1].t){ //determine which segment of the line we are currently on
			
			float part = atTime - pts[i].t;
			float whole = pts[i+1].t - pts[i].t;
			float pct = part / whole;
			
			pos.x = (1-pct) * pts[i].x + (pct) * pts[i+1].x;
			pos.y = (1-pct) * pts[i].y + (pct) * pts[i+1].y;
			
			return pos;
		}
	}
	
}

//-------------------------------------------------
ofPoint	line::getVelocity(float atTime){ //give it a time, and it will return a velocity
	
	ofPoint currPos;
	currPos = getPosition(atTime);
	
	ofPoint prevPos;
	float prevTime = atTime - 0.05;
	if(prevTime<0){
		prevTime = 8.0 - prevTime;
	}
	prevPos = getPosition(prevTime);
	
	ofPoint diff;
	diff.x = currPos.x - prevPos.x;
	diff.y = currPos.y - prevPos.y;
	
	return diff;
}

//-------------------------------------------------
void line::loadSample(int count){
	sample.loadSound(ofToString(count)+".wav");
	sample.setVolume(0);
	sample.setLoop(true);
	sample.play();
}

//-------------------------------------------------
bool line::isActive(float atTime){
	if(   (  (endTime < startTime) && ((atTime > startTime) || (atTime < endTime ))  ) || (  (atTime > startTime) && (atTime < endTime)  )   ){
		return true;
	}
	else{
		return false;
	}
}