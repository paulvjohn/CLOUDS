//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the EMPTY CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"

#include "ofxTonic.h"
#include "CloudsAudioEvents.h"
#include "CloudsGlobal.h"

//using namespace Tonic;

//TODO: rename this to your own visual system
class CloudsVisualSystemRipples : public CloudsVisualSystem {
  public:
    
	//TODO: Change this to the name of your visual system
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName(){
		return "Ripples";
	}

	//These methods let us add custom GUI parameters and respond to their events
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);

	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();

	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();

	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();

	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
		
    // draw any debug stuff here
	void selfDrawDebug();

	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();

	// this is called when your system is no longer drawing.
	// Right after this selfUpdate() and selfDraw() won't be called any more
	void selfEnd();

	// this is called when you should clear all the memory and delet anything you made in setup
    void selfExit();
    void selfSetDefaults();

	//events are called when the system is active
	//Feel free to make things interactive for you, and for the user!
    void selfKeyPressed(int key);
    void selfKeyReleased(ofKeyEventArgs & args);
    
//    void selfMouseDragged(int x, int y, int button);
//    void selfMouseMoved(int x, int y, int button);
//    void selfMousePressed(int x, int y, int button);
//    void selfMouseReleased(int x, int y, int button);
    
    void selfInteractionMoved(CloudsInteractionEventArgs& args);
	void selfInteractionStarted(CloudsInteractionEventArgs& args);
	void selfInteractionDragged(CloudsInteractionEventArgs& args);
	void selfInteractionEnded(CloudsInteractionEventArgs& args);
    
    // if you use a custom camera to fly through the scene
	// you must implement this method for the transitions to work properly
//	ofCamera& getCameraRef(){
//		return myCustomCamera;
//	}
    
    void restart();

  protected:
    ofxUISuperCanvas * customGui;
    ofx1DExtruder * tintHue, * tintSat, * tintBri, * tintAlpha;
    
    ofShader ripplesShader;
    ofFbo ripplesSrcFbo, ripplesDstFbo;
    ofVboMesh renderMesh;
    
    float minDropHue, maxDropHue;
    float minDropSat, maxDropSat;
    float minDropBri, maxDropBri;
    
    ofColor tintColor;
    ofColor dropColor;
    
    bool bDropOnPress;
    int dropRate;
    
	float damping;
    float radius;
    
	bool bRestart;

	// Sound
    int dontTriggerSoundCounter;
    ofxUISuperCanvas* soundGui;
    float volume[2];
    Tonic::ControlParameter volumeControl[2];
    bool bEnableSounds;
    ofMutex mutex;
    Tonic::ControlParameter mainGain;
    float fMainGain;
    Tonic::ofxTonicSynth mainSynth;
    Tonic::ofxTonicSynth notes[5];
    int noteIndex;
    int baseNote;
    vector<float> scale;
    void setScaleByName(string name);
    Tonic::Generator buildSynth();
    Tonic::Mixer mixer;
    void playNote(int note);
	void audioRequested(ofAudioEventArgs& args);
};
