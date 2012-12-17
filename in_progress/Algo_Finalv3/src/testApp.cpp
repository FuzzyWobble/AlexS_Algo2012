#include "testApp.h"
#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) { 
	return a->pos.x < b->pos.x; 
}

//--------------------------------------------------------------
void testApp::setup(){
	
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    ofEnableSmoothing();
	//ofSetFrameRate(120);
	
	pCount = 0;
	
	for(int i=0;i<100;i++){
		myParticles[i].setInitialCondition(20, 20, 0, 0);
		myParticles[i].fixed = true;
		myParticles[i].following = false;
	}
    
}

//--------------------------------------------------------------
void testApp::update(){
	
	for(int i=0;i<100;i++){
		
		if(myParticles[i].fixed==false){
			
			//determine if particle has landed on line
			for(int j=0;j<lines.size();j++){ //all lines
				vector <ofPoint> linePoint = lines[i].getVertices();
				for(int k=0;k<linePoint.size();k++){ //all point for lines
					if(ofDist(linePoint[i].x,linePoint[i].y,myParticles[i].pos.x,myParticles[i].pos.y)<20){
						myParticles[i].following = true;
						myParticles[i].lineIndex = j;
						myParticles[i].linePtIndex = k;
						myParticles[i].pct = 0;
						break;
					}
				}
			}
			
		}
	}
	
	for(int i=0;i<100;i++){
		if(myParticles[i].fixed==false){
			myParticles[i].resetForce();
			if(myParticles[i].following == false){
				myParticles[i].addForce(0,0.15);
			}else{
				setPositionForLine(i,myParticles[i].lineIndex,myParticles[i].linePtIndex);	
			}
			myParticles[i].addDampingForce();
			myParticles[i].bounceOffWalls();
			myParticles[i].update();
		}
	}
	
}
//--------------------------------------------------------------
void testApp::setPositionForLine(int i, int lineIdx, int ptIdx){
	
	//calculate speed
	float speed;
	vector <ofPoint> linePoints = lines[lineIdx].getVertices();
	if(ptIdx<linePoints.size()){ //we are not at the end of the line
		float x1 = linePoints[ptIdx].x;
		float y1 = linePoints[ptIdx].y;
		float x2 = linePoints[ptIdx+1].x;
		float y2 = linePoints[ptIdx+1].y;
		float yy = y2-y1;
		float xx = x2-x1;
		speed = yy; //only gravity in the y direction 
		myParticles[i].pct += 0.01*(yy/10.0);
		myParticles[i].pos.x = (1-speed) * linePoints[ptIdx].x + (speed) * linePoints[ptIdx+1].x;
		myParticles[i].pos.y = (1-speed) * linePoints[ptIdx].y + (speed) * linePoints[ptIdx+1].y;
		if(ofDist(myParticles[i].pos.x,myParticles[i].pos.y,linePoints[ptIdx+1].x,linePoints[ptIdx+1].y)<1.0){
			myParticles[i].linePtIndex++;
			myParticles[i].pct = 0;
		}
	}else{ //end of line
		myParticles[i].following==false;
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(255);
	
	ofSetColor(150,150,150);
	
	ofNoFill();
	
	ofBeginShape();
	for(int i=0;i<currentPts.size();i++){
		ofVertex(currentPts[i].x, currentPts[i].y);
	}
	ofEndShape();
	
	//loop through all lines
	for(int i=0;i<lines.size();i++){
		lines[i].draw();
	}
	
	ofFill();
	for(int i=0;i<100;i++){
		if(myParticles[i].following==true){
			myParticles[i].draw(20);
		}
		else{
			myParticles[i].draw(10);	
		}
	}
	
	ofSetColor(50,50,50);
	for(int j=0;j<lines.size();j++){ //all lines
		vector <ofPoint> linePoint = lines[j].getVertices();
		for(int k=0;k<linePoint.size();k++){ //all point for lines
			ofCircle(linePoint[k].x,linePoint[k].y,3);
		}
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'd'){
		myParticles[pCount].fixed = false; //release the particle
		pCount++;
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
	ofPoint temp;
	temp.x = x;
	temp.y = y;
	currentPts.push_back(temp);	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofPoint temp;
	temp.x = x;
	temp.y = y;
	currentPts.push_back(temp);
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	ofPolyline p;
	p.addVertexes(currentPts);
	lines.push_back(p);
	currentPts.clear();
}
