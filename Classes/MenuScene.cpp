//
//  MenuScene.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 5..
//
//

#include "Global.h"
#include "ScoreScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "MainMenuLayer.h"

MenuScene* MenuScene::create()
{
    MenuScene* pRet = new MenuScene();
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

bool MenuScene::init()
{
    CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(backgroundColor);
    
    CCLayer* menuLayer = MainMenuLayer::create();
    addChild(menuLayer);

    const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
    const CCPoint& theMidPoint = ccp(windowSize.width * 0.5f, windowSize.height * 0.5f);
    CCSprite* logo = CCSprite::create("logo.png");
    logo->setAnchorPoint(ccp(0.5f,0.5f));
    logo->setPosition(theMidPoint);
    menuLayer->addChild(logo);
    
    CCMenu* menu = CCMenu::create();
    menu->setPosition(ccp( windowSize.width * 0.5f, windowSize.height * 0.25f ));
    menuLayer->addChild(menu);
    
    CCMenuItemImage* play = CCMenuItemImage::create("play.png", "play_sel.png");
    play->setTarget(this, menu_selector(MenuScene::startGame));
    
    CCMenuItemImage* score = CCMenuItemImage::create("score.png", "score_sel.png");
    score->setTarget(this, menu_selector(MenuScene::showScore));
    
    CCMenuItemImage* config = CCMenuItemImage::create("settings.png", "settings_sel.png");
    
    menu->addChild(play);
    menu->addChild(score);
    menu->addChild(config);
    
    menu->alignItemsHorizontallyWithPadding(windowSize.width / 20.f);
    
    return true;
}

void MenuScene::startGame()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.25f, GameScene::create());
    CCDirector::sharedDirector()->replaceScene(fade);
}

void MenuScene::showScore()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.25f, ScoreScene::create());
    CCDirector::sharedDirector()->replaceScene(fade);
}