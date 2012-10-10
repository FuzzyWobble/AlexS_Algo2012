#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(255,255,255);
	
	bExplode = false;

	leMovie.loadMovie("movies/brian320.mov"); //small video
	//leMovie.loadMovie("movies/brian.mov"); //large video
	
	leMovie.setSpeed(1.2);

	
	//setup tiles ----------------------------------------
	
	tileSize = 20; //width and height of each tile
	int gridX = (int)(leMovie.width/(float)tileSize);
	int gridY = (int)(leMovie.height/(float)tileSize);
	
	float offsetX = (ofGetWidth()/2.0)-(leMovie.width/2.0);
	float offsetY = (ofGetHeight()/2.0)-(leMovie.height/2.0);
	
	for(int y=0;y<gridY;y++){ 
		for(int x=0;x<gridX;x++){ 

			particle aTile;
			aTile.pos.set(0,0);
			aTile.topLeftIndex = (y*tileSize*tileSize*gridX)+(x*tileSize); 
			aTile.home.set((x*tileSize)+offsetX,(y*tileSize)+offsetY);
			tiles.push_back(aTile); 
			
		}
	}
	
	leMovie.play();
	moviePixels = leMovie.getPixels();
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	if( leMovie.isFrameNew() && leMovie.isPlaying() ){
		
		moviePixels = leMovie.getPixels();
		
	}
	
	if(bExplode){
		for(int i=0;i<tiles.size();i++){
			tiles[i].resetForce();
			tiles[i].addForce(0,0.05); //gravity
			tiles[i].addDampingForce();
			tiles[i].update();	
			float half = tileSize/2.0;

			if(tiles[i].pos.x+tileSize >= ofGetWidth()){
				tiles[i].vel.x = -tiles[i].vel.x;
				tiles[i].pos.x = ofGetWidth()-tileSize;
			}
			if(tiles[i].pos.y+tileSize >= ofGetHeight()){
				tiles[i].vel.y = -tiles[i].vel.y;
				tiles[i].pos.y = ofGetHeight()-tileSize;
			}
			if(tiles[i].pos.x <= 0){
				tiles[i].vel.x = -tiles[i].vel.x;
				tiles[i].pos.x = 0;
			}
			if(tiles[i].pos.y <= 0){
				tiles[i].vel.y = -tiles[i].vel.y;
				tiles[i].pos.y = 0;
			}
			
		}
		
	}
	else{
		for(int i=0;i<tiles.size();i++){	
			tiles[i].xenoToPoint(tiles[i].home.x,tiles[i].home.y,0.1);
		}
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	for(int i=0;i<tiles.size();i++){
		tiles[i].draw(i, tileSize, leMovie.width, leMovie.height, moviePixels);	
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	bExplode = !bExplode;
	
	if(bExplode){
		for(int i=0;i<tiles.size();i++){
			float vx = ofRandom(-5,5);
			float vy = ofRandom(-5,5);
			tiles[i].vel.x = vx;
			tiles[i].vel.y = vy;
		}
	}
	else{
		for(int i=0;i<tiles.size();i++){
			tiles[i].vel.x = 0;
			tiles[i].vel.y = 0;
		}
	}
	
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
