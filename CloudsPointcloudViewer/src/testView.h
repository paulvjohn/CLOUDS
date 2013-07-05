#pragma once

#include "ofMain.h"
#include "ofxCocoaGLView.h"
#include "CloudsFCPParser.h"
#include "CloudsRGBDCombinedRenderer.h"
#include "CloudsVisualSystemRGBD.h"

@interface testView : ofxCocoaGLView <NSTableViewDataSource, NSTableViewDelegate> {
	IBOutlet NSTableView* clipTable;
	CloudsFCPParser parser;
	CloudsRGBDCombinedRenderer renderer;
	CloudsVisualSystemRGBD rgbdVisualSystem;
	
	CloudsClip currentClip;
	int currentClipIndex;

}

@property (assign) IBOutlet NSTableView *clipTable;

- (void)setup;
- (void)update;
- (void)draw;
- (void)exit;

- (void)keyPressed:(int)key;
- (void)keyReleased:(int)key;
- (void)mouseMoved:(NSPoint)p;
- (void)mouseDragged:(NSPoint)p button:(int)button;
- (void)mousePressed:(NSPoint)p button:(int)button;
- (void)mouseReleased:(NSPoint)p button:(int)button;
- (void)windowResized:(NSSize)size;

- (IBAction)loadClipFromTable:(id)sender;
- (IBAction)loadClip:(CloudsClip&)clip;

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView;
- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex;

@end
