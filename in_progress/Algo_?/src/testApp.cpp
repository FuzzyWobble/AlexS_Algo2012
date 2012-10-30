#include "testApp.h"
#include "particle.h"

#include "ofMain.h"

// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) { 
	
	bool bool1 = a->pos.x < b->pos.x;
	bool bool2 = a->pos.y < b->pos.y;
	return bool1 && bool2; //true if a.x < b.x
	
	//return (a->pos.x < b->pos.x); //true if a.x < b.x
}  
bool comparisonFunction2(  particle * a, particle * b ) { 
	return a->pos.y < b->pos.y; 
}  
      

//--------------------------------------------------------------
void testApp::setup(){

    for (int i = 0; i < 6000; i++){
        particle * p = new particle();
        myParticles.push_back(p);
        myParticles[i]->pos.set(ofRandom(10,ofGetWidth()-10),ofRandom(10,ofGetHeight()-10));
        myParticles[i]->vel.set(0,0);
		
		//populate myParticles 2 pointer vector
		//myParticles2.push_back(p);
    }
	
	ofSetCircleResolution(6);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	mousePrev = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
	//cout << ofGetFrameRate() << endl;
	
	// sort all the particles in x pos
	sort( myParticles.begin(), myParticles.end(), comparisonFunction );               // sort them!
	
	
	
	ofBackground(0,0,0); //Grey background, NY style
	
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
	
	for (int i = 0; i < myParticles.size(); i++){
		for (int j = i-1; j >= 0; j--){ //why look backwards
			if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  10 ) break;
			myParticles[i]->addRepulsionForce(*myParticles[j],10,0.01f);
		}
    }
	
	
    for (int i = 0; i < myParticles.size(); i++){
		myParticles[i]->addRepulsionForce( mouseX,mouseY,50,1.7);
		myParticles[i]->addDampingForce();
        myParticles[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
//	for(int y=0;y<img.height;y++){
//		for(int x=0;x<img.width;x++){
//			ofSetColor(px[y*img.width+x]);
//			ofRect(x*6,y*6,6,6);
//		}
//	}
	
	ofSetColor(255,255,255);
	// then draw:
ofDrawBitmapString(ofToString(ofGetFrameRate()), 5,15);

	
	for (int i = 0; i < myParticles.size(); i++){
		 myParticles[i]->draw();
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
}
