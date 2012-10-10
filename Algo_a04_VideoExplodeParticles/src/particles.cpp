#include "particles.h"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.005f;
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void particle::update(){	
	vel = vel + frc;
	pos = pos + vel;
}

//------------------------------------------------------------
void particle::draw(int num, int sz, int width, int height, unsigned char * pixels){
	
	ofDrawBitmapString("click to explode, click again to xeno", 5, 15);
	int index;
	for(int j=0;j<sz;j++){
		for(int i=0;i<sz;i++){
			
			int refR = (topLeftIndex+(j*width+i))*3;
			int refG = refR+1;
			int refB = refR+2;
			unsigned char colR = pixels[refR];
			unsigned char colG = pixels[refG];
			unsigned char colB = pixels[refB];
			
			ofSetColor((float)colR, (float)colG, (float)colB);
			ofRect(pos.x+i,pos.y+j,1,1);

			index++;
			
		}
	}
	
}

void particle::xenoToPoint(float catchX, float catchY, float spd){
	
	pos.x = spd * catchX + (1-spd) * pos.x; 
	pos.y = spd * catchY + (1-spd) * pos.y;
	
}



