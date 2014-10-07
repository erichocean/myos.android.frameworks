/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "UIApplicationIcon.h"
#import <UIKit/UIKit-private.h>

#define kImageSize              68
#define _kIconWidth             80
#define _kIconHeight            92
#define _kIconControlMargin     3

#pragma mark - Static functions
/*
static void _UIApplicationIconResetToNormalMode(UIApplicationIcon *applicationIcon)
{
    applicationIcon->_mode = UIApplicationIconModeNormal;
    applicationIcon->_closeControl.hidden = YES;
    applicationIcon->_deleteControl.hidden = YES;
    
    applicationIcon->_menuControl.hidden = YES;
    //applicationIcon->_anchorControl.hidden = YES;
}*/

@implementation UIApplicationIcon

#pragma mark - Life cycle

- (id)initWithApplication:(UIMAApplication *)application
{
    self = [super initWithFrame:CGRectMake(0,0,_kIconWidth,_kIconHeight)];
    if (self) {
        _application = application;
        //DLog(@"imageName: %@", _imageName);
        NSString *imagePath = [NSString stringWithFormat:@"/data/data/com.myos.myapps/apps/%@.app/Icon.png", application->_name];
        //DLog(@"imagePath: %@", imagePath);
        //UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
        _iconImage = [[UIImageView alloc] initWithImage:[UIImage imageWithContentsOfFile:imagePath]];
        //DLog(@"_iconImage: %@", _iconImage);
        _iconImage.frame = CGRectMake(5,5,kImageSize,kImageSize);
        [self addSubview:_iconImage];
        
        _iconLabel = [[UILabel alloc] initWithFrame:CGRectMake(0,kImageSize+5,_kIconWidth,15)];
        _iconLabel.textColor = [UIColor whiteColor];
        _iconLabel.textAlignment = UITextAlignmentCenter;
        _iconLabel.font = [UIFont systemFontOfSize:10];
        _iconLabel.text = application->_name;
        _iconLabel.adjustsFontSizeToFitWidth = YES;
        [self addSubview:_iconLabel];
        
        /*_closeControl = [[UIIconControl alloc] initWithFrame:CGRectMake(_kIconControlMargin,_kIconControlMargin,
                                                                        _kIconControlSize,_kIconControlSize)
                                                     andType:UIIconControlTypeClose];
        [_closeControl addTarget:self action:@selector(iconControlClicked:) forControlEvents:UIControlEventTouchUpInside];
        _closeControl.hidden = YES;
        _closeControl->_applicationIcon = self;
        [self addSubview:_closeControl];
        
        _deleteControl = [[UIIconControl alloc] initWithFrame:CGRectMake(_kIconControlMargin,_kIconControlMargin,
                                                                         _kIconControlSize,_kIconControlSize)
                                                      andType:UIIconControlTypeDelete];
        [_deleteControl addTarget:self action:@selector(iconControlClicked:) forControlEvents:UIControlEventTouchUpInside];
        _deleteControl.hidden = YES;
        _deleteControl->_applicationIcon = self;
        [self addSubview:_deleteControl];
        
        _menuControl = [[UIIconControl alloc] initWithFrame:CGRectMake(_kIconWidth-_kIconControlSize,_kIconControlMargin,
                                                                       _kIconControlSize,_kIconControlSize)
                                                    andType:UIIconControlTypeMenu];
        [_menuControl addTarget:self action:@selector(iconControlClicked:) forControlEvents:UIControlEventTouchUpInside];
        _menuControl.hidden = YES;
        _menuControl->_applicationIcon = self;
        [self addSubview:_menuControl];*/
        
        //_anchorControl = [[UIIconControl alloc] initWithFrame:CGRectMake(_kIconWidth-_kIconControlSize,kImageSize-_kIconControlSize,
        //                                                                 _kIconControlSize,_kIconControlSize)
        //                                              andType:UIIconControlTypeAnchor];
        //[_anchorControl addTarget:self action:@selector(iconControlClicked:) forControlEvents:UIControlEventTouchUpInside];
        //_anchorControl.hidden = YES;
        //_anchorControl->_applicationIcon = self;
        //[self addSubview:_anchorControl];
        
        // Single tap gesture
        UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                                                    action:@selector(singleTapped:)];
        [self addGestureRecognizer:singleTap];
        [singleTap release];
        
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self
                                                                                                  action:@selector(longPressed:)];
        [self addGestureRecognizer:longPress];
        [longPress release];
        
        [singleTap requireGestureRecognizerToFail:longPress];
        
        //_mode = UIApplicationIconModeNormal;
    }
    return self;
}

- (void)dealloc
{
    [_iconImage release];
    [_iconLabel release];
    [super dealloc];
}

#pragma mark - Accessors

#pragma mark - Actions

- (void)singleTapped:(id)sender
{
    //DLog();
    //if (_mode == UIApplicationIconModeNormal) {
        [_application singleTapped];
    //} else {
    //    _UIApplicationIconResetToNormalMode(self);
    //}
}

- (void)longPressed:(id)sender
{
    DLog();
    [_application showMenu];
    /*if (_mode == UIApplicationIconModeNormal) {
        if (_application->_running) {
            _mode = UIApplicationIconModeClose;
            _closeControl.hidden = NO;
        } else {
            _mode = UIApplicationIconModeDelete;
            _deleteControl.hidden = NO;
        }
        _menuControl.hidden = NO;
        //_anchorControl.hidden = NO;
    } else {
        _UIApplicationIconResetToNormalMode(self);
    }*/
}
/*
- (void)iconControlClicked:(UIIconControl *)iconControl
{
    DLog(@"iconControl: %@", iconControl);
    switch (iconControl->_type) {
        case UIIconControlTypeClose:
            [_application closeApp];
            _UIApplicationIconResetToNormalMode(self);
            break;
        case UIIconControlTypeDelete:
            [_application deleteApp];
            _UIApplicationIconResetToNormalMode(self);
            break;
        case UIIconControlTypeMenu:
            [_application showMenu];
            _UIApplicationIconResetToNormalMode(self);
            break;
        case UIIconControlTypeAnchor:
            //[_application anchorClicked];
            _application.anchored = !_application.anchored;
            [iconControl setNeedsDisplay];
            break;
        default:
            break;
    }
}*/

#pragma mark - Public methods

@end
