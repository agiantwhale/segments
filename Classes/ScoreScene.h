//
//  ScoreScene.h
//  segment
//
//  Created by 이일재 on 13. 7. 11..
//
//

#ifndef __segment__ScoreScene__
#define __segment__ScoreScene__

#include <cocos2d.h>

using namespace cocos2d;

class ScoreScene : public CCScene
{
public:
    static ScoreScene* create();
    
    virtual bool init();

    void pop();
};

#endif /* defined(__segment__ScoreScene__) */
