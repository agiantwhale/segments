//
//  CutGameAppDelegate.cpp
//  CutGame
//
//  Created by 이일재 on 13. 6. 30..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//

#include "AppDelegate.h"
#include "Global.h"
#include "cocos2d.h"
#include "Rig.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    srand(time(NULL));
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    LoadScoreInfo();
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pView);
    
    // turn on display FPS
    //pDirector->setDisplayStats(true);
    
    //Multi-device scaling magic.
    const CCSize& screenSize = CCDirector::sharedDirector()->getWinSize();
    g_rigMaxRadius = MIN(screenSize.width, screenSize.height) * 0.4f;
    g_rigMinRadius = g_rigMaxRadius * 0.1f;
    
    CCFileUtils::sharedFileUtils()->purgeCachedEntries();
    std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if(CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad)
    {
        if(screenSize.width != 768)
        {
            //iPad 3+
            g_screenScale = 4.f;
            searchPaths.insert(searchPaths.begin(),"HDR");
        }
        else
        {
            //iPad 1~2
            g_screenScale = 2.f;
            searchPaths.insert(searchPaths.begin(),"HD");
        }
    }
    else
    {
        if(screenSize.width != 320)
        {
            //iPhone 4+
            g_screenScale = 2.f;
            searchPaths.insert(searchPaths.begin(),"HD");
        }
        else
        {
            g_screenScale = 1.f;
            searchPaths.insert(searchPaths.begin(),"SD");
        }
    }
#endif
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //Extra code.
    g_screenScale = 2.f;
    searchPaths.insert(searchPaths.begin(),"HD");
#endif
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
    CCScene* pScene = MenuScene::create();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
