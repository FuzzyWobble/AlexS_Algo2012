#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "particle.h"
#include "ofxUI.h"

class testApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void drawPointCloud();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	ofxKinect kinect;

	ofxCvColorImage colorImg;
	
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	
	ofxCvContourFinder contourFinder;
	
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
	
	float nearMm, farMm; //threshold in mm
	float nearThreshold, farThreshold;
	
	int angle;

	ofEasyCam easyCam;
	
	int stepA, stepB;
	
	//smooth the contour
	void smoothContour();
	vector<ofPolyline> c_original;
	vector<ofPolyline> c_smooth;
	bool drawContour;
	
	vector<ofPoint> bodyPoints;
	
	int particleCount;
	int newParticleCount;
	float particleDamping;
	float newParticleDamping;
	float particleScale;
	float ppRepulsion,pbAttraction,pcAttraction;
	vector <particle *> particles;
	
	//unsigned char* depthPix[640*480];
	
	long updateKinectTimer;
	int updateKinectDuration;
	
	//gui
	bool hideGUI; 
	void setGUI();
	ofxUICanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
	float *buffer; 
    ofImage *img; 
	float red, green, blue; 
	
	int brightnessVal;
	
	float rippleX;
	
	long explodeTimer;
	bool trip;
};
