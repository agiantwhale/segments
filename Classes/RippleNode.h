//
//  RippleNode.h
//  segment
//
//  Created by 이일재 on 13. 7. 20..
//
//

#ifndef __segment__RippleNode__
#define __segment__RippleNode__

#include <cocos2d.h>

using namespace cocos2d;

class RippleNode : public CCNodeRGBA
{
public:
    static RippleNode* create();
    
    virtual bool init();
    virtual void draw();
};

#endif /* defined(__segment__RippleNode__) */
