//
//  HudLayer.h
//  segment
//
//  Created by 이일재 on 13. 7. 18..
//
//

#ifndef __segment__HudLayer__
#define __segment__HudLayer__

#include <cocos2d.h>

using namespace cocos2d;

class HudLayer : public CCLayer
{
    CC_SYNTHESIZE_READONLY(CCNode*, m_alignNode, AlignNode);
    
public:
    static HudLayer* create();
    
    HudLayer();
    
    void alignCuts();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void link();
    
private:
    int m_cutCounter;
};

#endif /* defined(__segment__HudLayer__) */
