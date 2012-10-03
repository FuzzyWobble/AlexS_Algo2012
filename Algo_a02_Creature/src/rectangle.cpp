#include "rectangle.h"


//------------------------------------------------------------------
rectangle::rectangle(){
	catchUpSpeed = 0.18f;
	

	pos.set(0,0);
	prevPos.set(0,0);
}

//------------------------------------------------------------------
void rectangle::draw(int num, float dist) {
	ofFill();
	float oscY,oscX;
	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position
    
	
	ofPushMatrix();
		ofTranslate(pos.x, pos.y, 0);
		ofRotateZ(angle * RAD_TO_DEG);
		oscY = sin(ofGetElapsedTimef()*4)*(num*2);
		oscX = sin(ofGetElapsedTimef()*4)*(num*1.5);
		ofSetColor(155,255,155,200-(num*8));
		ofRect(0+oscX,0+oscY,((25-num)/3.0)+1,55-num*2);
		ofRect(15+oscX,0+oscY,5,1);
		if(num==0){
			for(float c=0;c<PI;c+=0.2){
				ofCircle(35*cos(c-(PI/2.0))+10.0,35*sin(c-(PI/2.0)),3.0*sin(c));
			}
		}
	ofPopMatrix();
	
	
}

//------------------------------------------------------------------
void rectangle::xenoToPoint(float catchX, float catchY){
	
	//our xeno function
	pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x; 
	pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y; 

	//difference in position
	float dx = pos.x - prevPos.x;
	float dy = pos.y - prevPos.y;
	
	angle = atan2(dy, dx);

	//set our prev position
	prevPos.x = pos.x;
	prevPos.y = pos.y;
	

}
