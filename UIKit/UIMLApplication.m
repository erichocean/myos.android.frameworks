/*
 Copyright © 2014 myOS Group.
 
 This file is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.
 
 This file is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 Contributor(s):
 Amr Aboelela <amraboelela@gmail.com>
 */

#import <fcntl.h>
#import <UIKit/UIKit-private.h>
#import <IOKit/IOKit.h>
#import <CoreAnimation/CoreAnimation-private.h>
#import <CoreFoundation/CoreFoundation-private.h>

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
static long _freeMemory = NSIntegerMax;
static int _freeMemoryCount = 0;

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

@end

#pragma mark - Shared functions

void UIMLApplicationInitialize()
{
    //DLog(@"UIMLApplicationInitialize");
    _uiApplication = [UIApplication sharedApplication];
    _uiMAApplication = [[UIMAApplication alloc] init];
    //CFArrayAppendValue(_openedApplications, _launcherApp);
    //_openedApplicationsDictionary = [[NSMutableDictionary alloc] init];
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
#ifdef NA
    EAGLMLSetChildAppIsRunning(isRunning);
#endif
}

void UIMLApplicationTerminateSomeApps()
{
    //DLog(@"_openedApplications 1: %@", _openedApplications);
    //NSMutableArray *openedApplications = CFArrayCreateCopy(kCFAllocatorDefault, _openedApplications);
    _freeMemoryCount++;
    int count = _openedApplications.count;
    for (int i=0; i<=count; i++) {
        UIMAApplication *maApp = CFArrayGetValueAtIndex(_openedApplications, 0);
        if (maApp != _currentMAApplication) {
        //DLog(@"Terminating app: %@", maApp);
            [maApp terminate];
            CFArrayRemoveValueAtIndex(_openedApplications, 0);
        } else {
            return;
        }
    }
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
        //DLog(@"%@", maApp->_name);
        //UIMLApplicationCheckMemory();
        [_maAppView addSubview:maApp.defaultScreenView];
        long freeMemory = CFGetFreeMemory();
        DLog(@"%@ Free memory: %ld KB", maApp->_name, freeMemory);
        if (freeMemory > _freeMemory && (_freeMemoryCount % 2 == 0) ||
            freeMemory < 5000 && (_freeMemoryCount % 2 == 1)) {
            DLog(@"Low memory");
            UIMLApplicationTerminateSomeApps();
            freeMemory = CFGetFreeMemory();
            DLog(@"%@ Free memory 2: %ld KB", maApp->_name, freeMemory);
        }
        _freeMemory = freeMemory;
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
    //DLog();
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
    if ([_CAAnimatorNAConditionLock condition] == _CAAnimatorConditionLockHasWork) {
        [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
    }
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
    //_currentMAApplication->_needsScreenCapture = YES;
    /*if (currentAppIndex == CFArrayGetCount(_openedApplications) - 1) {
        return;
    }*/
    _currentMAApplication->_score++;
    //}
    _CFArrayMoveValueToTop(_openedApplications, _currentMAApplication);
    //DLog(@"_openedApplications: %@", _openedApplications);
}

void UIMLApplicationTerminateApps()
{
#ifdef NA
    if ([_CAAnimatorNAConditionLock condition] == _CAAnimatorConditionLockHasWork) {
        [_CAAnimatorNAConditionLock lockWithCondition:_CAAnimatorConditionLockHasNoWork];
    }
#endif
    //DLog(@"_currentMAApplication: %@", _currentMAApplication);
    if (!_currentMAApplication) {
        return;
    }
    if (_currentMAApplication->_running) {
        IOPipeWriteMessage(MAPipeMessageTerminateApp, YES);
    }
    for (UIMAApplication *maApp in _openedApplications) {
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
