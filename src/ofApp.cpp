#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
	leap.open();
    leap.setupGestures();
    
    //Set light position
	l1.setPosition(200, 300, 50);
	l2.setPosition(-200, -200, 50);
    
	cam.setOrientation(ofPoint(-20, 0, 0));
    
    model.loadModel("battery.dae", true); //Load collada 3D model file
    model.setPosition(ofGetWidth()*2/6, (float)ofGetHeight() * 0.75 , 0);  //Set position for model
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

//--------------------------------------------------------------
void ofApp::update(){
    fingersFound.clear();
	fingerPoint.clear() ;
    simpleHands = leap.getSimpleHands();
    leap.updateGestures();
    
    model.update(); //update the 3D model
    
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        for(int i = 0; i < simpleHands.size(); i++){
            
            for(int j = 0; j < simpleHands[i].fingers.size(); j++){
                int id = simpleHands[i].fingers[j].id ;
                ofPolyline & polyline = fingerTrails[id] ;
                ofPoint pt = simpleHands[i].fingers[j].pos ;
                handPoint = simpleHands[i].handPos ;
                fingerPoint.push_back(simpleHands[i].fingers[j].pos) ;
                //if the distance between the last point and the current point is too big - lets clear the line
                //this stops us connecting to an old drawing
                if( polyline.size() && (pt-polyline[polyline.size()-1] ).length() > 50 ){
                    polyline.clear();
                }
                
                //add our point to our trail
                polyline.addVertex(pt);
                
                //store fingers seen this frame for drawing
                fingersFound.push_back(id);
            }
        }
    }
    
    mesh = model.getCurrentAnimatedMesh(0);
    leap.markFrameAsOld();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDisableLighting();
    ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),  OF_GRADIENT_BAR);
	
	ofSetColor(200);
	ofDrawBitmapString("ofxLeapMotion - Example App\nLeap Connected? " + ofToString(leap.isConnected()), 20, 20);
    
	cam.begin();
    
	ofPushMatrix();
    ofRotate(90, 0, 0, 1);
    ofSetColor(20);
    ofDrawGridPlane(800, 20, false);
	ofPopMatrix();
	
	ofEnableLighting();
	l1.enable();
	l2.enable();
	
	m1.begin();
	m1.setShininess(0.6);
    
    ofPushMatrix() ;
    ofTranslate(model.getPosition().x, model.getPosition().y, 0);
    ofRotate(-leap.swipeSpeed, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix() ;
	
	for(int i = 0; i < fingersFound.size(); i++){
//		ofxStrip strip;
		int id = fingersFound[i];
        
		ofPolyline & polyline = fingerTrails[id];
        //ofCircle(handPoint, 10) ;
        ofCircle(fingerPoint[i], 50) ;
        model.setPosition(handPoint.x, handPoint.y, 0) ;
        
//		strip.generate(polyline.getVertices(), 15, ofPoint(0, 0.5, 0.5) );
//		
//		ofSetColor(255 - id * 15, 0, id * 25);
//		strip.getMesh().draw();
	}
    /* Leap iGesture Key
     --------------------------------
     1 = Screen Tap
     2 = Key Tap
     3 = Swipe Right
     4 = Swipe Left
     5 = Swipe Down
     6 = Swipe Up
     7 = Swipe Forward
     8 = Swipe Backward (towards yourself)
     9 = Circle Left (counter-clockwise)
     10 = Circle Right (clockwise)
     --------------------------------
     */
    switch (leap.iGestures) {
        case 1: //Screen Tap
            break;
        case 2: //Key Tap
            break;
            
        case 3: //Swipe Right
            break;
        case 4: //Swipe Left
            break;
        case 9: //Circle Left
            break;
        case 10: //Circle Right

            break;
        default:
            break;
    }
	
    l2.disable();
    
    //    for(int i = 0; i < simpleHands.size(); i++){
    //        simpleHands[i].debugDraw();
    //    }
    
	m1.end();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::exit() {
    leap.close();
}
