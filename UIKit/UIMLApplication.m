/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <fcntl.h>
#import <UIKit/UIKit-private.h>
#import <IOKit/IOKit.h>
#import <CoreAnimation/CoreAnimation-private.h>
#import <CoreFoundation/CoreFoundation-private.h>

//#define _kTimeToTerminateChild          10.0
#define _kTerminateChildTimeOut         2.0
//#define _kGobackTimeLimit               1.0

static BOOL _childAppRunning = NO;
static UIMLApplication *_mlApp = nil;
static CFTimeInterval _startTime;
//static CFTimeInterval _lastGobackTime = 0;
static UIApplication *_uiApplication = nil;
static UIMLApplication *_uiMLApplication = nil;
static UIMAApplication *_uiMAApplication = nil;
static UIView *_launcherView = nil;
static UIView *_maAppView = nil;

#pragma mark - Static functions

@implementation UIMLApplication

#pragma mark - Life cycle
/*
- (id)init
{
    if ((self=[super init])) {
        _uiApplication = [UIApplication sharedApplication];
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}*/

#pragma mark - Class methods

+ (UIMLApplication *)sharedMLApplication
{
    if (!_mlApp) {
        _mlApp = [[UIMLApplication alloc] init];
    }
    return _mlApp;
}

#pragma mark - Accessors

#pragma mark - Delegates

- (void)presentAppDone
{
    DLog();
    _launcherView.hidden = YES;
    //[_uiApplication->_keyWindow sendSubviewToBack:_launcherView];
    //[_uiApplication->_keyWindow removeFromSuperview];
    //DLog();
    _UIApplicationEnterBackground();
    //NSArray *subviews = [_uiApplication->_keyWindow subviews];
    //UIView *view = [subviews objectAtIndex:subviews.count-1];
    //UIMAApplication *maApp = [_openedApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", view]];
    [[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
    //DLog(@"maApp: %@", maApp);
    //[_EAGLMLLock lock];
    //_EAGLMLCanDraw = YES;
    //DLog(@"_EAGLMLCanDraw: %d", _EAGLMLCanDraw);
    //[_EAGLMLLock lock];
    //DLog(@"_EAGLMLLock2: %@", _EAGLMLLock);
    //DLog(@"_EAGLMLLock->counter2: %d", _EAGLMLLock->counter);
    //if (_currentMAApplication != maApp) {
    [_uiMAApplication setAsCurrent:YES];
    //}
    //_lastGobackTime = CACurrentMediaTime();
}
/*
- (void)goBackDone
{
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    //NSArray *subviews = [_uiApplication->_keyWindow subviews];
    //UIView *currentView = [subviews objectAtIndex:subviews.count-1];
    //UIMAApplication *maApp = [_openedApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", currentView]];
    [_uiMAApplication setAsCurrent:YES];
}*/

@end

#pragma mark - Shared functions

void UIMLApplicationInitialize()
{
    DLog(@"UIMLApplicationInitialize");
    _uiApplication = [UIApplication sharedApplication];
    _uiMAApplication = [[UIMAApplication alloc] init];
    //CFArrayAppendValue(_openedApplications, _launcherApp);
    //_openedApplicationsDictionary = [[NSMutableDictionary alloc] init];
    
    //_EAGLMLLock = [[NSLock alloc] init];
    //DLog(@"_EAGLMLLock: %@", _EAGLMLLock);
    //[_EAGLMLLock lock];
}

void UIMLApplicationLauncherViewDidAdded()
{
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    //DLog();
    _launcherView = [[_uiApplication->_keyWindow subviews] objectAtIndex:0];
    _maAppView = [[UIView alloc] initWithFrame:_launcherView.frame];
    //_maAppView.backgroundColor = [UIColor redColor];
    [_uiApplication->_keyWindow insertSubview:_maAppView atIndex:0];
    //DLog(@"_launcherView: %@", _launcherView);
    //DLog(@"_maAppView: %@", _maAppView);
}

void UIMLApplicationSetChildAppIsRunning(BOOL isRunning)
{
    _startTime = CACurrentMediaTime();
    //DLog(@"_startTime: %f", _startTime);
    _childAppRunning = isRunning;
    //[[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
#ifdef NA
    EAGLMLSetChildAppIsRunning(isRunning);
#endif
}

void UIMLApplicationPresentAppScreen(UIMAApplication *maApp, BOOL coldStart)
{
    //DLog();
    //UIApplication *uiApplication = [UIMLApplication sharedMLApplication]->_uiApplication;
    //DLog(@"uiApplication: %@", uiApplication);
    //_uiMAApplication = maApp;
    //[_uiApplication->_keyWindow bringSubviewToFront:_maAppView];
    _launcherView.hidden = YES;
    _UIApplicationEnterBackground();
    if (coldStart) {
        [_maAppView addSubview:maApp.defaultScreenView];
        [maApp startApp];
    } else {
        [maApp setAsCurrent:YES];
    }
#ifdef NA
    [_CAAnimatorNAConditionLock unlockWithCondition:_CAAnimatorConditionLockHasWork];
#endif
}

void UIMLApplicationHandleMessages()
{
#ifdef NA
    if (!_childAppRunning) {
        //DLog();
        return;
    }
    //DLog();
    int message = IOPipeReadMessage();
    switch (message) {
        case MLPipeMessageEndOfMessage:
            //DLog(@"MLPipeMessageEndOfMessage");
            break;
        case MLPipeMessageChildIsReady:
            //DLog(@"MLPipeMessageChildIsReady");
            break;
        case MLPipeMessageTerminateApp:
            DLog(@"MLPipeMessageTerminateApp");
            //[[[_application->_keyWindow subviews] lastObject] removeFromSuperview];
            break;
        default:
            break;
    }
#endif
}

void UIMLApplicationShowLauncher()
{
    DLog();
    if ([[_maAppView subviews] count] > 0) {
        //DLog(@"[[_maAppView subviews] count] > 0");
        [[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
    }
    [_currentMAApplication gotoBackground];
    _UIApplicationEnterForeground();
    _launcherView.hidden = NO;
    //DLog();
    //[_uiApplication->_keyWindow bringSubviewToFront:_launcherView];
#ifdef NA
    [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
#endif
}

void UIMLApplicationGoBack()
{
    _maAppView.hidden = NO;
    if (!_launcherView.hidden) {
        if (CFArrayGetCount(_openedApplications) == 0) {
            DLog(@"CFArrayGetCount(_openedApplications) == 0");
            return;
        } else {
            //DLog(@"_currentMAApplication: %@", _currentMAApplication);
            UIMLApplicationPresentAppScreen(_currentMAApplication, NO);
        }
    } else {
        _maAppView.hidden = NO;
        if (CFArrayGetCount(_openedApplications) == 1) {
            return;
        }
        [_currentMAApplication gotoBackground];
        int currentAppIndex = _CFArrayGetIndexOfValue(_openedApplications, _currentMAApplication);
        //DLog(@"currentAppIndex: %d", currentAppIndex);
        if (currentAppIndex == 0) {
            _uiMAApplication = _CFArrayGetLastValue(_openedApplications);
        } else {
            _uiMAApplication = CFArrayGetValueAtIndex(_openedApplications, currentAppIndex-1);
            //DLog(@"_uiMAApplication: %@", _uiMAApplication);
        }
        [_uiMAApplication setAsCurrent:YES];
    }
}

void UIMLApplicationMoveCurrentAppToTop()
{
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    if (!_launcherView.hidden) {
        return;
    }
    //int currentAppIndex = [_openedApplications indexOfObject:_currentMAApplication];
    //_currentMAApplication->_needsScreenCapture = YES;
    /*if (currentAppIndex == CFArrayGetCount(_openedApplications) - 1) {
        return;
    }*/
    //_currentMAApplication->_score++;
    //}
    _CFArrayMoveValueToTop(_openedApplications, _currentMAApplication);
    //DLog(@"_openedApplications: %@", _openedApplications);
    //_currentAppIndex = CFArrayGetCount(_openedApplications) - 1;
}

void UIMLApplicationTerminateApps()
{
#ifdef NA
    if ([_CAAnimatorNAConditionLock condition] == _CAAnimatorConditionLockHasWork) {
        [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
    }
#endif
    DLog(@"_currentMAApplication: %@", _currentMAApplication);
    if (_currentMAApplication->_running) {
        IOPipeWriteMessage(MAPipeMessageTerminateApp, YES);
    }
    for (UIMAApplication *maApp in _openedApplications) {
        //for (NSString *key in _openedApplicationsDictionary) {
        //DLog();
        //UIMAApplication *maApp = [_openedApplicationsDictionary objectForKey:key];
        //DLog(@"maApp: %@", maApp);
        if (maApp != _currentMAApplication || !_currentMAApplication->_running) {
            [maApp terminate];
        }
    }
    if (_currentMAApplication->_running) {
        BOOL done = NO;
        _startTime = CACurrentMediaTime();
        while (!done) {
            int message = IOPipeReadMessage();
            switch (message) {
                case MLPipeMessageEndOfMessage:
                    DLog(@"MLPipeMessageEndOfMessage");
                    break;
                case MLPipeMessageTerminateApp:
                    DLog(@"MLPipeMessageTerminateApp");
                    done = YES;
                    break;
                default:
                    break;
            }
            if (CACurrentMediaTime() - _startTime > _kTerminateChildTimeOut) {
                DLog(@"CACurrentMediaTime() - _startTime > _kTerminateChildTimeOut");
                done = YES;
                [_currentMAApplication terminate];
            }
        }
    }
}
