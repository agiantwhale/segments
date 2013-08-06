//
//  MainMenuLayer.cpp
//  segment
//
//  Created by 이일재 on 13. 8. 6..
//
//

#include "MainMenuLayer.h"

MainMenuLayer* MainMenuLayer::create() {
    MainMenuLayer *pRet = new MainMenuLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
bool MainMenuLayer::init() {
    setKeypadEnabled(true);
    
    return true;
}

void MainMenuLayer::keyBackClicked() {
    CCDirector::sharedDirector()->end();
}
#endif