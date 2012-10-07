#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofBackground(0);

	
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < fireworks.size(); i++){
		
		if(fireworks[i].streakY < fireworks[i].explodeHeight && fireworks[i].bExploding == false){
			fireworks[i].bExploding = true;
			fireworks[i].explode();
		}
		
		if(fireworks[i].bExploding){
			bool alive = fireworks[i].updateExplode();
			if(alive){
				
			}
			else{
				fireworks.erase(fireworks.begin()+i,fireworks.begin()+i+1);
			}
		}
		else{ //streak
			fireworks[i].updateStreak();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	for (int i = 0; i < fireworks.size(); i++){
		if(fireworks[i].bExploding){
			fireworks[i].drawExplode();
		}
		else{ //streak
			fireworks[i].drawStreak();
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
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	firework aFirework;
	aFirework.init();
	fireworks.push_back(aFirework);
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
