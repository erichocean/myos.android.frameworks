/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

typedef enum {
    UIMLApplicationScreenDirectionFromRight,
    UIMLApplicationScreenDirectionFromLeft,
    UIMLApplicationScreenDirectionToRight,
    UIMLApplicationScreenDirectionToLeft,
}  UIMLApplicationScreenDirection;

@interface UIMLApplication : NSObject {
@package
    //BOOL _isActive;
}

+ (UIMLApplication *)sharedMLApplication;
- (void)presentAppDone;

@end

void UIMLApplicationInitialize();
void UIMLApplicationLauncherViewDidAdded();
//NSString *UIMLApplicationRunCommand(NSString *command, BOOL usingPipe);
void UIMLApplicationSetChildAppIsRunning(BOOL isRunning);
//void UIMLApplicationLog(NSString *longString);
void UIMLApplicationHandleMessages();
//void UIMLApplicationRunApp(UIMAApplication *maApp);
void UIMLApplicationPresentAppScreen(UIMAApplication *maApp, BOOL coldStart);
void UIMLApplicationMoveCurrentAppToTop();
void UIMLApplicationTerminateApps();
void UIMLApplicationGoBack();
void UIMLApplicationShowLauncher();
