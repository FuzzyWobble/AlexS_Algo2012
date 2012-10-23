#include "testApp.h"
#include "particle.h"

#include "ofMain.h"

// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) { 
	return a->pos.x < b->pos.x; 
}
      

//--------------------------------------------------------------
void testApp::setup(){

    for (int i = 0; i < 6000; i++){
        particle * p = new particle();
        myParticles.push_back(p);
        myParticles[i]->pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        myParticles[i]->vel.set(0,0);
    }
	
	ofSetCircleResolution(6);
	ofSetRectMode(OF_RECTMODE_CENTER);

	img.loadImage("face1.jpg");
	px = img.getPixels();
	
	//960x720
	camWidth 		= 320;	//x2 // try to grab at this size. 
	camHeight 		= 240;
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	//videoInverted 	= new unsigned char[camWidth*camHeight*3];
	//videoTexture.allocate(camWidth,camHeight, GL_RGB);	
}

//--------------------------------------------------------------
void testApp::update(){
	
	//cout << ofGetFrameRate() << endl;
	
	// sort all the particle
	sort( myParticles.begin(), myParticles.end(), comparisonFunction );      
	
	ofBackground(0,0,0); //Grey background, NY style
	
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
	
	for (int i = 0; i < myParticles.size(); i++){
		for (int j = i-1; j >= 0; j--){
			if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  10){
				//cout << "break x" << endl;
				break;
			}
			myParticles[i]->addRepulsionForce( *myParticles[j],10,1.1f);
		}
    }
	
	
    for (int i = 0; i < myParticles.size(); i++){
		myParticles[i]->addRepulsionForce( mouseX,mouseY,50,1.7);
		myParticles[i]->addDampingForce();
		myParticles[i]->bounceOffWalls();
        myParticles[i]->update();
	}
	
	vidGrabber.grabFrame();
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		pixels = vidGrabber.getPixels();
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	//vidGrabber.draw(200,200,camWidth,camHeight);
	
	for (int i = 0; i < myParticles.size(); i++){
		int cx,cy;
		cx = myParticles[i]->pos.x/2.0;
		cy = myParticles[i]->pos.y/2.0;
		int ref1 = (cy*camWidth+cx)*3;
		int ref2 = ref1+1;
		int ref3 = ref1+2;
		ofSetColor((float)pixels[ref1],(float)pixels[ref2],(float)pixels[ref3]);
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
