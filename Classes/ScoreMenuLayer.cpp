//
//  ScoreMenuLayer.cpp
//  segment
//
//  Created by 이일재 on 13. 8. 6..
//
//

#include "ScoreMenuLayer.h"
#include "ScoreScene.h"

ScoreMenuLayer* ScoreMenuLayer::create() {
    ScoreMenuLayer *pRet = new ScoreMenuLayer();
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
bool ScoreMenuLayer::init() {
    setKeypadEnabled(true);
    
    return true;
}

void ScoreMenuLayer::keyBackClicked() {
    ScoreScene* scene = (ScoreScene*)getParent();
    scene->pop();
}
#endif