//
//  TimerNode.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 8..
//
//

#include "TimerNode.h"
#include "GameScene.h"
#include "Rig.h"

TimerNode::TimerNode()
{
    m_totalTime = 25.f;
    m_remainTime = 0.f;
}

TimerNode* TimerNode::create()
{
    TimerNode* pRet = new TimerNode();
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

bool TimerNode::init()
{
    m_timeSprite = CCSprite::create("timer.png");
    m_timeSprite->setOpacity(150);
    addChild(m_timeSprite);
    
    scheduleUpdate();
    
    return true;
}

void TimerNode::update(float dt)
{
    GameScene* gameScene = (GameScene*)getParent();
    
    m_remainTime -= dt;
    
    if(m_remainTime < 0.f)
    {
        if(gameScene->getLevelState() == LEVEL_GAME)
            gameScene->setLevelState(LEVEL_LOSE);
    }
    
    float maxScale = std::min(m_remainTime/m_totalTime, 1.f);
    maxScale = std::max(0.f, maxScale);
    m_timeSprite->setScale(maxScale);
}

void TimerNode::addTime(float time)
{
    m_remainTime += time;
}