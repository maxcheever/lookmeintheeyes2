#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
    
        	void makeFaceArr();
        	void makeNewFrame();
		
        	struct indexBrightness {
            		int i;
            		float brightness;
        	};

        	ofImage Face;
        	indexBrightness faceArr[786432];
        	ofVideoGrabber videoGrabber;
        	ofTexture texture;
        	ofPixels dest;
    
        	int camWidth;
        	int camHeight;
};
