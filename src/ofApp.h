#pragma once

#include "ofMain.h"
#include "ofxLeapMotion.h"
#include "ofxCv.h"
#include "ofx3DBaseLoader.h"
#include "ofx3DModelLoader.h"
#include "ofxAssimpAnimation.h"
#include "ofxAssimpMeshHelper.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpTexture.h"
#include "ofVboMesh.h"

class ofApp : public ofBaseApp{

	public:
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
        void exit() ;
    
        ofxLeapMotion leap;
        vector <ofxLeapMotionSimpleHand> simpleHands;
        vector <int> fingersFound;
        vector <ofPoint> fingerPoint ;
        ofPoint handPoint ;
        ofEasyCam cam;
        ofLight l1;
        ofLight l2;
        ofMaterial m1;
        map <int, ofPolyline> fingerTrails;
    
        ofxCv::ObjectFinder finder;
        ofxAssimpModelLoader model ;
        bool bAnimate;
        bool bAnimateMouse;
        float animationPosition;
        ofMesh mesh;
		
};
