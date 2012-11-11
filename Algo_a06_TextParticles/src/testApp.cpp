#include "testApp.h"
#include "ofMain.h"
#include "particle.h"

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
    
    font.loadFont("verdana.ttf", 80, true, true, true);
    
    string text = "FuzzyWobbleDotCom";
    
    vector<ofTTFCharacter> letters = font.getStringAsPoints(text); //extract letters

    for(int i = 0; i < letters.size(); i++){ //letter of each word
        
		vector<ofPolyline> letterOutLine = letters[i].getOutline();
		
        for (int j = 0; j < letterOutLine.size(); j++ ){ //polyline of each letter

			//smooth and resample?
            letterOutLine[j].simplify();
            letterOutLine[j].getResampledByCount(2000);
			letterOutLine[j].close();
			letterLines.push_back(letterOutLine[j]);
        }
    }
	
	stringWidth = font.getStringBoundingBox(text, 0, 0).width; //bounding box
	
	//let's correct the position now
	for(int i = 0; i < letterLines.size(); i++){ 
		vector<ofPoint> linePts = letterLines[i].getVertices();
		for(int j=0;j<linePts.size();j++){
			linePts[j].x += ofGetWidth()*0.5-stringWidth*0.5;
			linePts[j].y += ofGetHeight()*0.5+20;
		}
		ofPolyline tempPoly;
		tempPoly.addVertexes(linePts);
		tempPoly.close();
		letterLinesAdj.push_back(tempPoly);
	}
	
	cout << "LetterLinesAdjSize:" << letterLinesAdj.size() << endl;
	
	int step = 5;
	for(int i = 0; i < letterLinesAdj.size(); i++){ //letter of each word
		for(int y=0;y<ofGetHeight();y=y+step){
			for(int x=0;x<ofGetWidth();x=x+step){
				if(letterLinesAdj[i].inside(x,y)){
					particle * p = new particle();
					myParticles.push_back(p);
					myParticles[i]->pos.set(x,y);
					myParticles[i]->vel.set(0,0);
				}
			}
		}
	}
    
	cout << "ParticlesSize:" << myParticles.size() << endl;

	ofSetLineWidth(1);
	
    //ofSetFullscreen(true);
	
	ofBackground(0);
	
}

//--------------------------------------------------------------
void testApp::update(){
    
	//sort( myParticles.begin(), myParticles.end(), comparisonFunction );      
	
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
	
	for (int i = 0; i < myParticles.size(); i++){
		for (int j = i-1; j >= 0; j--){
//			if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  10){
//				break;
//			}
			myParticles[i]->addRepulsionForce( *myParticles[j],10,0.1f);
		}
    }
	
    for (int i = 0; i < myParticles.size(); i++){
		myParticles[i]->addRepulsionForce(mouseX,mouseY,50,1.7);
		myParticles[i]->addDampingForce();
		myParticles[i]->bounceOffWalls();
        myParticles[i]->update();
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);
	

	
	for (int j = 0; j < letterLinesAdj.size(); j++ ){ //polyline of each letter
		ofSetColor(100,100,100);
		letterLinesAdj[j].draw();
	}
	for (int i = 0; i < myParticles.size(); i++){
		ofSetColor(200,200,200);
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
