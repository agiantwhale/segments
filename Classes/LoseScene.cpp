//
//  LoseScene.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 11..
//
//

#include "Global.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "LoseScene.h"

LoseScene* LoseScene::create(const ScoreInfo& info)
{
    LoseScene* pRet = new LoseScene();
    if (pRet && pRet->initWithScore(info))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool LoseScene::initWithScore(const ScoreInfo& info)
{
    if(g_scoreInfo.level < info.level)
    {
        g_scoreInfo.level = info.level;
        g_scoreInfo.accuracy = info.accuracy;
        SaveScoreInfo(g_scoreInfo);
    }
    
    CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(backgroundColor);
    
    CCLayer* menuLayer = CCLayer::create();
    addChild(menuLayer);
    
    const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
    const CCPoint& midPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.5f);
    const CCPoint& lowerPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.25f);
    CCSprite* scoreboard = CCSprite::create("board.png");
    scoreboard->setPosition(midPoint);
    menuLayer->addChild(scoreboard);
    
    CCMenu* menu = CCMenu::create();
    menu->setPosition(lowerPoint);
    CCMenuItemImage* retry = CCMenuItemImage::create("retry.png", "retry_sel.png");
    retry->setTarget(this, menu_selector(LoseScene::retryCallback));
    menu->addChild(retry);
    
    CCMenuItemSprite* end = CCMenuItemImage::create("end.png", "end_sel.png");
    end->setTarget(this, menu_selector(LoseScene::endCallback));
    menu->addChild(end);
    
    menu->alignItemsHorizontally();
    
    menuLayer->addChild(menu);
    
    CCString* string = CCString::createWithFormat("You've made it to %i-gon!", info.level);
    CCLabelTTF* label = CCLabelTTF::create(string->getCString(), DEFAULT_FONT, DEFAULT_LABEL_SIZE * SCREEN_SCALE());
    label->setColor(ccBLACK);
    label->setPosition(ccp(scoreboard->getContentSize().width * 0.5f, scoreboard->getContentSize().height * 4.f / 5.f));
    scoreboard->addChild(label);
    
    float accuracy = info.accuracy / (float)(info.level-2) * 100.f;
    CCString* accuracyString = CCString::createWithFormat("with %.2f average accuracy", accuracy);
    CCLabelTTF* accuracyLabel = CCLabelTTF::create(accuracyString->getCString(), DEFAULT_FONT, DEFAULT_LABEL_SIZE * SCREEN_SCALE());
    accuracyLabel->setColor(ccBLACK);
    accuracyLabel->setPosition(ccp(scoreboard->getContentSize().width * 0.5f, scoreboard->getContentSize().height * 3.f / 5.f));
    scoreboard->addChild(accuracyLabel);
    
    return true;
}

void LoseScene::retryCallback()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.25f, GameScene::create());
    CCDirector::sharedDirector()->replaceScene(fade);
}

void LoseScene::endCallback()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.25f, MenuScene::create());
    CCDirector::sharedDirector()->replaceScene(fade);
}