//
//  TimerNode.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 8..
//
//

#ifndef __CutGame__TimerNode__
#define __CutGame__TimerNode__

#include <cocos2d.h>

using namespace cocos2d;

class TimerNode : public CCNode
{
    CC_SYNTHESIZE_READONLY(CCSprite*, m_timeSprite, TimeSprite);
    CC_SYNTHESIZE_READONLY(float, m_totalTime, TotalTime);
    CC_SYNTHESIZE_READONLY(float, m_remainTime, RemainingTime);
    
public:
    TimerNode();
    
    static TimerNode* create();

    virtual bool init();
    virtual void update(float dt);
    
    void addTime(float time);
};

#endif /* defined(__CutGame__TimerNode__) */
