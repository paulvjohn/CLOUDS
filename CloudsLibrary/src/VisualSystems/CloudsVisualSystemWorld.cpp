//
//  CloudsVisualSystemWorld.cpp
//  VSWorld
//
//  Created by Patricio Gonzalez Vivo on 6/13/13.
//
//

#include "CloudsVisualSystemWorld.h"

string CloudsVisualSystemWorld::getSystemName()
{
	return "World";
}

void CloudsVisualSystemWorld::selfSetup()
{
//    loadParticles("simple-rivers.txt");
    
    loadPath( coast, "simple-coast.txt");
    loadPath( borders, "simple-borders.txt");
    loadPath( rivers, "simple-rivers.txt");
    
//    loadPoints( points, "airports.txt");
    loadPoints( points, "simple-cities.txt");
    
    globalOffset.set(0,0,0);
}

void CloudsVisualSystemWorld::loadParticles( string _file ){
    ifstream fileIn;
	
    string filePath = getDataPath()+"visualsystems/World/"+_file;
    ofBuffer buffer = ofBufferFromFile(filePath);
    
    wParticle *lastParticle = NULL;
    wParticle *newParticle = NULL;
    
    while(!buffer.isLastLine()) {
        string temp = buffer.getNextLine();
        
        if(temp.length() != 0) {
            
            vector<string> values = ofSplitString(temp, " ");
            
            if ( values[0] == "segment"){
                
                newParticle = NULL;
                lastParticle = NULL;
                
            } else {
                
                newParticle = new wParticle();
                newParticle->set( ofPoint(ofToFloat(values[0]),
                                          ofToFloat(values[1]),
                                          ofToFloat(values[2]) ) );
                newParticle->loc = *newParticle;
                
                if ( lastParticle != NULL){
                    newParticle->connect = lastParticle;
                }
                
                particles.push_back(newParticle);
                lastParticle = newParticle;
            }
        }
    }

}

void CloudsVisualSystemWorld::loadPath(vector< vector<ofPoint> > &_path, string _file){
    
    ifstream fileIn;
	
    string filePath = getDataPath()+"visualsystems/World/"+_file;
    ofBuffer buffer = ofBufferFromFile(filePath);

    int lineCount = 0;
    vector<ofPoint> newPoly;
    
    while(!buffer.isLastLine()) {
        string temp = buffer.getNextLine();
        
        if(temp.length() != 0) {
            
            vector<string> values = ofSplitString(temp, " ");
            
            if ( values[0] == "segment"){
                
                if (newPoly.size() > 1){
                    _path.push_back( newPoly );
                }
                newPoly.clear();
            } else {
                ofPoint newPoint = ofPoint(ofToFloat(values[0]),
                                           ofToFloat(values[1]),
                                           ofToFloat(values[2]) );
                
                newPoly.push_back(newPoint);
            }
            
            lineCount++;
        }
    }
}

void CloudsVisualSystemWorld::loadPoints(vector<ofPoint> &_points, string _file){
    ofVec3f center = ofVec3f(0,0,-300);
    
    string filePath = getDataPath()+"visualsystems/World/"+_file;
    ofBuffer buffer = ofBufferFromFile(filePath);
    
    while(!buffer.isLastLine()) {
        string temp = buffer.getNextLine();
        
        if(temp.length() != 0) {
            vector<string> values = ofSplitString(temp, "|");
            
            ofQuaternion latRot, longRot;
            latRot.makeRotate( ofToFloat(values[1]), 1, 0, 0);
            longRot.makeRotate( ofToFloat(values[2]), 0, 1, 0);
            
            ofVec3f worldPoint = latRot * longRot * center;
            
            _points.push_back(worldPoint);
        }
    }
}

void CloudsVisualSystemWorld::selfSetupSystemGui()
{
    sysGui->addSlider("pointsNoisePeaks", 0.0, 500, &pointNoisePeaks);
    sysGui->addSlider("density", 0.0, 1.0, &density);
    sysGui->addSlider("gravity", 0.0, 1.0, &gravity);
    sysGui->addSlider("repulsion", 0.0, 1.0, &repulsion);
    
    sysGui->addSlider("turbulence", 0.0, 0.09, &turbulence);
    sysGui->addSlider("neigbordhood", 1, 300, &neigbordhood);
    sysGui->addSlider("independence", 0, 0.01, &independence);

}

void CloudsVisualSystemWorld::selfSetupRenderGui()
{

}

void CloudsVisualSystemWorld::guiSystemEvent(ofxUIEventArgs &e)
{

}


void CloudsVisualSystemWorld::selfKeyPressed(ofKeyEventArgs & args){
    
}

void CloudsVisualSystemWorld::selfUpdate()
{
    ofSetColor(255);

    if ( points.size() > 2){
        ofPoint randomPlace = points[ofRandom(points.size()-1)];
        wParticle *newParticle = new wParticle();
        newParticle->set( randomPlace.x, randomPlace.y, randomPlace.z);
        newParticle->loc = *newParticle;
        particles.push_back(newParticle);
    }
    
    while (particles.size() > 1000) {
        delete particles[0];
        particles.erase(particles.begin());
    }
    
    for(int i = 0; i < particles.size(); i++){
        particles[i]->addRepulsionForce( ofPoint(0,0,0), 400, repulsion);
        particles[i]->addAttractionForce( ofPoint(0,0,0), 1000, gravity);
//        particles[i]->applyGravityForce(gravity);
        particles[i]->applyFlockingForce(&globalOffset,neigbordhood,independence);
        particles[i]->update(density);
    }
    
    globalOffset += ofPoint(turbulence/neigbordhood,
							turbulence/neigbordhood,
							turbulence/neigbordhood);
}

void CloudsVisualSystemWorld::selfDraw()
{
    mat->begin();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    ofPushMatrix();
    ofPushStyle();
    
    ofScale(0.3,0.3,0.3);
    
    ofRotateY(ofGetFrameNum()*0.01);
    
    ofFill();
    ofSetColor(20,20);
	ofDrawSphere(0, 0, 290);
    
    ofNoFill();
    ofSetColor(255,20);
	ofDrawSphere(0, 0, 295);
    
    ofSetColor(255,100);
//    glBegin(GL_POINTS);
    for(int i = 0; i < particles.size(); i++){
        particles[i]->draw();
    }
//    glEnd();
    
//    ofSetLineWidth(1.5);
    for(int i = 0; i < coast.size(); i++){
        ofSetColor(255);
        
        ofBeginShape();
        for (int j = 0; j < coast[i].size(); j++) {
            ofVertex(coast[i][j]);
        }
        ofEndShape(false);
    }

    ofSetLineWidth(0.5);
    ofSetColor(150);
//    for(int i = 0; i < borders.size(); i++){
//        ofBeginShape();
//        for (int j = 0; j < borders[i].size(); j++) {
//            ofVertex(borders[i][j]);
//        }
//        ofEndShape(false);
//    }
    
    ofSetLineWidth(0.2);
    ofSetColor(0,140,200);
    for(int i = 0; i < rivers.size(); i++){
        ofBeginShape();
        for (int j = 0; j < rivers[i].size(); j++) {
            ofVertex(rivers[i][j]);
        }
        ofEndShape(false);
    }
    
//    ofSetColor(255);
//    ofColor color = ofColor(255,0,0);
//    for(int i = 0; i < points.size(); i++){
//        ofPoint tail = points[i];
//        ofPoint head = points[i] - ofPoint(0,0,0);
//        head.normalize();
//        ofPoint pos = tail*ofGetElapsedTimef()*0.001;
//        float noise = powf(pointNoisePeaks,ofNoise( sin(pos.x),pos.y,pos.z*0.1));
//        head *= noise;
//        color.setHue(ofMap(noise,0.001,pointNoisePeaks,20,50,true ));
//        ofSetColor(color);
//        ofLine(tail, tail+head);
//    }
    
    
    ofPopStyle();
    ofPopMatrix();
    
    glDisable(GL_NORMALIZE);
    glDisable(GL_DEPTH_TEST);
    mat->end();
}


void CloudsVisualSystemWorld::selfSetupGuis()
{
    
}

void CloudsVisualSystemWorld::selfAutoMode()
{
    
}


void CloudsVisualSystemWorld::selfDrawBackground()
{
    
}

void CloudsVisualSystemWorld::selfDrawDebug()
{
    
}

void CloudsVisualSystemWorld::selfSceneTransformation()
{
    
}

void CloudsVisualSystemWorld::selfExit()
{
    
}

void CloudsVisualSystemWorld::selfBegin()
{
    
}

void CloudsVisualSystemWorld::selfEnd()
{
    
}

void CloudsVisualSystemWorld::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void CloudsVisualSystemWorld::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemWorld::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemWorld::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemWorld::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemWorld::selfSetupGui()
{
    
}

void CloudsVisualSystemWorld::selfGuiEvent(ofxUIEventArgs &e)
{
    
}

void CloudsVisualSystemWorld::guiRenderEvent(ofxUIEventArgs &e)
{
    
}