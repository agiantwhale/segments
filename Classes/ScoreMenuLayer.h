//
//  ScoreMenuLayer.h
//  segment
//
//  Created by 이일재 on 13. 8. 6..
//
//

#ifndef __segment__ScoreMenuLayer__
#define __segment__ScoreMenuLayer__

#include <cocos2d.h>

using namespace cocos2d;

class ScoreMenuLayer : public CCLayer
{
public:
    static ScoreMenuLayer *create();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    virtual bool init();
    
    virtual void keyBackClicked(void);
#endif
};

#endif /* defined(__segment__ScoreMenuLayer__) */
