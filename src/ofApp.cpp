#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth = 1024;
    camHeight = 768;
    videoGrabber.initGrabber(camWidth,camHeight);
    texture.allocate(camWidth,camHeight, GL_RGB);
    
    Face.load("face4.jpg");
    // Face.setImageType(OF_IMAGE_GRAYSCALE);
    makeFaceArr();

}

//--------------------------------------------------------------
void ofApp::update(){
    
    videoGrabber.update();
    
    if(videoGrabber.isFrameNew()){
        makeNewFrame();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(100,100,100);
    ofSetColor(255,255,255);

    texture.draw(0, 0);
    videoGrabber.draw(0,0, 256, 192);

}

//--------------------------------------------------------------
void ofApp::exit(){

}

bool compare(ofApp::indexBrightness x, ofApp::indexBrightness y) { return x.brightness < y.brightness; };

// creates array of target image pixels sorted by brightness
void ofApp::makeFaceArr(){
    
    int n = Face.getWidth()*Face.getHeight();
    int m = 0;
    
    vector<indexBrightness> faceBrightness(n);
    
    for (int i = 0; i < n; i++) {
        faceBrightness[i].i = i;
        faceBrightness[i].brightness = Face.getColor(i*3).getBrightness();
        
        if (faceBrightness[i].brightness > m)
            m = faceBrightness[i].brightness;
    }
    
    // counting sort for smoother output see https://github.com/maxcheever/lookmeintheeyes1
    vector<int> count(m+1, 0);
    
    for (int i = 0; i < n; i++)
        count[faceBrightness[i].brightness]++;
    
    for (int i = 1; i <= m; i++)
        count[i] += count[i-1];
    
    for (int i = n-1; i >= 0; i--) {
        faceArr[count[faceBrightness[i].brightness]-1] = faceBrightness[i];
        count[faceBrightness[i].brightness]--;
    }
    
}

// makes the output frame using the sorted input frame and target image
void ofApp::makeNewFrame(){
    
    
    int iWidth = Face.getWidth();
    int iHeight = Face.getHeight();
    int n = iWidth*iHeight;
    ofPixels src = videoGrabber.getPixels();
    
    
    vector<indexBrightness> sampleBrightness(n);
    
    for (int i = 0; i < n; i++) {
        sampleBrightness[i].i = i;
        sampleBrightness[i].brightness = src.getColor(i*3).getBrightness();
    }
    
    // intro sort for smoother output see https://github.com/maxcheever/lookmeintheeyes1
    sort(sampleBrightness.begin(), sampleBrightness.end(), compare);
    
    dest.allocate(iWidth, iHeight, OF_IMAGE_COLOR);
    
    // map pixels to the correct position in output frame
    for (int i = 0; i < n; i++) {
        dest.setColor(faceArr[i].i*3, src.getColor(sampleBrightness[i].i*3));
    }
    
    texture.loadData(dest);
    
}
