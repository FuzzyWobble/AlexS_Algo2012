#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255, 255, 255);
	bRecording = false;
	zero = 0.0;
	loopDuration = 4.0;
	lineCount = 0;

}


//--------------------------------------------------------------
void testApp::update(){

	//basic eight second counter;
	if(ofGetElapsedTimef() - zero > loopDuration){
		zero = ofGetElapsedTimef();
	}
	duration = ofGetElapsedTimef() - zero;
	
	lineCount = lines.size()-1; 
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//duration output
	ofSetColor(0);
	ofDrawBitmapString("loops every four seconds, timer:"+ofToString(duration), 5,15);
	
	for(int i=0;i<lines.size();i++){ //loop through all recorded lines
		
		bool lineIsActive = lines[i].isActive(duration);

		if(lineIsActive){
			ofSetColor(0);
		}
		else{
			ofSetColor(200);
		}
		
		lines[i].draw();
		
		ofFill();
		
		if(lineIsActive){
			ofSetColor(0);
			ofPoint pos = lines[i].getPosition(duration); //get our playback position
			ofPoint vel = lines[i].getVelocity(duration);
			float velVal = (ofDist(0,0,vel.x,vel.y)/10.0);
			
			ofCircle(pos.x, pos.y, 5.0);

			//height effects pitch
			float pitch = ofMap(pos.y, 0, (float)ofGetHeight(), 2.5, 0.1);
			lines[i].sample.setSpeed(pitch);

			//velocity effects volume
			float soundVolume = ofMap(velVal,0,15,0,1);
			//lines[i].sample.setVolume(soundVolume);
			lines[i].sample.setVolume(0.75);
		}
		else{
			ofSetColor(200);
			ofCircle(lines[i].pts[0].x, lines[i].pts[0].y, 3);
			lines[i].sample.setVolume(0);
		}
		
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if(ofGetElapsedTimef() - dragTimer <= loopDuration){ //we should not record lines longer than an 8 second duration
		timePoint temp;
		temp.x = x;
		temp.y = y;
		temp.t = duration;
		lines[lineCount].pts.push_back(temp);
	}
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	bRecording = true;
	
	//add our first point
	timePoint temp;
	temp.x = x;
	temp.y = y;
	temp.t = duration;
	
	//start our drag timer
	dragTimer = ofGetElapsedTimef();
	
	//hmm this seems a bit odd
	//is there a better way to do this without creating myLine?...
	line myLine;
	myLine.startTime = duration;
	myLine.loadSample(lines.size()+1);
	myLine.pts.push_back(temp);
	lines.push_back(myLine);
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	bRecording = false;
	
	lines[lineCount].endTime = duration;
	 
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}



