//
//  LoseScene.h
//  segment
//
//  Created by 이일재 on 13. 7. 11..
//
//

#ifndef __segment__LoseScene__
#define __segment__LoseScene__

#include <cocos2d.h>
#include "Global.h"

using namespace cocos2d;

class LoseScene : public CCScene
{
public:
    static LoseScene* create(const ScoreInfo& info);
    
    virtual bool initWithScore(const ScoreInfo& info);

    void retryCallback();
    void endCallback();
};

#endif /* defined(__segment__LoseScene__) */
