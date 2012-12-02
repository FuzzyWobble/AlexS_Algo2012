#include "testApp.h"

/*
fuzzywobble.com 
kinect particle insanity
required 
-particle system (particle.cpp, particle.h)
-ofxKinect
-ofxOpenCv
-OfxXmlSettings
-ofxUI 
*/

//--------------------------------------------------------------
// comparison routine for sort...peeds up particles!
bool comparisonFunction(  particle * a, particle * b ) { 
	return a->pos.x < b->pos.x; 
}

//--------------------------------------------------------------
void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	kinect.setRegistration(true);
    ofEnableAlphaBlending();
	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	kinect.open(); // opens first available kinect
	
	//open CV stuff
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearMm = 500; //closest is 500mm?
	farMm = 1500; //max is 6000mm?
	
	bThreshWithOpenCV = true; //use openCV to subtract background
	
	ofSetFrameRate(60);
	
	angle = 0;
	kinect.setCameraTiltAngle(angle);
	
	// start from the front
	bDrawPointCloud = false;
	
	newParticleCount = 3000;
	newParticleDamping = 0.1;

	updateKinectDuration = 70;
	updateKinectTimer = 0;
	
	particleScale = 1.0;
	
	ppRepulsion = 0.1;
	pbAttraction = 0.06;
	pcAttraction = 0.05;
	
	stepA = 50;
	stepB = 10;
	
	drawContour = false;
	
	setGUI();
	gui->loadSettings("GUI/guiSettings.xml");
}

//--------------------------------------------------------------
void testApp::update() {
	
	ofBackground(20);
	
	if(newParticleCount!=particleCount){
		particles.clear();
		for(int i=0;i<newParticleCount;i++){
			particle * p = new particle();
			p->pos.set(ofRandom(20,620),ofRandom(20,460));
			//p->posOrigin.set(x,y);
			p->vel.set(0,0);
			p->trailSize = 30;
			particles.push_back(p);
		}	
		particleCount = newParticleCount;
	}
	if(newParticleDamping!=particleDamping){
		for(int i=0;i<newParticleCount;i++){
			particles[i]->damping = newParticleDamping;
		}
		newParticleDamping = particleDamping;
	}
	
	if(ofGetElapsedTimeMillis() - updateKinectTimer > updateKinectDuration){
		kinect.update();	
		updateKinectTimer = ofGetElapsedTimeMillis();
		
		if(kinect.isFrameNew()){
			
			grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);

			//nearThreshold = 255.0-((nearMm-500)/6000.0);
			//farThreshold = 255.0-((farMm-500)/6000.0);
			
			nearThreshold = 255;
			farThreshold = 200;
			
			if(bThreshWithOpenCV) {
				grayThreshNear = grayImage;
				grayThreshFar = grayImage;
				grayThreshNear.threshold(nearThreshold, true);
				grayThreshFar.threshold(farThreshold);
				cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
			} else {

				unsigned char * pix = grayImage.getPixels();
				
				int numPixels = grayImage.getWidth() * grayImage.getHeight();
				for(int i = 0; i < numPixels; i++) {
					if(pix[i] < nearThreshold && pix[i] > farThreshold) {
						pix[i] = 255;
					} else {
						pix[i] = 0;
					}
				}
			}

			grayImage.flagImageChanged();

			contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 5, true);
			
			smoothContour();			
		}
	}
	
	// particles update -----------------------------------------------------
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->resetForce();
	}
	
	//particle-to-contour ATTRACTION forces
	for(int i=0;i<c_smooth.size();i++){ //2
		vector<ofPoint> outlinePts = c_smooth[i].getVertices();
		for(int j=0;j<outlinePts.size();j++){ //?
			for (int k=0;k<particles.size();k++){ 
				particles[k]->addAttractionForce(outlinePts[j].x, outlinePts[j].y, 80, pcAttraction);			}
		}
	}
	
	//particle-to-body ATTRACTION forces
	//find body points (points inside body)
	bodyPoints.clear();
	for(int i=0;i<c_smooth.size();i++){ //loop through all blobs
		ofRectangle tempRect = c_smooth[i].getBoundingBox();
		int step = stepA;
		for(int y=tempRect.y;y<tempRect.y+tempRect.height;y=y+step){
			for(int x=tempRect.x;x<tempRect.x+tempRect.width;x=x+step){	
				if(kinect.getDistanceAt(x,y) < 1500){
					step = stepB;
					ofPoint temp;
					temp.set(x,y);
					bodyPoints.push_back(temp);					
				}
				else{
					step = stepA;
				}
			}
			step = stepA;
		}
	}
	for (int i=0;i<particles.size();i++){
		for(int j=0;j<bodyPoints.size();j++){
			particles[i]->addAttractionForce(bodyPoints[j].x,bodyPoints[j].y,120,pbAttraction);	
		}
	}
	
	//particle-to-particle REPULSION forces
	sort( particles.begin(), particles.end(), comparisonFunction ); //sort by x      
	for (int i = 0; i < particles.size(); i++){
		for (int j = i-1; j >= 0; j--){
			if ( fabs(particles[j]->pos.x - particles[i]->pos.x) >  30){ //tricky way to speed up this loop
				break;
			}
			particles[i]->addRepulsionForce(*particles[j],30,ppRepulsion);
		}
	}	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->addForce(0,0.05);
		particles[i]->trailUpdate();
		particles[i]->addDampingForce();
		particles[i]->bounceOffWalls();
		particles[i]->update();
	}	
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetColor(255, 255, 255);
	
	if(bDrawPointCloud) {
		easyCam.begin();
		drawPointCloud();
		easyCam.end();
	} else {

		//kinect.drawDepth(10, 10, 400, 300);
		//kinect.draw(420, 10, 400, 300);
		//grayImage.draw(10, 320, 400, 300);
		//ofSetColor(50,50,50);
		//grayImage.draw(0, 0, 640, 480);
		//ofSetColor(255);
		//contourFinder.draw(0, 0, 640, 480);
		
		ofSetColor(220);
		
		//draw particles
		for (int i=0;i<particles.size();i++){
			ofColor col = kinect.getColorAt(particles[i]->pos.x, particles[i]->pos.y);
			int dist = kinect.getDistanceAt(particles[i]->pos.x,particles[i]->pos.y);
			float particleSize = (particles[i]->vel.length()*particleScale) + 1.0;
			int alpha = ofMap(dist,400,3000,255,0,true);
			col.setBrightness(brightnessVal); 
			//trippy colours
			//draw streak
			for(int j=1;j<particles[i]->trailSize;j++){
				ofSetLineWidth(((float)j/(float)particles[i]->trail.size())*particleSize);
				ofSetColor(col.r,col.g,col.b,(alpha-100)*((float)j/(float)particles[i]->trail.size()));
				ofLine(particles[i]->trail[j].x,particles[i]->trail[j].y,particles[i]->trail[j-1].x,particles[i]->trail[j-1].y);
			}
			//draw particle
			ofSetColor(col.r,col.g,col.b,alpha);
			particles[i]->draw(particleSize);
		}
		
		
		//draw contours 
		ofSetColor(200,200,200);
		if(drawContour==true){
			contourFinder.draw(0, 0, 640, 480);
			ofSetLineWidth(2);
			for(int i=0;i<c_smooth.size();i++){
				c_smooth[i].draw();
				vector<ofPoint> outlinePts = c_smooth[i].getVertices();
				for(int j=0;j<outlinePts.size();j++){ 
					ofRect(outlinePts[j].x,outlinePts[j].y,5,5);
				}
			}
			for(int i=0;i<bodyPoints.size();i++){
				ofRect(bodyPoints[i].x,bodyPoints[i].y,5,5);
			}
			ofSetLineWidth(1);
		}
		
	}
	
	// fps
	if(hideGUI==false){
		ofSetColor(120,120,120);
		ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate())+", [p]oint cloud, [h]ide GUI, view [c]ontours", 7,15);
	}
}

void testApp::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards' 
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	glEnable(GL_DEPTH_TEST);
	mesh.drawVertices();
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}
//--------------------------------------------------------------
void testApp::smoothContour(){
	
	c_original.clear();
	c_smooth.clear();
	vector<ofxCvBlob>& blobs = contourFinder.blobs;  
	
	for(int i=0;i<blobs.size();i++){
		ofPolyline temp;
		temp.addVertexes(blobs[i].pts);
		c_original.push_back(temp);
	}
	for(int i=0;i<c_original.size();i++){
		ofPolyline temp2 = c_original[i].getResampledBySpacing(30);
		//temp2.simplify(0.9);
		temp2.close(); 
		c_smooth.push_back(temp2);
	}
}



//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	gui->saveSettings("GUI/guiSettings.xml");
	delete gui; 
	delete[] buffer; 
    //delete img; 
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		case'p':
			bDrawPointCloud = !bDrawPointCloud;
			break;
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case 'h':
            gui->toggleVisible();
			break;
			
		case 'c':
            drawContour =! drawContour;
			break;
	}
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){
	
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 	
	
	if(name == "UPDATE-KINECT-MILLIS"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		updateKinectDuration = slider->getScaledValue(); 
	}else if(name == "PARTICLE-DAMPING"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		newParticleDamping = slider->getScaledValue(); 
	}else if(name == "PARTICLE-SCALE"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		particleScale = slider->getScaledValue(); 		
	}else if(name == "PARTICLE-COUNT"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		newParticleCount = slider->getScaledValue(); 	
	}else if(name == "PARTICLE-PARTICLE-REPULSION"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		ppRepulsion = slider->getScaledValue();
	}else if(name == "PARTICLE-BODY-ATTRACTION"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		pbAttraction = slider->getScaledValue(); 
	}else if(name == "PARTICLE-CONTOUR-ATTRACTION"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		pcAttraction = slider->getScaledValue(); 
	}else if(name == "STEP-A"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		stepA = slider->getScaledValue(); 
	}else if(name == "STEP-B"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		stepB = slider->getScaledValue(); 
	}else if(name == "BRIGHTNESS"){
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		brightnessVal = slider->getScaledValue(); 
	}else{
		//do nothing
	}
}	

//--------------------------------------------------------------
void testApp::setGUI(){
	
	float dim = 12; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	hideGUI = false; 	
	
	gui = new ofxUICanvas(0, 20, length+xInit, ofGetHeight()); 
	gui->addWidgetDown(new ofxUILabel("Kinect Particles GUI", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUILabel("'h' to hide", OFX_UI_FONT_SMALL)); 
	gui->addSpacer(length-xInit, 2);
	gui->addSlider("UPDATE-KINECT-MILLIS", 20, 200, updateKinectDuration, length-xInit,dim);
	gui->addSlider("PARTICLE-DAMPING", 0.01, 0.2, newParticleDamping, length-xInit,dim); 
	gui->addSlider("PARTICLE-SCALE", 0.5, 2.0, particleScale, length-xInit,dim);
	gui->addSlider("PARTICLE-COUNT", 500, 5000, newParticleCount, length-xInit,dim);
	gui->addSlider("PARTICLE-PARTICLE-REPULSION", 0.05, 0.3, ppRepulsion, length-xInit,dim);
	gui->addSlider("PARTICLE-BODY-ATTRACTION", 0.01, 0.2, pbAttraction, length-xInit,dim);
	gui->addSlider("PARTICLE-CONTOUR-ATTRACTION", 0.01, 0.2, pcAttraction, length-xInit,dim);
	gui->addSlider("STEP-A", 20, 100, stepA, length-xInit,dim);
	gui->addSlider("STEP-B", 5, 30, stepB, length-xInit,dim);
	gui->addSlider("BRIGHTNESS", 100, 250, brightnessVal, length-xInit,dim);
 	
	ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}
