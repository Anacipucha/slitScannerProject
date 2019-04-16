#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    unsigned char* imageStored;
    unsigned char* imageStored2;
    unsigned char* imageStored3;
    
    int camWidth;
    int camHeight;
    
    int switchCase;
    int columnNum;
    int rowNum;
    
    ofImage slitScanImage;
    ofVideoGrabber myVideoGrabber;
    ofTexture myTexture;
    
    ofTrueTypeFont myFont;
    
private:
    void movePixelsInImage(ofImage * image);
};
