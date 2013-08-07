//
//  GameScene.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 6..
//
//

#ifndef __CutGame__GameScene__
#define __CutGame__GameScene__

#include <cocos2d.h>
#include "Rig.h"
#include "Global.h"

using namespace cocos2d;

class GameLayer;
class HudLayer;

enum LevelState
{
    LEVEL_WIN,
    LEVEL_GAME,
    LEVEL_LOSE
};

class GameScene : public CCScene
{
    CC_SYNTHESIZE(ScoreInfo, m_scoreInfo, ScoreInfo);
    CC_SYNTHESIZE(LevelState, m_levelState, LevelState);
    CC_SYNTHESIZE_READONLY(CCLayerColor*, m_backgroundLayer, BackgroundLayer);
    CC_SYNTHESIZE_READONLY(GameLayer*, m_gameLayer, GameLayer);
    CC_SYNTHESIZE_READONLY(HudLayer*, m_hudLayer, HudLayer);
    
public:
    static GameScene* create();
    
    GameScene();
    
    virtual bool init();

    void resetGame();
    void loseGame();
};

#endif /* defined(__CutGame__GameScene__) */
