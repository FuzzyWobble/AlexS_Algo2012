#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255, 255, 255);
	bRecording = false;
	zero = 0.0;
	loopDuration = 4.0;
	
	currentSound.loadSound("drawbar_c4_a.aif");
	currentSound.setVolume(0);
	currentSound.setLoop(true);
	currentSound.play();

}


//--------------------------------------------------------------
void testApp::update(){

	//basic eight second counter;
	if(ofGetElapsedTimef() - zero > loopDuration){
		zero = ofGetElapsedTimef();
	}
	duration = ofGetElapsedTimef() - zero;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//duration output
	ofSetColor(0);
	ofDrawBitmapString("loops every four seconds, timer:"+ofToString(duration), 5,15);
	
	if(bRecording){ //draw current line
		ofNoFill();
		ofBeginShape();
		for(int i=0;i<currentPts.size();i++){
			ofVertex(currentPts[i].x, currentPts[i].y);
		}
		ofEndShape();
		float pitch = ofMap(currentPts[currentPts.size()-1].y, 0, (float)ofGetHeight(), 2.5, 0.1);
		currentSound.setSpeed(pitch);
		currentSound.setVolume(0.6); //hmm, this is difficult to make variable with the way i set up the code. need to fix this.
	}
	else{
		currentSound.setVolume(0);
	}
	
	for(int i=0;i<lines.size();i++){ //loop through all recorded lines
		
		bool lineIsActive = false;
		//okay this is IF statement is ugly
		//problem is - we have two cases
		//case 1: our line occurs at some point between zero and 'loopDuartion'
		//case 2: out line occurs while 'loopDuration' is reset to zero
		//this IF statment ensures our current time is an active playback time for the line
		if(   (  (lines[i][lines[i].size()-1].t < lines[i][0].t) && ((duration > lines[i][0].t) || (duration < lines[i][lines[i].size()-1].t))  ) || (  (duration > lines[i][0].t) && (duration < lines[i][lines[i].size()-1].t)  )   ){
			lineIsActive = true;
		}
		
		if(lineIsActive){
			ofSetColor(0);
		}
		else{
			ofSetColor(200);
		}
		
		ofNoFill();
		ofBeginShape();
		for (int j=0;j<lines[i].size();j++){ //loop through all points for each line
			if(j==0){
				ofDrawBitmapString(ofToString(lines[i][j].t), lines[i][j].x+5, lines[i][j].y+5);
			}
			if(j==lines[i].size()-1){
				ofDrawBitmapString(ofToString(lines[i][j].t), lines[i][j].x+5, lines[i][j].y+5);
			}
			ofVertex(lines[i][j].x, lines[i][j].y);
		}
		ofEndShape();
		
		ofFill();
		if(lineIsActive){
			ofSetColor(0);
			ofPoint pos = getPosition(i,duration); //get our playback position
			ofPoint vel = getVelocity(i);
			float velVal = (ofDist(0,0,vel.x,vel.y)/10.0);
			
			ofCircle(pos.x, pos.y, 5.0);
			
			//y positions effect pitch
			if(pos.y>0){ //was getting some weird beeping, maybe this IF will fix it?
				float pitch = ofMap(pos.y, 0, (float)ofGetHeight(), 2.5, 0.1);
				samples[i].setSpeed(pitch);
			}
			
			//velocity effects volume
			float soundVolume = ofMap(velVal,0,15,0,1);
			samples[i].setVolume(soundVolume);
		}
		else{
			ofSetColor(200);
			ofCircle(lines[i][0].x, lines[i][0].y, 3);
			samples[i].setVolume(0);
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
		currentPts.push_back(temp);
		
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
	currentPts.push_back(temp);
	
	//start our drag timer
	dragTimer = ofGetElapsedTimef();
	
	//load sample
	ofSoundPlayer ourSample;
	ourSample.loadSound("drawbar_c4_a.aif");
	ourSample.setVolume(0);
	ourSample.setLoop(true);
	ourSample.play();
	samples.push_back(ourSample);
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	bRecording = false;
	
	//add the line we just drew to the line vector
	lines.push_back(currentPts);
	
	//clear the current line
	currentPts.clear();
	 
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
ofPoint testApp::getPosition(int lineNum, float durationPass){
	
	ofPoint pos;
	
	for (int i = 0; i < lines[lineNum].size(); i++){ //loop through all points for this line
		if (durationPass >= lines[lineNum][i].t && durationPass < lines[lineNum][i+1].t){ //determine which segment of the line we are currently on
			
			// calculate pct: 
			
			float part = durationPass - lines[lineNum][i].t;
			float whole = lines[lineNum][i+1].t - lines[lineNum][i].t;
			float pct = part / whole;
			
			// figure out where we are between a and b
			
			pos.x = (1-pct) * lines[lineNum][i].x + (pct) * lines[lineNum][i+1].x;
			pos.y = (1-pct) * lines[lineNum][i].y + (pct) * lines[lineNum][i+1].y;
			
			return pos;
		}
	}
	
}
//-------------------------------------------------
ofPoint	testApp::getVelocity(int lineNum){
	
	ofPoint currPos;
	currPos = getPosition(lineNum, duration);
	
	ofPoint prevPos;
	float prevTime = duration - 0.05;
	if(prevTime<0){
		prevTime = 8.0 - prevTime;
	}
	prevPos = getPosition(lineNum, prevTime);
	
	ofPoint diff;
	diff.x = currPos.x - prevPos.x;
	diff.y = currPos.y - prevPos.y;
	
	return diff;
}


