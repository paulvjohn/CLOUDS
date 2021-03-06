#pragma once

#include "ofMain.h"
#include "statistics.h"
#include "curvedLine.h"
#include "lineMatchUtils.h"
//#include "ofxTimeMeasurements.h"
//#include "ofxShivaVGRenderer.h"
#include "CloudsVisualSystem.h"
#include "BrushedLine.h"


class threadedSeeker : public ofThread {
    
    
    void threadedFunction();
public:
        ofPolyline line40;
        ofPolyline nodeLineLast100;
    
        vector < polyPtr > polyPtrs;
        vector < int > lastFound;
        bool bFoundMatch;
        matchStruct match;
        float thresh;
    
    
};


class drawnLineApp {

	public:
    
    
    
        ofMutex mutex;
        threadedSeeker seeker;
    
    

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawLineSet(lineSet & set, matchStruct & match, ofPoint ptA, ofPoint ptB);
    
    
        void lookForGoodMatchSetup();
        void lookForGoodMatchWork();
    
    
        lineSet & linesetFromFile( string fileName );

        lineSet set;
        vector < lineSet > lineSets;
        curvedLine CL;
        vector < ofPolyline > rotatedLines;
    
        ofPolyline nodeLineLast100;
        ofPolyline nodeLine40;
    
        vector < distanceResult > distanceResults;
        vector < matchStruct > matchStructs;
        float lastMatchTime;
    
    
        ofShader shader;
        float angleCatch;
    
        float matchEnergy;
        ofPoint catchPt;
        float scale;
    
         ofFbo fbo;
    // ofPtr<ofBaseRenderer> _defaultRenderer;
    // ofPtr<ofxShivaVGRenderer> _shivaVGRenderer;
    
    BrushedLine BL;
    
    bool bShowDebug;
    
    CloudsVisualSystem * SYS;
};
