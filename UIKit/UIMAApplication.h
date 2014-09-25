/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIImageView.h>

#define kMainPipeRead           10
#define kMainPipeWrite          21

@class UIApplicationIcon, UIMAApplication;

extern NSMutableDictionary *_allApplicationsDictionary;
extern UIMAApplication *_currentMAApplication;

@interface UIMAApplication : NSObject {
@package
    NSString *_name;
    NSMutableDictionary *_data;
    BOOL _running;
    int _score;
    pid_t _pid;
    int _pipeRead;
    int _pipeWrite;
    int _animationPipeRead;
    int _animationPipeWrite;
    UIImageView *_screenImageView;
    UIApplicationIcon *_applicationIcon;
}

@property (nonatomic, retain) UIImageView *screenImageView;
@property (nonatomic, retain) NSString *name;
@property (nonatomic) int score;
@property (nonatomic) int pageNumber;
@property (nonatomic) int xLocation;
@property (nonatomic) int yLocation;
@property (nonatomic) BOOL anchored;
@property BOOL running;

- (id)initWithAppName:name;
- (void)swapLocationWithApp:(UIMAApplication *)anotherApp;
- (void)startApp;
- (void)setAsCurrent:(BOOL)withSignal;
- (void)terminate;
- (void)singleTapped;
- (void)closeApp;
- (void)deleteApp;

@end

//void UIMAApplicationInitialize();
//int UIMAApplicationHandleMessages();
void UIMAApplicationSaveData(UIMAApplication *app);
void UIMAApplicationClosePipes();
