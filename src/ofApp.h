#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
    
    void makeFaceArr();
    
    struct indexBrightness {
        int i;
        float brightness;
    };

    ofImage Face;
    indexBrightness faceArr[786432];
    ofVideoGrabber videoGrabber;
    ofTexture texture;

    unsigned char* vidOut;
    int camWidth;
    int camHeight;
};
