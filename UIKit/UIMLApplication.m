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
//#define _kCaptureScreenTimeLimit      2.0
#define _kGobackTimeLimit               1.0

static NSMutableDictionary *_runningApplicationsDictionary;
static BOOL _childAppRunning = NO;
static UIMLApplication *_mlApp = nil;
static CFTimeInterval _startTime;
static CFTimeInterval _lastGobackTime = 0;

#pragma mark - Static functions

@implementation UIMLApplication

#pragma mark - Life cycle

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
}

#pragma mark - Class methods

+ (UIMLApplication *)sharedMLApplication
{
    if (!_mlApp) {
        _mlApp = [[UIMLApplication alloc] init];
    }
    return _mlApp;
}

#pragma mark - Accessors

#pragma mark - Other delegates

- (void)presentAppDone
{
    [_uiApplication->_keyWindow sendSubviewToBack:_launcherView];
    _launcherView.hidden = YES;
    //DLog();
    _UIApplicationEnterBackground();
    NSArray *subviews = [_uiApplication->_keyWindow subviews];
    UIView *view = [subviews objectAtIndex:subviews.count-1];
    UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", view]];
    //DLog(@"maApp: %@", maApp);
    //[_EAGLMLLock lock];
    //_EAGLMLCanDraw = YES;
    //DLog(@"_EAGLMLCanDraw: %d", _EAGLMLCanDraw);
    //[_EAGLMLLock lock];
    //DLog(@"_EAGLMLLock: %@", _EAGLMLLock);
    //[_EAGLMLLock lock];
    //[_EAGLMLLock unlock];
    //DLog(@"_EAGLMLLock2: %@", _EAGLMLLock);
    //DLog(@"_EAGLMLLock->counter2: %d", _EAGLMLLock->counter);
    if (_currentMAApplication != maApp) {
        [maApp setAsCurrent:YES];
    }
    _lastGobackTime = CACurrentMediaTime();
}

- (void)goBackDone
{
    //UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    NSArray *subviews = [_uiApplication->_keyWindow subviews];
    UIView *currentView = [subviews objectAtIndex:subviews.count-1];
    UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", currentView]];
    [maApp setAsCurrent:YES];
}

@end

#pragma mark - Shared functions

void UIMLApplicationInitialize()
{
    //DLog(@"UIMLApplicationInitialize");
    //_runningApplications = CFArrayCreateMutable(kCFAllocatorDefault, 5, &kCFTypeArrayCallBacks);
    //_launcherApp = [UIApplication sharedApplication];
    //CFArrayAppendValue(_runningApplications, _launcherApp);
    _runningApplicationsDictionary = [[NSMutableDictionary alloc] init];
    
    //_EAGLMLLock = [[NSLock alloc] init];
    //DLog(@"_EAGLMLLock: %@", _EAGLMLLock);
    //[_EAGLMLLock lock];
}

void UIMLApplicationLauncherViewDidAdded()
{
    //DLog(@"_launcherApp->_keyWindow: %@", _launcherApp->_keyWindow);
    UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    //DLog();
    mlApplication->_launcherView = [[mlApplication->_uiApplication->_keyWindow subviews] objectAtIndex:0];
}

void UIMLApplicationSetChildAppIsRunning(BOOL isRunning)
{
    _startTime = CACurrentMediaTime();
    //DLog(@"_startTime: %f", _startTime);
    _childAppRunning = isRunning;
#ifdef NA
    EAGLMLSetChildAppIsRunning(isRunning);
#endif
}

void UIMLApplicationPresentAppScreen(UIMAApplication *maApp, float animationDuration)
{
    //DLog();
    UIApplication *uiApplication = [UIMLApplication sharedMLApplication]->_uiApplication;
    //DLog(@"currentView: %@", currentView);
    [uiApplication->_keyWindow bringSubviewToFront:maApp->_screenImageView];
    
    maApp->_screenImageView.frame = CGRectMake(0,0,uiApplication->_keyWindow.frame.size.width,uiApplication->_keyWindow.frame.size.height);
    //DLog(@"maApp->_screenImageView: %@", maApp->_screenImageView);
    maApp->_screenImageView.hidden = NO;
    maApp->_screenImageView.alpha = 0;
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationCurve:UIViewAnimationCurveLinear];
    [UIView setAnimationDuration:animationDuration];
    [UIView setAnimationDelegate:[UIMLApplication sharedMLApplication]];
    [UIView setAnimationDidStopSelector:@selector(presentAppDone)];
    
    maApp->_screenImageView.alpha = 1;
    //maApp->_screenImageView.frame = CGRectMake(0,0,uiApplication->_keyWindow.frame.size.width,uiApplication->_keyWindow.frame.size.height);
    [UIView commitAnimations];
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

void UIMLApplicationRunApp(UIMAApplication *maApp)
{
    //DLog();
    maApp.running = YES;
    [_runningApplicationsDictionary setObject:maApp forKey:[NSString stringWithFormat:@"%p", maApp->_screenImageView]];
    UIApplication *uiApplication = [UIMLApplication sharedMLApplication]->_uiApplication;
    [uiApplication->_keyWindow addSubview:maApp->_screenImageView];
    [maApp startApp];
}

void UIMLApplicationShowLauncher()
{
    //DLog();
    if (!_currentMAApplication) {
        return;
    }
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    UIMAApplicationTakeScreenCaptureIfNeeded(_currentMAApplication);
    IOPipeWriteMessage(MAPipeMessageWillEnterBackground, YES);
    _UIApplicationEnterForeground();
    
    UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    _currentMAApplication = nil;
    
    mlApplication->_launcherView.hidden = NO;
    //DLog();
    [mlApplication->_uiApplication->_keyWindow performSelector:@selector(bringSubviewToFront:)
                                                    withObject:mlApplication->_launcherView
                                                    afterDelay:0.1];
#ifdef NA
    [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
#endif
}

void UIMLApplicationGoBack()
{
    UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    NSArray *subviews = [mlApplication->_uiApplication->_keyWindow subviews];
    UIView *currentView;
    //DLog();
    //DLog(@"subviews: %@", subviews);
    if (!_currentMAApplication) {
        //DLog(@"!_currentMAApplication");
        if (subviews.count == 1) {
            //DLog(@"subviews.count == 1");
        } else {
            //DLog(@"subviews.count > 1");
            currentView = [subviews objectAtIndex:subviews.count-2];
            currentView.hidden = NO;
            //currentView.frame = CGRectMake(0,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
            
            //DLog(@"view: %@", view);
            UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", currentView]];
            //DLog(@"maApp: %@", maApp);
            [maApp setAsCurrent:YES];
            UIMLApplicationPresentAppScreen(maApp, 0.25);
        }
        return;
    }
    if (subviews.count == 2) {
        //DLog(@"subviews.count == 2");
        return;
    }
    currentView = _currentMAApplication->_screenImageView;
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    
    IOPipeWriteMessage(MAPipeMessageWillEnterBackground, YES);
    
    int currentViewIndex = [subviews indexOfObject:currentView];
    if (currentViewIndex == subviews.count-1) {
        currentView->_layer.contents = _UIScreenCaptureScreen();
    }
    if (currentViewIndex == 1) {
        //DLog(@"currentViewIndex == 1");
        //DLog(@"[subviews indexOfObject:_currentMAApplication->_screenImageView] == 1");
        //[UIView beginAnimations:nil context:nil];
        //[UIView setAnimationDuration:0.25];
        //[UIView setAnimationDelegate:[UIMLApplication sharedMLApplication]];
        //[UIView setAnimationDidStopSelector:@selector(goBackDone)];
        //for (int i=2; i<subviews.count; i++) {
        currentView = [subviews objectAtIndex:subviews.count-1];
        currentView.hidden = NO;
        //currentView.frame = CGRectMake(0,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
        //}
        //[UIView commitAnimations];
        [mlApplication goBackDone];
        return;
    }
    
    UIView *previousView = [subviews objectAtIndex:currentViewIndex-1];
    UIMAApplication *previousApp = [_runningApplicationsDictionary objectForKey:[NSString stringWithFormat:@"%p", previousView]];
    //DLog(@"previousApp: %@", previousApp);
    previousView.hidden = NO;
    //previousView.frame = CGRectMake(0,previousView.frame.origin.y,previousView.frame.size.width,previousView.frame.size.height);
    //DLog(@"previousView: %@", previousView);
    //[UIView beginAnimations:nil context:nil];
    //[UIView setAnimationDuration:0.25];
    currentView.hidden = YES;
    //currentView.frame = CGRectMake(currentView.frame.size.width,currentView.frame.origin.y,currentView.frame.size.width,currentView.frame.size.height);
    //[UIView commitAnimations];
    [previousApp setAsCurrent:YES];
    //DLog(@"_currentMAApplication2: %@", _currentMAApplication);
}

void UIMLApplicationMoveCurrentAppToTop()
{
    //return;
    if (!_currentMAApplication) {
        return;
    }
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    UIView *currentView = _currentMAApplication->_screenImageView;
    UIMLApplication *mlApplication = [UIMLApplication sharedMLApplication];
    NSArray *subviews = [mlApplication->_uiApplication->_keyWindow subviews];
    int currentViewIndex = [subviews indexOfObject:currentView];
    _currentMAApplication->_needsScreenCapture = YES;
    if (currentViewIndex == subviews.count - 1) {
        return;
    }
    //currentView->_layer.contents = _UIScreenCaptureScreen();
    UIApplication *uiApplication = mlApplication->_uiApplication;
    [uiApplication->_keyWindow bringSubviewToFront:currentView];
    //DLog(@"_launcherApp->_keyWindow.subviews: %@", _launcherApp->_keyWindow.subviews);
    //UIMAApplication *currentApp = CFArrayGetValueAtIndex(_runningApplications, _currentAppIndex);
    //if (currentApp != _launcherApp) {
    _currentMAApplication->_score++;
    //}
    //_CFArrayMoveValueToTop(_runningApplications, currentApp);
    //DLog(@"_runningApplications: %@", _runningApplications);
    //_currentAppIndex = CFArrayGetCount(_runningApplications) - 1;
}

void UIMLApplicationTerminateApps()
{
    //DLog(@"_runningApplicationsDictionary: %@", _runningApplicationsDictionary);
    //float timeOut = _kTerminateChildTimeOut;
    //DLog();
    for (NSString *key in _runningApplicationsDictionary) {
        //DLog();
        UIMAApplication *maApp = [_runningApplicationsDictionary objectForKey:key];
        //DLog(@"maApp: %@", maApp);
        //[_runningApplicationsDictionary setObject:nil forKey:maApp->_name];
        //[maApp setAsCurrent:NO];
        if ([maApp isCurrent]) {
            //DLog();
            IOPipeWriteMessage(MAPipeMessageTerminateApp, YES);
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
        //DLog();
        [maApp terminate];
    }
}
