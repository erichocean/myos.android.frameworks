/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <fcntl.h>
#import <UIKit/UIKit-private.h>
#import <IOKit/IOKit.h>
#import <CoreAnimation/CoreAnimation-private.h>
#import <CoreFoundation/CoreFoundation-private.h>

#define _kTimeToTerminateChild          10.0
#define _kTerminateChildTimeOut         1.0
#define _kGobackTimeLimit               1.0

//static NSMutableDictionary *_runningApplicationsDictionary;
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
    //UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", view]];
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
    //UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", currentView]];
    [_uiMAApplication setAsCurrent:YES];
}*/

@end

#pragma mark - Shared functions

void UIMLApplicationInitialize()
{
    DLog(@"UIMLApplicationInitialize");
    _uiApplication = [UIApplication sharedApplication];
    _uiMAApplication = [[UIMAApplication alloc] init];
    //CFArrayAppendValue(_runningApplications, _launcherApp);
    //_runningApplicationsDictionary = [[NSMutableDictionary alloc] init];
    
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
    DLog(@"_launcherView: %@", _launcherView);
    DLog(@"_maAppView: %@", _maAppView);
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
    _uiMAApplication = maApp;
    [_uiApplication->_keyWindow bringSubviewToFront:_maAppView];
    if (coldStart) {
        [maApp startApp];
        //imageView.frame = _maAppView.frame;
        //if ([[_maAppView subviews] count] == 0) {
        [_maAppView addSubview:maApp.defaultScreenView];
        
        //[[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
        //}
        
        //UIImageView *defaultScreenView = maApp.defaultScreenView;
        //UIImageView *defaultAppScreenView = [_appView subviewAtIndex:0]
        //maApp.screenImageView.frame = CGRectMake(0,0,uiApplication->_keyWindow.frame.size.width,uiApplication->_keyWindow.frame.size.height);
        //DLog(@"maApp.screenImageView: %@", maApp.screenImageView);
        //maApp.screenImageView.hidden = NO;
        /*defaultScreenView.alpha = 0;
         [UIView beginAnimations:nil context:nil];
         [UIView setAnimationCurve:UIViewAnimationCurveLinear];
         [UIView setAnimationDuration:0.25];
         [UIView setAnimationDelegate:[UIMLApplication sharedMLApplication]];
         [UIView setAnimationDidStopSelector:@selector(presentAppDone)];
         defaultScreenView.alpha = 1;
         //maApp.screenImageView.alpha = 1;
         [UIView commitAnimations];*/
    } /*else {
        [[UIMLApplication sharedMLApplication] presentAppDone];
    }*/
    //[[UIMLApplication sharedMLApplication] presentAppDone];
    
    
    _launcherView.hidden = YES;
    //[_uiApplication->_keyWindow sendSubviewToBack:_launcherView];
    //[_uiApplication->_keyWindow removeFromSuperview];
    //DLog();
    _UIApplicationEnterBackground();
    if (coldStart) {
        [[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
    }
    //NSArray *subviews = [_uiApplication->_keyWindow subviews];
    //UIView *view = [subviews objectAtIndex:subviews.count-1];
    //UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", view]];
    //if (coldStart) {
    //[[[_maAppView subviews] objectAtIndex:0] removeFromSuperview];
    //DLog(@"maApp: %@", maApp);
    //[_EAGLMLLock lock];
    //_EAGLMLCanDraw = YES;
    //DLog(@"_EAGLMLCanDraw: %d", _EAGLMLCanDraw);
    //[_EAGLMLLock lock];
    //DLog(@"_EAGLMLLock2: %@", _EAGLMLLock);
    //DLog(@"_EAGLMLLock->counter2: %d", _EAGLMLLock->counter);
    //if (_currentMAApplication != maApp) {
    [_uiMAApplication setAsCurrent:YES];
    
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
/*
void UIMLApplicationRunApp(UIMAApplication *maApp)
{
    DLog();
    //maApp.running = YES;
    //[_runningApplicationsDictionary setObject:maApp forKey:[NSString stringWithFormat:@"%p", maApp.screenImageView]];
    //UIApplication *uiApplication = [UIMLApplication sharedMLApplication]->_uiApplication;
    //[_uiApplication->_keyWindow addSubview:maApp.screenImageView];
    [maApp startApp];
}*/

void UIMLApplicationShowLauncher()
{
    DLog();
    if (!_currentMAApplication) {
        return;
    }
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    //UIMAApplicationTakeScreenCaptureIfNeeded(_currentMAApplication);
    IOPipeWriteMessage(MAPipeMessageWillEnterBackground, YES);
    _UIApplicationEnterForeground();
    
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    _currentMAApplication = nil;
    
    _launcherView.hidden = NO;
    //DLog();
    [_uiApplication->_keyWindow performSelector:@selector(bringSubviewToFront:)
                                     withObject:_launcherView
                                     afterDelay:0.1];
    //DLog(@"mlApplication->_launcherView: %@", mlApplication->_launcherView);
#ifdef NA
    [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
#endif
}

void UIMLApplicationGoBack()
{
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    //NSArray *subviews = [_uiApplication->_keyWindow subviews];
    //UIView *currentView;
    //DLog();
    //DLog(@"_runningApplications: %@", _runningApplications);
    //_maAppView.hidden = NO;
    if (!_launcherView.hidden) { //(!_currentMAApplication) {
        DLog(@"!_launcherView.hidden");
        return;
        /*
        if (CFArrayGetCount(_runningApplications) == 0) {
            //if (subviews.count == 1) {
            //DLog(@"CFArrayGetCount(_runningApplications) == 0");
            return;
        } else {
            DLog(@"CFArrayGetCount(_runningApplications) > 0");
            
            UIMLApplicationPresentAppScreen(_currentMAApplication, NO);
            return;
            //currentView = [subviews objectAtIndex:subviews.count-2];
            //currentView.frame = CGRectMake(0,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
            //DLog(@"view: %@", view);
            //UIMAApplication *maApp = [_runningApplications   // objectForKey:[NSString stringWithFormat:@"%p", currentView]];
            //DLog(@"maApp: %@", maApp);
            //[_currentMAApplication setAsCurrent:YES];
            [_uiApplication->_keyWindow bringSubviewToFront:_maAppView];
            _launcherView.hidden = YES;
            _uiMAApplication = _currentMAApplication;
            //UIMLApplicationPresentAppScreen(_currentMAApplication, NO);
        }*/
    } else {
        _maAppView.hidden = NO;
        if (CFArrayGetCount(_runningApplications) == 1) {
            //DLog(@"CFArrayGetCount(_runningApplications) == 1");
            return;
        }
        //currentView = _currentMAApplication.screenImageView;
        //DLog(@"_currentMAApplication: %@", _currentMAApplication);
        IOPipeWriteMessage(MAPipeMessageWillEnterBackground, YES);
        //int currentAppIndex = [_runningApplications indexOfObject:_currentMAApplication];
        CFRange range = {0, CFArrayGetCount(_runningApplications)};
        int currentAppIndex  = CFArrayGetFirstIndexOfValue(_runningApplications, range, _currentMAApplication);
        //DLog(@"currentAppIndex: %d", currentAppIndex);
        if (currentAppIndex == 0) {
            //DLog(@"currentAppIndex == 0");
            //DLog(@"[subviews indexOfObject:_currentMAApplication->_screenImageView] == 1");
            //[UIView beginAnimations:nil context:nil];
            //[UIView setAnimationDuration:0.25];
            //[UIView setAnimationDelegate:[UIMLApplication sharedMLApplication]];
            //[UIView setAnimationDidStopSelector:@selector(goBackDone)];
            //for (int i=2; i<subviews.count; i++) {
            _uiMAApplication = _CFArrayGetLastValue(_runningApplications);//[_runningApplications objectAtIndex:CFArrayGetCount(_runningApplications)-1];
            //currentView = [subviews objectAtIndex:subviews.count-1];
            //currentView.hidden = NO;
            //currentView.frame = CGRectMake(0,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
            //}
            //[UIView commitAnimations];
            //[mlApplication goBackDone];
        } else {
            _uiMAApplication = [_runningApplications objectAtIndex:currentAppIndex-1];
            //DLog(@"_uiMAApplication: %@", _uiMAApplication);
        }
        //UIView *previousView = [subviews objectAtIndex:currentViewIndex-1];
        //UIMAApplication *previousApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", previousView]];
        //DLog(@"previousApp: %@", previousApp);
        //previousView.hidden = NO;
        //previousView.frame = CGRectMake(0,previousView.frame.origin.y,previousView.frame.size.width,previousView.frame.size.height);
        //DLog(@"previousView: %@", previousView);
        //[UIView beginAnimations:nil context:nil];
        //[UIView setAnimationDuration:0.25];
        //currentView.hidden = YES;
        //currentView.frame = CGRectMake(currentView.frame.size.width,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
        //[UIView commitAnimations];
    }
    [_uiMAApplication setAsCurrent:YES];
    //[previousApp setAsCurrent:YES];
    //DLog(@"_currentMAApplication2: %@", _currentMAApplication);
}

void UIMLApplicationMoveCurrentAppToTop()
{
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    if (!_launcherView.hidden) {
        return;
    }
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    //UIView *currentView = _currentMAApplication.screenImageView;
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    //NSArray *subviews = [mlApplication->_uiApplication->_keyWindow subviews];
    int currentAppIndex = [_runningApplications indexOfObject:_currentMAApplication];
    //_currentMAApplication->_needsScreenCapture = YES;
    if (currentAppIndex == CFArrayGetCount(_runningApplications) - 1) {
        return;
    }
    //currentView->_layer.contents = _UIScreenCaptureScreen();
    //UIApplication *uiApplication = mlApplication->_uiApplication;
    //[uiApplication->_keyWindow bringSubviewToFront:currentView];
    //DLog(@"_launcherApp->_keyWindow.subviews: %@", _launcherApp->_keyWindow.subviews);
    //UIMAApplication *currentApp = CFArrayGetValueAtIndex(_runningApplications, _currentAppIndex);
    //if (currentApp != _launcherApp) {
    _currentMAApplication->_score++;
    //}
    _CFArrayMoveValueToTop(_runningApplications, _currentMAApplication);
    //DLog(@"_runningApplications: %@", _runningApplications);
    //_currentAppIndex = CFArrayGetCount(_runningApplications) - 1;
}

void UIMLApplicationTerminateApps()
{
#ifdef NA
    if ([_CAAnimatorNAConditionLock condition] == _CAAnimatorConditionLockHasWork) {
        [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
    }
#endif
    DLog(@"_currentMAApplication: %@", _currentMAApplication);
    IOPipeWriteMessage(MAPipeMessageTerminateApp, YES);
    for (UIMAApplication *maApp in _runningApplications) {
    //for (NSString *key in _runningApplicationsDictionary) {
        //DLog();
        //UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:key];
        //DLog(@"maApp: %@", maApp);
        if (maApp != _currentMAApplication) {
            [maApp terminate];
        }
    }
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
        }
    }
}
