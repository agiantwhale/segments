//
//  LoseMenuLayer.cpp
//  segment
//
//  Created by 이일재 on 13. 8. 6..
//
//

#include "LoseMenuLayer.h"
#include "LoseScene.h"

LoseMenuLayer* LoseMenuLayer::create() {
    LoseMenuLayer *pRet = new LoseMenuLayer();
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
bool LoseMenuLayer::init() {
    setKeypadEnabled(true);
    
    return true;
}

void LoseMenuLayer::keyBackClicked() {
    LoseScene* scene = (LoseScene*)getParent();
    scene->endCallback();
}
#endif