#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	
	
	numCreatures = 1;
	
	for(int c=0;c<numCreatures;c++){
		
		//setup
		vector <particle> aCreature;
		vector <spring> aSpring;
		
		//center point
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(100,500),ofRandom(100,500),0,0);
		aCreature.push_back(myParticle);
		
		int size = ofRandom(40,80); //set size of creature
		
		//particles
		for (int i=0;i<size;i++){
			particle myParticle;
			float x = 100 + 150 * cos ( (i / 200.0) * TWO_PI);
			float y = 100 + 150 * sin ( (i / 200.0) * TWO_PI);
			myParticle.setInitialCondition(x,y,0,0);
			myParticle.trailSize = ofRandom(25,50); //random trail size
			aCreature.push_back(myParticle);
		}
		creatures.push_back(aCreature);
		//aCreature.erase();
		
		
		//springs
		for (int i=1;i<size+1;i++){ //skip zero
			spring mySpring;
			mySpring.distance = size/2.0;
			mySpring.springiness = ofRandom(0.005,0.01);
			mySpring.particleA = &(creatures[c][0]); //center pt
			mySpring.particleB = &(creatures[c][i]); //all other pts
			aSpring.push_back(mySpring);		
		}
		springs.push_back(aSpring);
		//aSpring.erase();
		
		//color of creature
		ofColor creatureColor;
		creatureColor.set(ofRandom(160,222),ofRandom(160,222),ofRandom(160,222));
		creaturesColor.push_back(creatureColor);
		
	}

}

//--------------------------------------------------------------
void testApp::update(){
	
	for(int c=0;c<numCreatures;c++){
		//reset force
		for(int i = 0; i < creatures[c].size(); i++){
			creatures[c][i].resetForce();
		}
		//repulsion from particles
		for(int i = 1; i < creatures[c].size(); i++){
			for (int j = 0; j < i; j++){
				creatures[c][i].addRepulsionForce(creatures[c][j], 100, 0.2);
			}
		}
		//repulsion from center pt
		for(int i = 0; i < creatures[c].size(); i++){
			//creatures[c][0].addRepulsionForce(creatures[c][i], 50, 0.7);
		}
		//update springs
		for(int i = 0; i < springs[c].size(); i++){
			springs[c][i].update();
		}
		
		//finalize
		for(int i = 0; i < creatures[c].size(); i++){
			creatures[c][i].bounceOffWalls();
			creatures[c][i].addDampingForce();
			creatures[c][i].addForce(sin(ofGetElapsedTimef()/2.5)*ofRandom(0.01,0.05),0.05);
			
			//update with sticky walls
			if(creatures[c][i].pos.x<5 && creatures[c][i].pos.x>-1){
				//cout << creatures[c][i].frc.x << endl;
				if(creatures[c][i].frc.x<3.0){
					creatures[c][i].pos.x = 1; //stuck to wall
				}
				else{
					creatures[c][i].update();
				}
			}
			else if(creatures[c][i].pos.x<ofGetWidth()+1 && creatures[c][i].pos.x>ofGetWidth()-5){
				//cout << creatures[c][i].frc.x << endl;
				if(creatures[c][i].frc.x>-1.5){
					creatures[c][i].pos.x = ofGetWidth()-1; //stuck to wall
				}
				else{
					creatures[c][i].update();
				}
			}
			else{
				creatures[c][i].update();
			}

		}
		
		//update trail
		for(int i = 0; i < creatures[c].size(); i++){
			creatures[c][i].trailUpdate();
		}

	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(100);
	ofDrawBitmapString("Creatures! Left wall is really sticky, right wall is moderately sticky", 5, 15);
	
	for(int c=0;c<numCreatures;c++){ //loop through creatures
		
		for (int i = 0; i < creatures[c].size(); i++){ //loop through particles
			
			float scl = 0.01 * (sin(ofGetElapsedTimef()/10.0)+0.1);
			
			float rr = 	creaturesColor[c].r * ofNoise(creatures[c][i].pos.x*scl,creatures[c][i].pos.y*scl,creatures[c][i].pos.y*scl);
			float gg = 	creaturesColor[c].g * ofNoise(creatures[c][i].pos.x*scl,creatures[c][i].pos.y*scl,creatures[c][i].pos.y*scl);
			float bb = 	creaturesColor[c].b * ofNoise(creatures[c][i].pos.x*scl,creatures[c][i].pos.y*scl,creatures[c][i].pos.y*scl);
			
													
			//particle size - dist from center
			float pSz = 10.0 - (ofDist(creatures[c][i].pos.x,creatures[c][i].pos.y,creatures[c][0].pos.x,creatures[c][0].pos.y) / 20.0);
			if(pSz<3){pSz=3;}
			if(pSz>10){pSz=10;}
							
			
			if(i>0){ //dont draw trail at center pr
				for (int j = 1; j < creatures[c][i].trail.size(); j++){
					ofSetColor(rr,gg,bb,((float)j/(float)creatures[c][i].trail.size())*100.0);
					ofSetLineWidth(((float)j/(float)creatures[c][i].trail.size())*pSz);
					ofLine(creatures[c][i].trail[j].x,creatures[c][i].trail[j].y,creatures[c][i].trail[j-1].x,creatures[c][i].trail[j-1].y);
				}	
			}
			
			ofSetLineWidth(1);
			if(i>0){ //one less spring										
				ofSetColor(rr,gg,bb,240);
				springs[c][i-1].draw();
			}
			
			if(i>0){ //dont draw particle at center pt
				for(int a=0;a<6;a++){ //concetric circles
					ofSetColor(rr,gg,bb,240-(a*20));
					float pSz2 = ofMap(pSz*a,0,50,1,12);
					creatures[c][i].draw(pSz2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if(dragEnabled==true){
		int xx = mouseX;
		int yy = mouseY;
		if(xx<30){
			xx=30;
		}
		if(xx>ofGetWidth()-30){
			xx=ofGetWidth()-30;
		}
		creatures[closest][0].pos.set(xx,yy);
	}
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	int dist = 10000;
	dragEnabled = false;
	
	for(int c=0;c<numCreatures;c++){
		int howFar = ofDist(mouseX,mouseY,creatures[c][0].pos.x,creatures[c][0].pos.y);
		if(howFar<dist){
			dist = howFar;
			closest = c;
		}
	}
	if(dist<50){ //we are close enough to the center
		dragEnabled = true;
		creatures[closest][0].bFixed = true;
	}
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
	if(dragEnabled==true){
		creatures[closest][0].bFixed = false;
	}
	
}

