/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <fcntl.h>
#import <UIKit/UIKit-private.h>
#import <IOKit/IOKit.h>
#import <OpenGLES/EAGL-private.h>
#import <CoreGraphics/CoreGraphics-private.h>

NSMutableDictionary *_allApplicationsDictionary;
UIMAApplication *_currentMAApplication = nil;

static NSString *const _kUIMAApplicationPageNumberPath = @"page.pageNumber";
static NSString *const _kUIMAApplicationXLocationPath = @"page.xLocation";
static NSString *const _kUIMAApplicationYLocationPath = @"page.yLocation";
static NSString *const _kUIMAApplicationAnchoredPath = @"page.anchored";
static NSString *const _kUIMAApplicationScorePath = @"application.score";

#pragma mark - Static functions

static void UIMAApplicationRunApp(NSString *appName)
{
    const char *appPath = [[NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/%@", appName, appName] cString];
    const char *cAppName = [appName cString];
    //DLog(@"appPath: %s", appPath);
    char *const args[] = {cAppName, NULL};
    const char *myEnv[] = {"LD_LIBRARY_PATH=/data/data/com.myos.myapps/lib:$LD_LIBRARY_PATH", 0};
    execve(appPath, args, myEnv);
    //DLog();
}

@implementation UIMAApplication

@synthesize name=_name;
@synthesize score=_score;
@dynamic screenImageView;
@dynamic pageNumber;
@dynamic xLocation;
@dynamic yLocation;
@dynamic anchored;

#pragma mark - Life cycle

+ (void)initialize
{
    _allApplicationsDictionary = [[NSMutableDictionary alloc] init];
}

- (id)initWithAppName:(NSString *)name
{
    if ((self=[super init])) {
        _name = name;
        [_allApplicationsDictionary setObject:self forKey:name];
        _running = NO;
        _needsScreenCapture = YES;
        NSString *dataPath = [NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/data.json", _name];
        NSData *data = [NSData dataWithContentsOfFile:dataPath];
        _data = [[NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:NULL] retain];
        //DLog(@"_data: %@", _data);
        int x = [[_data valueForKeyPath:_kUIMAApplicationXLocationPath] intValue];
        int y = [[_data valueForKeyPath:_kUIMAApplicationYLocationPath] intValue];
        _score = [[_data valueForKeyPath:_kUIMAApplicationScorePath] intValue];
        
        _applicationIcon = [[UIApplicationIcon alloc] initWithApplication:self];
        
        //NSString *imagePath = [NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/Default.png", _name];
        //UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
        _screenImageView = nil;//[[UIImageView alloc] initWithImage:image];
        //DLog(@"%@, Loaded _screenImageView: %@", name, _screenImageView);
        
        //DLog(@"x: %d", x);
    }
    return self;
}

- (void)dealloc
{
    [_name release];
    [_data release];
    [_screenImageView release];
    [_applicationIcon release];
    [super dealloc];
}

#pragma mark - Accessors

- (UIImageView *)screenImageView
{
    //DLog();
    if (!_screenImageView) {
        NSString *imagePath = [NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/Default.png", _name];
        UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
        _screenImageView = [[UIImageView alloc] initWithImage:image];
    }
    return _screenImageView;
}

- (void)setScreenImageView:(UIImageView *)screenImageView
{
    if (_screenImageView) {
        [_screenImageView release];
    }
    _screenImageView = [screenImageView retain];
}

- (int)pageNumber
{
    //DLog(@"self: %p", self);
    return [[_data valueForKeyPath:_kUIMAApplicationPageNumberPath] intValue];
}

- (void)setPageNumber:(int)pageNumber
{
    [_data setValue:[NSNumber numberWithInt:pageNumber] forKeyPath:_kUIMAApplicationPageNumberPath];
}

- (int)xLocation
{
    //DLog();
    return [[_data valueForKeyPath:_kUIMAApplicationXLocationPath] intValue];
}

- (void)setXLocation:(int)x
{
    [_data setValue:[NSNumber numberWithInt:x] forKeyPath:_kUIMAApplicationXLocationPath];
}

- (int)yLocation
{
    //DLog();
    return [[_data valueForKeyPath:_kUIMAApplicationYLocationPath] intValue];
}

- (void)setYLocation:(int)y
{
    [_data setValue:[NSNumber numberWithInt:y] forKeyPath:_kUIMAApplicationYLocationPath];
}

- (BOOL)anchored
{
    //DLog();
    return [[_data valueForKeyPath:_kUIMAApplicationAnchoredPath] boolValue];
}

- (void)setAnchored:(BOOL)anchored
{
    [_data setValue:[NSNumber numberWithBool:anchored] forKeyPath:_kUIMAApplicationAnchoredPath];
}

- (BOOL)running
{
    return _running;
}

- (void)setRunning:(BOOL)newValue
{
    //[self willChangeValueForKey:@"running"];
    _running = newValue;
    //DLog(@"self: %@, running: %d", self, _running);
    //[self didChangeValueForKey:@"running"];
    _applicationIcon->_iconLabel.textColor = [UIColor yellowColor]; // orangeColor];
}

- (NSString *)description
{
    //DLog(@"_data: %@", _data);
    return [NSString stringWithFormat:@"<%@: %p; name: %@; running: %d; isCurrent: %d; score: %d; pageNumber: %d; xLocation: %d; yLocation: %d; anchored: %d>", [self className], self, _name, _running, [self isCurrent], _score, self.pageNumber, self.xLocation, self.yLocation, self.anchored];
}

#pragma mark - Data

- (void)swapLocationWithApp:(UIMAApplication *)anotherApp
{
    int tempPageNumber = self.pageNumber;
    self.pageNumber = anotherApp.pageNumber;
    anotherApp.pageNumber = tempPageNumber;
    int tempX = self.xLocation;
    int tempY = self.yLocation;
    self.xLocation = anotherApp.xLocation;
    self.yLocation = anotherApp.yLocation;
    anotherApp.xLocation = tempX;
    anotherApp.yLocation = tempY;
}

#pragma mark - Delegates

- (void)closeApp
{
    DLog(@"self: %@", self);
}

- (void)deleteApp
{
    DLog(@"self: %@", self);
}

- (void)showMenu
{
    DLog(@"self: %@", self);
}
/*
- (void)anchorClicked
{
    DLog(@"self: %@", self);
}*/

#pragma mark - Actions

- (void)singleTapped
{
    //DLog();
    if (!_running) {
        //DLog(@"!_running");
        UIMLApplicationRunApp(self);
        //DLog();
        //[self setAsCurrent:NO];
        UIMLApplicationPresentAppScreen(self, 0.5);
    } else {
        //DLog();
        //[self setAsCurrent:YES];
        UIMLApplicationPresentAppScreen(self, 0.25);
    }
}

#pragma mark - Public methods

- (void)startApp
{
    //return;
    //DLog(@"_name: %@", _name);
    int pipe1[2];
    int pipe2[2];
    
    int animationPipe1[2];
    int animationPipe2[2];
    if (pipe(pipe1)) {
        NSLog(@"Pipe1 failed.");
        return;
    }
    if (pipe(pipe2)) {
        NSLog(@"Pipe2 failed.");
        return;
    }
    if (pipe(animationPipe1)) {
        NSLog(@"Pipe1 failed.");
        return;
    }
    if (pipe(animationPipe2)) {
        NSLog(@"Pipe2 failed.");
        return;
    }
    //DLog(@"_name: %@", _name);
    long flags;
    _pid = fork();
    //DLog(@"pid: %d", pid);
    if (_pid == 0) {
        flags = fcntl(pipe1[0], F_GETFL);
        fcntl(pipe1[0], F_SETFL, flags | O_NONBLOCK);
        //dup(mypipe[0]);
        dup2(pipe1[0], kMainPipeRead);
        dup2(pipe2[1], kMainPipeWrite);
        
        flags = fcntl(animationPipe1[0], F_GETFL);
        fcntl(animationPipe1[0], F_SETFL, flags | O_NONBLOCK);
        //dup(mypipe[0]);
        dup2(animationPipe1[0], _kEAGLMAPipeRead);
        dup2(animationPipe2[1], _kEAGLMAPipeWrite);
        
        //DLog(@"dup2");
        IOPipeSetPipes(kMainPipeRead, kMainPipeWrite);
        //#ifndef NA
        //EAGLMASetPipes(kAnimationPipeRead, kAnimationPipeWrite);
        //#endif
        //DLog();
        IOPipeWriteMessage(MLPipeMessageChildIsReady, YES);
        //DLog();
        //IOPipeWriteMessageWithPipe(EAGLMLMessageChildIsReady, YES, _kEAGLMAPipeWrite);
        //DLog();
        UIMAApplicationRunApp(_name);
    } else {
        int pipeRead = pipe2[0];
        int pipeWrite = pipe1[1];
        flags = fcntl(pipeRead, F_GETFL);
        fcntl(pipeRead, F_SETFL, flags | O_NONBLOCK);
        
        //DLog();
        close(pipe1[0]);
        close(pipe2[1]);
        
        int animationPipeRead = animationPipe2[0];
        int animationPipeWrite = animationPipe1[1];
        flags = fcntl(animationPipeRead, F_GETFL);
        fcntl(animationPipeRead, F_SETFL, flags | O_NONBLOCK);
        //DLog();
        close(animationPipe1[0]);
        close(animationPipe2[1]);
        
        //IOPipeSetPipes(pipeRead, pipeWrite);
        _pipeRead = pipeRead;
        _pipeWrite = pipeWrite;
        _animationPipeRead = animationPipeRead;
        _animationPipeWrite = animationPipeWrite;
        //DLog();
        [self setAsCurrent:NO];
        
        IOPipeWriteMessage(MAPipeMessageCharString, NO);
        IOPipeWriteCharString(_name);
        UIMLApplicationSetChildAppIsRunning(YES);
    }
}

- (BOOL)isCurrent
{
    return (_currentMAApplication == self);
}

- (void)setAsCurrent:(BOOL)withSignal
{
    IOPipeSetPipes(_pipeRead, _pipeWrite);
    _currentMAApplication = self;
    //DLog(@"self: %@", self);
#ifdef NA
    EAGLMLSetPipes(_animationPipeRead, _animationPipeWrite);
    if (withSignal) {
        kill(_pid, SIGALRM);
    }
#endif
    _score++;
}

- (void)terminate
{
    DLog(@"%@", self);
    //_running = NO;
    UIMAApplicationSaveData(self);
    kill(_pid, SIGTERM);
    if (wait(NULL) == -1) {
        NSLog(@"wait error");
    }
}

@end

#pragma mark - Shared functions

void UIMAApplicationTakeScreenCaptureIfNeeded(UIMAApplication *app)
{
    if (app->_needsScreenCapture) {
        app->_screenImageView->_layer.contents = _UIScreenCaptureScreen();
        app->_needsScreenCapture = NO;
    }
}

void UIMAApplicationSaveData(UIMAApplication *app)
{
    NSString *dataPath = [NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/data.json", app->_name];
    //DLog(@"dataPath: %@", dataPath);
    [app->_data setValue:[NSNumber numberWithInt:app->_score] forKeyPath:_kUIMAApplicationScorePath];
    //DLog(@"app->_data: %@", app->_data);
    NSData *data = [NSJSONSerialization dataWithJSONObject:app->_data options:0 error:NULL];
    [data writeToFile:dataPath atomically:YES];
}

void UIMAApplicationClosePipes()
{
    close(kMainPipeRead);
    close(kMainPipeWrite);
}
