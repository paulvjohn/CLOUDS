
#pragma once

#include "ofMain.h"

#include "ofxUI.h"
#include "CloudsVisualSystemRezanator.h"
#include "CloudsRGBDCombinedRender.h"

class CloudsVisualSystemSeeingDark : public CloudsVisualSystemRezanator {
 public:
	CloudsVisualSystemSeeingDark();

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
	
	void selfSetupTimeline();
	
	void loadMovieForComposition(string videoPath);

	CloudsRGBDCombinedRender renderer;
	
	ofxUISuperCanvas* composeGui;
	ofxUITextInput* fileNameInput;
	
	bool clipLoaded;
	float nearPlane;
	float farPlane;
	float scale;
	
	ofVec3f centerOffsetCourse;
	ofVec3f centerOffsetFine;
	bool drawCenterDebug;
	
	bool beginning;
	bool middle;
	bool end;

	ofVec2f scanlineSimplify;
	ofVboMesh horizontalScanLines;
	ofVboMesh verticalScanLines;
	bool refreshScanlineMesh;
	void generateScanlines();
};
