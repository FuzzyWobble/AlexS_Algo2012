#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"


class particle
{
    public:
        ofVec2f pos;
		ofVec2f posOrigin;
        ofVec2f vel;
        ofVec2f frc;   
		
		unsigned int bitFlagW;
		unsigned int bitFlagH;
	
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		bool addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw(float sz);
	
		void bounceOffWalls();
		void xenoToPoint(float spd);
	
		float damping;

		void trailUpdate();
		vector <ofPoint> trail;
		int trailSize;

    protected:
    private:
};

#endif // PARTICLE_H
