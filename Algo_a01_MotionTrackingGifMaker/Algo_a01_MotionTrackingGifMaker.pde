/*
requires - http://www.extrapixel.ch/processing/gifAnimation/

click with the mouse to add tracking points
use the right and left arrow to move through the animation frame-by-frame
press 'd' to delete the tracking point in the current frame
press 'a' to begin creating your animation - each time you move to your next frame (right arrow) that frame is added to the gif animation
press 's' to export your animation
*/

import gifAnimation.*;
import processing.opengl.*;

Gif yourGif;
GifMaker gifExport;
PImage[] animationFrames;
PVector[] trackingPoints;

int currentFrame;
int totalFrames;

boolean startCreatingGif = false;
boolean drawCircles = true;

public void setup() {
  yourGif = new Gif(this, "robot_dance.gif"); 
  animationFrames = Gif.getPImages(this, "robot_dance.gif");
  
  gifExport = new GifMaker(this, "export.gif");
  gifExport.setRepeat(0); // make it an "endless" animation
  //gifExport.setTransparent(255); // every white pixel will be transparent?
  
  trackingPoints = new PVector[animationFrames.length];
  
  size(animationFrames[0].width, animationFrames[0].height);
  currentFrame = 0;
  totalFrames = animationFrames.length;
  
  //frameRate(100);
  //fill(241,96,233,100);
  //stroke(241,96,233,100);
  //strokeWeight(5);
}

void draw() {
  background(0);
  image(animationFrames[currentFrame],0,0);
  
    if(trackingPoints[currentFrame] != null){ //point was set
      if(drawCircles == true){
        //ellipse(trackingPoints[currentFrame].x, trackingPoints[currentFrame].y,5,5);
      }
      int lineCount = 0;
      for(int j=currentFrame;j>=currentFrame-9;j--){
        if(j-1>=0){
          int opac = int((1.0-(lineCount/9.0))*250.0);
          stroke(241,96,233,opac);
          strokeWeight(9-lineCount);
          if(trackingPoints[j-1] != null && trackingPoints[j] != null){
            line(trackingPoints[j].x,trackingPoints[j].y,trackingPoints[j-1].x,trackingPoints[j-1].y);
          }
        }
      lineCount++;  
      }
    }
  
}

void mousePressed(){
  trackingPoints[currentFrame] = new PVector(mouseX, mouseY);
}

void keyPressed(){
  if(key == CODED){
    if(keyCode == RIGHT){
      if(currentFrame==totalFrames-1){
        currentFrame = 0; 
      }
      else{
        currentFrame++;
        println("frame "+currentFrame+" of "+(totalFrames-1));
        if(startCreatingGif == true){
          gifExport.setDelay(1); //damn what if you wanna go faster! 
          gifExport.addFrame();  
        }
      }
    }
    if(keyCode == LEFT){ 
      if(currentFrame==0){
        currentFrame = totalFrames-1;  
      }
      else{
        currentFrame--; 
        println("frame "+currentFrame+" of "+(totalFrames-1)); 
      }
    }
  }
  if(key == 'd'){
    trackingPoints[currentFrame] = null;
    println("point deleted"); 
  }
  if(key == 's'){ 
    gifExport.setQuality(100);
    gifExport.finish(); 
    println("GIF saved"); 
  }
  if(key == 'a'){
    if(startCreatingGif == false){
      println("Create gif turned on. It cannot be turned off. Every time you click the right arrow, a new frame is added to the GIF. Hit 's' to save the gif at any time.");
      startCreatingGif = true;
    } 
  }
}

