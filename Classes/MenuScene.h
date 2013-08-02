//
//  MenuScene.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 5..
//
//

#ifndef __CutGame__MenuScene__
#define __CutGame__MenuScene__

#include <cocos2d.h>

using namespace cocos2d;

class MenuScene : public CCScene
{
public:
    static MenuScene* create();
    
    virtual bool init();
    
    void startGame();
    void showScore();
};

#endif /* defined(__CutGame__MenuScene__) */
