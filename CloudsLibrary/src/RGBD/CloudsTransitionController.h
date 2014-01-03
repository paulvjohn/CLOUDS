//
//  CloudsTransitionController.h
//  CLOUDS
//
//  Created by James George on 1/3/14.
//
//

#pragma once

#include "ofMain.h"

typedef enum {
	TRANSITION_INTERVIEW_IDLE = 0,
	TRANSITION_INTERVIEW_OUT = 1,
	TRANSITION_VISUALSYSTEM_IN = 2,
	TRANSITION_VISUALSYSTEM_OUT = 3,
	TRANSITION_INTERVIEW_IN = 4
} CloudsTransitionState;

class CloudsTransitionController {
  public:
	CloudsTransitionController();
	
	void transitionToVisualSystem(float transitionOutDuration, float transitionInDuration);
	void transitionToInterview(float transitionOutDuration, float transitionInDuration);
	
	void update();
	
	float percentTransitionIn;
	float percentTransitionOut;

	float getInterviewTransitionPoint();
	
	bool transitioning;
	bool triggeredMidpoint;
	bool fadingOut();
	
	//returns 0 - 1.0 for use in alpha on the visual system texture
	//ramps down when fading out, then up when fading in
	float getFadeValue();
	
	bool isStateNew();
	CloudsTransitionState getCurrentState();
	string getCurrentStateDescription();
	//ofEvent<CloudsPlaybackControllerEvent> CloudsPlaybackControllerEvent::events;
  protected:
	
	CloudsTransitionState currentState;
	
	float transitionStartTime;
	
	float transitionInCompleteTime;
	float transitionOutCompleteTime;
	
	bool newState;
	CloudsTransitionState getNextState();
	

};