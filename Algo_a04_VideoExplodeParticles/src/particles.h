#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class particle
{
public:
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
	
	particle();
	
	void resetForce();
	void addForce(float x, float y);
	void addDampingForce();
	void setInitialCondition(float px, float py, float vx, float vy);
	void xenoToPoint(float catchX, float catchY, float spd);
	void update();
	void draw(int num, int sz, int width, int height, unsigned char * pixels);
	
	ofPoint home;
	
	int topLeftIndex;
	
	float damping;
	
protected:
private:
};

#endif // PARTICLE_H
