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
    {
        ColorInfo info(
                       ccc4(83, 204, 92, 255),  //Fill
                       ccc4(76, 127, 80, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(45, 255, 61, 150),  //Piece
                       ccc4(52, 127, 57, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(83, 204, 200, 255),  //Fill
                       ccc4(81, 127, 126, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(45, 255, 247, 150),  //Piece
                       ccc4(52, 127, 125, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(83, 114, 204, 255),  //Fill
                       ccc4(85, 96, 127, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(45, 99, 255, 150),  //Piece
                       ccc4(52, 71, 127, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    } 
    
    {
        ColorInfo info(
                       ccc4(196, 83, 204, 255),  //Fill
                       ccc4(124, 77, 127, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(240, 45, 255, 150),  //Piece
                       ccc4(122, 52, 127, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(204, 83, 106, 255),  //Fill
                       ccc4(127, 78, 88, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(255, 45, 84, 150),  //Piece
                       ccc4(127, 52, 66, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(204, 114, 83, 255),  //Fill
                       ccc4(153, 86, 62, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(204, 79, 36, 150),  //Piece
                       ccc4(76, 43, 31, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(204, 177, 83, 255),  //Fill
                       ccc4(153, 133, 62, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(204, 166, 36, 150),  //Piece
                       ccc4(76, 66, 31, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(204, 200, 83, 255),  //Fill
                       ccc4(153, 150, 62, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(204, 198, 36, 150),  //Piece
                       ccc4(76, 75, 31, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(146, 204, 83, 255),  //Fill
                       ccc4(109, 153, 62, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(123, 204, 36, 150),  //Piece
                       ccc4(55, 76, 31, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    {
        ColorInfo info(
                       ccc4(83, 204, 144, 255),  //Fill
                       ccc4(62, 153, 108, 255),  //Outline
                       ccc4(255, 255, 255, 255),//Arrow
                       ccc4(36, 204, 121, 150),  //Piece
                       ccc4(31, 76, 54, 255)   //Background
                       );
        
        ccColor4B fillColor = info.getFillColor();
        ccColor4B arrowColor = ccc4(255-fillColor.r, 255-fillColor.g, 255-fillColor.b, 255);
        info.setArrowColor(arrowColor);
        
        m_colorInfoStack.push_back(info);
    }
    
    g_rigVertexes = 3;
    m_scoreInfo.level = 3;
    
    resetGame();
    
    return true;
}

void GameScene::resetGame()
{
    removeAllChildren();
    
    ColorInfo randomColor = m_colorInfoStack[ rand() % m_colorInfoStack.size() ];
    
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