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
	ofSetLineWidth(3);
	ofSetBackgroundAuto(false); 
	
	img.loadImage("phil.jpg");
	pix = img.getPixels();
    
//    font.loadFont("verdana.ttf", 130, true, true, true);
//    
//    string text = "FuzzyWobble";
//	
//	VF.setupField(20,20,ofGetWidth(), ofGetHeight());
//    
//    vector<ofTTFCharacter> letters = font.getStringAsPoints(text); //extract letters
//
//    for(int i = 0; i < letters.size(); i++){ //letter of each word
//        
//		vector<ofPolyline> letterOutLine = letters[i].getOutline();
//		
//        for (int j = 0; j < letterOutLine.size(); j++ ){ //polyline of each letter
//
//			//smooth and resample?
//            //letterOutLine[j].simplify();
//            //letterOutLine[j].getResampledByCount(2000);
//			//letterOutLine[j].close();
//			letterLines.push_back(letterOutLine[j]);
//        }
//    }
//	
//	stringWidth = font.getStringBoundingBox(text, 0, 0).width; //bounding box
//	stringHeight = font.getStringBoundingBox(text, 0, 0).height; //bounding box
//	
//	//let's correct the position now
//	for(int i = 0; i < letterLines.size(); i++){ 
//		vector<ofPoint> linePts = letterLines[i].getVertices();
//		for(int j=0;j<linePts.size();j++){
//			linePts[j].x += ofGetWidth()*0.5-stringWidth*0.5-20;
//			linePts[j].y += ofGetHeight()*0.5+stringHeight*0.5-25;
//			
//			
//		}
//		ofPolyline tempPoly;
//		tempPoly.addVertexes(linePts);
//		tempPoly.close();
//		letterLinesAdj.push_back(tempPoly);
//	}
//	
//	cout << "LetterLinesAdjSize:" << letterLinesAdj.size() << endl;
//	
//	int step = 5;
//	
//    for(int y=0;y<ofGetHeight();y=y+step){
//        for(int x=0;x<ofGetWidth();x=x+step){
//            for(int i = 0; i < letterLinesAdj.size(); i++){ //letter of each word
//                if(letterLinesAdj[i].inside(x,y)){
//					particle * p = new particle();
//                    p->pos.set(x,y);
//					p->posOrigin.set(x,y);
//                    p->vel.set(0,0);
//					myParticles.push_back(p);
//				}
//			}
//		}
//	}
//    
//	cout << "ParticlesSize:" << myParticles.size() << endl;
//	ofSetLineWidth(1);
//	ofBackground(0);
//	//ofSetFullscreen(true);
//	
//	mode=1;
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < myParticles.size(); i++){
		myParticles[i]->resetForce();
	}	


	sort(myParticles.begin(), myParticles.end(), comparisonFunction); //sort by x      
	for(int i = 0; i < myParticles.size(); i++){
		for(int j = i-1; j >= 0; j--){
			if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  5){ //tricky way to speed up this loop
				break;
			}
			myParticles[i]->addRepulsionForce( *myParticles[j],5,0.01f);	
		}
	}

	for (int i = 0; i < myParticles.size(); i++){
		myParticles[i]->addForce(ofRandom(-.1,.1),ofRandom(-.1,.1));
		myParticles[i]->addDampingForce();
		myParticles[i]->bounceOffWalls();
        myParticles[i]->update();
		
		
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(255);
	
//	ofSetColor(150,150,150);
//	ofDrawBitmapString("four modes, [1]MouseAttractWithXeno, [2]MouseAttactWithoutXeno, [3]ClickToEnableField, [4]Reset", 5,15);
//    
//	if(mode==3){
//		ofSetColor(220,0,0);
//		for(int i=0;i<hole.size();i++){
//			if(i==hole.size()-1){
//			if(hole[i].x!=0){
//				ofCircle(hole[i].x, hole[i].y, heldDuration[i]/20.0);
//			}			
//			}
//		}
//		//VF.draw();
//	}
	
	
	for(int y=0;y<img.height;y++){
		for(int x=0;x<img.width;x++){
			ofSetColor(pix[y*img.width+x]);
			ofRect(x,y,1,1);
		}
	}
	
	
	for(int i = 0; i < myParticles.size(); i++){
		ofFill();
		ofSetColor(0);
		myParticles[i]->draw();
		ofNoFill();
		ofBeginShape();
			for(int a=1;a<myParticles[i]->posHistory.size();a++){
				int ref = (int)(myParticles[i]->posHistory[a].y * img.width + myParticles[i]->posHistory[a].x);
				ofSetColor(pix[ref]);
				//ofLine(myParticles[i]->posHistory[a].x,myParticles[i]->posHistory[a].y,myParticles[i]->posHistory[a-1].x,myParticles[i]->posHistory[a-1].y);
				ofCurveVertex(myParticles[i]->posHistory[a].x,myParticles[i]->posHistory[a].y);
			}
		ofEndShape();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if(key == '1'){
		mode = 1;
		for (int i = 0; i < myParticles.size(); i++){
			myParticles[i]->damping = 0.03;
		}
	}
	if(key == '2'){
		mode = 2;
		for (int i = 0; i < myParticles.size(); i++){
			myParticles[i]->damping = 0.03;
		}
	}
	if(key == '3'){
		mode = 3;
		VF.clear();
		hole.clear();
		heldDuration.clear();
		for (int i = 0; i < myParticles.size(); i++){
			myParticles[i]->damping = 0.005;
		}
	}
	if(key == '4'){
		mode = 4;
		for (int i = 0; i < myParticles.size(); i++){
			myParticles[i]->damping = 0.07;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	holdTimer = ofGetElapsedTimeMillis();
	px = x;
	py = y;
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
	long heldFor = ofGetElapsedTimeMillis() - holdTimer;
	float distX = mouseX - px;
	float distY = mouseY - py;
	mouse_vx = distX/((float)heldFor*0.1);
	mouse_vy = distY/((float)heldFor*0.1);
	
	cout << "mouse vel: " << mouse_vx << "," << mouse_vy << endl;
	
	int pCount=ofRandom(5,50);
	
	for(int i=0;i<pCount;i++){
		particle * p = new particle();
		p->pos.set(px,py);
		p->vel.set(mouse_vx*ofRandom(0.8,1.2),mouse_vy*ofRandom(0.8,1.2));
		ofPoint tempPt;
		tempPt.set(mouseX,mouseY);
		p->posHistory.push_back(tempPt);
		myParticles.push_back(p);
	}
	
//	if(mode == 3){
//		heldDuration.push_back(ofGetElapsedTimeMillis()-holdTimer);
//		ofPoint pt;
//		pt.set(hit.x,hit.y);
//		hole.push_back(pt);
//		VF.clear();
//		VF.addInwardCircle(pt.x,pt.y,1200,(ofGetElapsedTimeMillis()-holdTimer)/200.0);
//	}
}
