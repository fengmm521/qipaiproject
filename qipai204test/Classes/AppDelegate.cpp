#include "AppDelegate.h"
#include "ShopView.h"
#include "WelcomeView.h"
#include "LoginView.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    //setOrientation(kOrientationLandscapeLeft);
    //CCEGLView::sharedOpenGLView().setDesignResolutionSize(800.0, 480.0);
    pDirector->setOpenGLView(pEGLView);

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    //pDirector->enableRetinaDisplay(true);

    pEGLView->setDesignResolutionSize(800,480, kResolutionShowAll);
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = WelcomeView::CreateScene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
