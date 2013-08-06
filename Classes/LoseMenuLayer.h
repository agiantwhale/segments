//
//  LoseMenuLayer.h
//  segment
//
//  Created by 이일재 on 13. 8. 6..
//
//

#ifndef __segment__LoseMenuLayer__
#define __segment__LoseMenuLayer__

#include <cocos2d.h>

using namespace cocos2d;

class LoseMenuLayer : public CCLayer
{
public:
    static LoseMenuLayer *create();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    virtual bool init();
    
    virtual void keyBackClicked(void);
#endif
};

#endif /* defined(__segment__LoseMenuLayer__) */
