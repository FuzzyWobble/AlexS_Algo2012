#include "rectangle.h"


//------------------------------------------------------------------
rectangle::rectangle(){
	//catchUpSpeed = 0.08f;
}

//------------------------------------------------------------------
void rectangle::draw(float sz, float opc) {
	ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position
	ofSetColor(250*opc);
	ofCircle(pos.x, pos.y, sz);
}

//------------------------------------------------------------------
void rectangle::xenoToPoint(float catchX, float catchY, float spd){
	
	pos.x = spd * catchX + (1-spd) * pos.x; 
	pos.y = spd * catchY + (1-spd) * pos.y;
	
	// pos.x = spd * catchX + (1-spd) * pos.x; - Zachs equation
	// xeno math explianed
	// A------B--------------------C
	// A is beginning, C is end
	// say you wanna move .25 of the remaining dist each iteration
	// your first iteration you moved to B, wich is 0.25 of the distance between A and C
	// the next iteration you will move .25 the distance between B and C
	// let the next iteration be called 'new'
	// pos.new = pos.b + (pos.c-pos.b)*0.25
	// now let's simplify this equation
	// pos.new = pos.b(1-.25) + pos.c(.25)
	// since pos.new and pos.b are analogous to pos.x
	// and pos.c is analogous to catchX 
	// we can write pos.x = pos.x(1-.25) + catchX(.25) 
	// this equation is the same as Zachs simplified equation
	
}
