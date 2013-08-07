//
//  GameScene.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 6..
//
//

#include "LoseScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "HudLayer.h"
#include "Global.h"

GameScene* GameScene::create()
{
    GameScene* pRet = new GameScene();
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

GameScene::GameScene()
{
    m_backgroundLayer = NULL;
    m_gameLayer = NULL;
    m_hudLayer = NULL;
}

bool GameScene::init()
{
    g_rigVertexes = 3;
    m_scoreInfo.level = 3;
    
    resetGame();
    
    return true;
}

void GameScene::resetGame()
{
    //Clear all previous game.
    removeAllChildren();
    
    ColorInfo randomColor = RandomColorScheme();
    
    m_backgroundLayer = CCLayerColor::create(randomColor.getBackgroundColor());
    addChild(m_backgroundLayer);
    
    m_gameLayer = GameLayer::create(randomColor);
    m_gameLayer->setScoreInfo(m_scoreInfo);
    addChild(m_gameLayer);
    
    m_levelState = LEVEL_GAME;
    
    CCLayerColor* fadeLayer = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(fadeLayer,2);
    
    CCSequence* sequence = CCSequence::create
    (
        CCFadeOut::create(0.3f),
        CCRemoveSelf::create(),
        NULL
    );
    
    fadeLayer->runAction(sequence);
    
    m_hudLayer = HudLayer::create();
    addChild(m_hudLayer, 1);
    m_hudLayer->link();
}

void GameScene::loseGame()
{
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, LoseScene::create(m_gameLayer->getScoreInfo()));
    CCDirector::sharedDirector()->replaceScene(fade);
}