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

// creates array of pixels in face sorted by brightness (ascending) while keeping track of original index
void ofApp::makeFaceArr(){
    
    /*
     * this function uses counting sort (https://www.geeksforgeeks.org/counting-sort/)
     * due to the fact that the difference between the number of values being sorted (786432)
     * is much larger than the range of values represented (0-255)
     * essentially, this is nearly O(n) on the array size due to the number of repeated values
     */
    
    int n = Face.getWidth()*Face.getHeight();
    int m = 0;
    
    vector<indexBrightness> faceBrightness(n);
    
    // populate temp brightness array
    for (int i = 0; i < n; i++) {
        faceBrightness[i].i = i;
        faceBrightness[i].brightness = Face.getColor(i*3).getBrightness();
        
        if (faceBrightness[i].brightness > m)
            m = faceBrightness[i].brightness;
    }
    
    vector<int> count(m+1, 0);
    
    // count the occurences of each brightness value
    for (int i = 0; i < n; i++)
        count[faceBrightness[i].brightness]++;
    
    // prefix sum at each index
    for (int i = 1; i <= m; i++)
        count[i] += count[i-1];
    
    // populate final array
    for (int i = n-1; i >= 0; i--) {
        faceArr[count[faceBrightness[i].brightness]-1] = faceBrightness[i];
        count[faceBrightness[i].brightness]--;
    }
    
}

// makes the output image
void ofApp::makeNewFrame(){
    
    /*
     * it would make sense to use counting sort again here due to the fact
     * since the range of values is still much smaller than the number of values,
     * but i noticed that using std::sort here creates a distribution of color
     * that is much smoother in the output (std::sort is still efficient at O(nlogn))
     */
    
    int iWidth = Face.getWidth();
    int iHeight = Face.getHeight();
    int n = iWidth*iHeight;
    ofPixels src = videoGrabber.getPixels();
    
    
    vector<indexBrightness> sampleBrightness(n);
    
    // populate temp brightness array
    for (int i = 0; i < n; i++) {
        sampleBrightness[i].i = i;
        sampleBrightness[i].brightness = src.getColor(i*3).getBrightness();
    }
    
    sort(sampleBrightness.begin(), sampleBrightness.end(), compare);
    
    dest.allocate(iWidth, iHeight, OF_IMAGE_COLOR);
    
    // map pixels to the correct position
    for (int i = 0; i < n; i++) {
        dest.setColor(faceArr[i].i*3, src.getColor(sampleBrightness[i].i*3));
    }
    
    texture.loadData(dest);
    
}
