#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "CloudsVisualSystemRezanator.h"

/** 
 * COMPUTATION visual system
 * shows ticker tape strands running in fields
 * that can be zoomed in and diverted
 */

class CloudsVisualSystemRGBD : public CloudsVisualSystemRezanator {
  public:

	string getSystemName();
    
    void selfSetup();
    void selfSetupGuis();
    
    void selfUpdate();
    void selfDrawBackground();
    void selfDrawDebug();
    void selfSceneTransformation();
    void selfDraw();
    void selfExit();
    void selfBegin();
	void selfEnd();
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
    
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
	
  protected:
	
	float pointcloudScale;
	float pointcloudOffsetZ;
	
	ofVec2f scanlineSimplify;
	
	bool refreshScanlineMesh;
	float verticalScanlineAlpha;
	float verticalScanlineThickness;
	float horizontalScanlineAlpha;
	float horizontalScanlineThickness;
	
	
	void generateScanlines();
	ofMesh horizontalScanLines;
	ofMesh verticalScanLines;
	
	ofMesh randomPoints;
	
};