//
//  SettingsScene.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 27..
//
//

#include "SettingsScene.h"

SettingsScene* SettingsScene::create()
{
    SettingsScene* pRet = new SettingsScene();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

SettingsScene::SettingsScene()
{
}

bool SettingsScene::init()
{
    CCLayer* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(backgroundColor);
    
    return true;
}

void SettingsScene::update(float dt)
{
}