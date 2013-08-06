//
//  ScoreScene.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 11..
//
//

#include "Global.h"
#include "Rig.h"
#include "MenuScene.h"
#include "ScoreScene.h"
#include "PolygonNode.h"
#include "ScoreMenuLayer.h"

ScoreScene* ScoreScene::create()
{
    ScoreScene* pRet = new ScoreScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool ScoreScene::init()
{
    CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(backgroundColor);
    
    CCLayer* menuLayer = ScoreMenuLayer::create();
    addChild(menuLayer);
    
    const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
    const CCPoint midPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.5f);
    const CCPoint lowerPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.15f);
    const CCPoint scorePoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.65f);
    const CCPoint accuracyPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.55f);
    
    CCSprite* scoreboard = CCSprite::create("scoreboard.png");
    scoreboard->setAnchorPoint(ccp(0.5f,0.5f));
    scoreboard->setPosition(midPoint);
    menuLayer->addChild(scoreboard);
    
    CCMenu* menu = CCMenu::create();
    menu->setPosition(lowerPoint);
    CCMenuItemImage* back = CCMenuItemImage::create("back.png", "back_sel.png");
    back->setTarget(this, menu_selector(ScoreScene::pop));
    menu->addChild(back);
    
    menu->alignItemsHorizontallyWithPadding(20 * SCREEN_SCALE());
    
    menuLayer->addChild(menu);
    
    CCString* highscore = CCString::createWithFormat("%i-gon", g_scoreInfo.level);
    CCLabelTTF* label = CCLabelTTF::create(highscore->getCString(), DEFAULT_FONT, DEFAULT_LABEL_SIZE * SCREEN_SCALE() * 1.5f);
    label->setColor(ccBLACK);
    label->setPosition(scorePoint);
    menuLayer->addChild(label);
    
    float accuracyf = g_scoreInfo.accuracy / (float)(g_scoreInfo.level-2) * 100.f;
    CCString* accuracy = CCString::createWithFormat("with %.2f average accuracy.", accuracyf);
    CCLabelTTF* accuracyLabel = CCLabelTTF::create(accuracy->getCString(), DEFAULT_FONT, DEFAULT_LABEL_SIZE * SCREEN_SCALE() * 0.75f);
    accuracyLabel->setColor(ccBLACK);
    accuracyLabel->setPosition(accuracyPoint);
    menuLayer->addChild(accuracyLabel);
    
    return true;
}

void ScoreScene::pop()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.25f, MenuScene::create());
    CCDirector::sharedDirector()->replaceScene(fade);
}