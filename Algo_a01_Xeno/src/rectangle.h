#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ofMain.h"

class rectangle {

	public:
	
        rectangle();
	
		void	draw(float sz, float opc);
		void	xenoToPoint(float catchX, float catchY, float spd);
	
		ofPoint		pos;
		float		catchUpSpeed;		// take this pct of where I want to be, and 1-catchUpSpeed of my pos

};

#endif // RECTANGLE_H
