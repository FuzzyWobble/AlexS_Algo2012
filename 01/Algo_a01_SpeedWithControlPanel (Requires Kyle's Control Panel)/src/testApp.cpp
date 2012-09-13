#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	//ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetCircleResolution(100);
	//ofSetRectMode(CENTER);
	
	panel.setup("control", 770, 0, 300, 200);				//Name of your panel
	panel.addPanel("speed", 1, false);						//Name of each section. Number of columns. Locked?
	panel.addPanel("geometry", 1, false);
	panel.addPanel("cpu_settings", 1, false);
	
	panel.setWhichPanel("speed");							//Which panel would we like to manipulate
	panel.addSlider("pos_inc", "VAL_pos", 0.1,0.001,100, false);		
	
	panel.setWhichPanel("geometry");						//Which panel would we like to manipulate
	panel.addToggle("rect", "VAL_rect", true);
	panel.addSlider("size", "VAL_size", 15.0,5.0,30.0, false); 
	
	panel.setWhichPanel("cpu_settings");
	panel.addSlider("pixels_per_cm_of_your_display", "VAL_ppcm", 50.0,35.0,120.0, false);
	//http://en.wikipedia.org/wiki/List_of_displays_by_pixel_density - mine is 43
	
	panel.loadSettings("settings.xml");						//Load settings from xml
	
	xpos=0.0;
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(xpos>ofGetWidth()){
		xpos = 0.0;	
		xpos_start = 0.0;
		dist_timer = ofGetElapsedTimeMillis();
	}
	else{
		xpos += panel.getValueF("VAL_pos");	
	}
	panel.update();											//Update panel every frame
	cout << xpos << endl;
	
	
	if(xpos-xpos_start>100){
		xpos_start = xpos; //reset
		float one_hundred_pix_per_seconds = 100.0*1000.0/(ofGetElapsedTimeMillis()-dist_timer);
		calc_cm_per_sec = (1/panel.getValueF("VAL_ppcm"))*one_hundred_pix_per_seconds;
		dist_timer = ofGetElapsedTimeMillis();//reset timer
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableAlphaBlending();
	ofSetColor(250);
	if (panel.getValueB("VAL_rect")){
		ofRect(xpos,ofGetHeight()/2.0,panel.getValueF("VAL_size"),panel.getValueF("VAL_size"));
	} else {
		ofCircle(xpos,ofGetHeight()/2.0,panel.getValueF("VAL_size"));
	}
	
	panel.draw();
	
	//maths stuffs
	float cm_per_s = 60*(1/panel.getValueF("VAL_ppcm"))*panel.getValueF("VAL_pos");
	
	ofDrawBitmapString("CENTIMETERS/SECOND -> measured value: "+ofToString(calc_cm_per_sec)+", theoretical value: "+ofToString(cm_per_s),5,15);
	
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
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}