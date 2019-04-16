#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 640;
    camHeight = 480;
    columnNum = 0;
    rowNum = 0;
    switchCase = 1;
    
    myFont.load("/Users/angelnacipucha/Desktop/of_v0.10.1_osx_release/apps/myApps/slitScanProject/src/Menlo.ttc",20);
    
    myVideoGrabber.setDesiredFrameRate(60);
    myVideoGrabber.initGrabber(camWidth, camHeight);
    
    imageStored = new unsigned char [camWidth * camHeight * 3];
    imageStored2 = new unsigned char [camWidth * camHeight * 3];
    imageStored3 = new unsigned char [camWidth * camHeight * 3];
    
    myTexture.allocate (camWidth, camHeight, GL_RGB);
    slitScanImage.allocate (camWidth, camHeight, OF_IMAGE_COLOR);
    ofSetVerticalSync(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    myVideoGrabber.update();
    
    switch (switchCase) {
        case 1:
            if (myVideoGrabber.isFrameNew()) {
                unsigned char* pixelData = myVideoGrabber.getPixels().getData();
                int rowNumPixels, columnNumPixels, mouseXPixels;
                
                for (int row = 0; row < camHeight; row++) {
                    rowNumPixels = row * camWidth * 3;
                    for (int cc = 0; cc < 3; cc++) {
                        columnNumPixels = columnNum * 3;
                        mouseXPixels = mouseX * 3;
                        imageStored[rowNumPixels + columnNumPixels +cc] = pixelData [rowNumPixels + mouseXPixels + cc];
                    }
                }
                columnNum ++;
                myTexture.loadData(imageStored, camWidth, camHeight, GL_RGB);
            }
            break;
        case 2:
            if (myVideoGrabber.isFrameNew()) {
                unsigned char* pixelData = myVideoGrabber.getPixels().getData();
                int rowNumPixels, columnNumPixels, mouseXPixels;
                int v1 = ofRandom(0, 8);
                
                for (int column = 0; column < camWidth; column++) {
                    columnNumPixels = column * camHeight * 3;
                    for (int cc = 0; cc < v1; cc++) {
                        rowNumPixels = rowNum * 3;
                        mouseXPixels = mouseX *3;
                        imageStored2[columnNumPixels + rowNumPixels +cc] = pixelData [columnNumPixels + mouseXPixels + cc];
                    }
                }
                rowNum ++;
                myTexture.loadData(imageStored2, camWidth, camHeight, GL_RGB);
            }
            break;
        case 3:
            if (myVideoGrabber.isFrameNew()) {
                unsigned char* pixelData = myVideoGrabber.getPixels().getData();
                unsigned char* imageStored3 = slitScanImage.getPixels().getData();
                
                movePixelsInImage(&slitScanImage);
                
                for (int x = 0; x < camWidth; x++) {
                    for (int cc = 0; cc <3 ; cc++) {
                        int imagePostion = ((camWidth * camHeight *3)) + (x) * 3;
                        int videoPostion = (x) * 3;
                        
                        imageStored3[imagePostion + cc] = pixelData[videoPostion + cc];
                        
                    }
                }
            }
            break;
        default:
            //Nothing here
            break;
    }
}

void ofApp::movePixelsInImage (ofImage * image) {
    unsigned char * pixelData = image -> getPixels().getData();
    for (int column = 0; column < image->getWidth() - 1; column++ ) {
        for (int row = 0; row < image -> getHeight(); row++) {
            for (int cc = 0; cc < 3; cc++) {
                int postion = row * (image -> getWidth() * 3) + column * 3;
                int nextPostion = postion + camWidth * 3;
                pixelData[postion + cc] = pixelData[nextPostion + cc];
                
            }
        }
    }
    image-> update();
}


//--------------------------------------------------------------
void ofApp::draw(){
    myVideoGrabber.draw(0,0);
    
    if (switchCase == 1 || switchCase == 2) {
        ofDrawLine(mouseX, 0 , mouseX, camHeight);
    } else {
        ofDrawLine(0, 2, camWidth, 2);
    }
    
    myFont.drawString("Press either: 1, 2, or 3 ", 50, camHeight + 50);
    myFont.drawString("for different slit scanners! ", 50, camHeight + 80);
    myFont.drawString("Slit Scanner: ", (3 * ofGetWidth() )/ 4 - 200, camHeight + 50);
    string switchCaseString = to_string(switchCase);
    myFont.drawString(switchCaseString, (3 * ofGetWidth() )/ 4 + 10, camHeight + 50);
    
    if (switchCase == 1) {
        myTexture.draw(650, 0);
    }
    if (switchCase == 2) {
        myTexture.draw(650, 0);
    }
    if (switchCase == 3) {
        slitScanImage.draw(650, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1'){
        switchCase = 1;
    } else if (key == '2') {
        switchCase = 2;
    } else if (key == '3') {
        switchCase = 3;
    }
}

