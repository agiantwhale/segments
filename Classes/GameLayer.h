//
//  GameLayer.h
//  CutGame
//
//  Created by 이일재 on 13. 6. 30..
//
//

#ifndef __CutGame__GameLayer__
#define __CutGame__GameLayer__

#include <cocos2d.h>
#include "Rig.h"
#include "GameScene.h"

using namespace cocos2d;

class PolygonNode;
class PieceNode;
class ArrowNode;

struct SliceInfo
{
    int touchId;
    CCPoint beginPoint;
    CCPoint endPoint;
};

class GameLayer : public CCLayer
{
    CC_SYNTHESIZE(ScoreInfo, m_scoreInfo, ScoreInfo);
    CC_SYNTHESIZE_READONLY(ArrowNode*, m_arrowNode, Arrow);
    CC_SYNTHESIZE_READONLY(PieceNode*, m_pieceNode, Piece);
    CC_SYNTHESIZE_READONLY(PolygonNode*, m_goalPolygon, GoalPolygon);
    CC_SYNTHESIZE_READONLY(PolygonNode*, m_slicePolygon, SlicePolygon);
    CC_SYNTHESIZE_READONLY(std::vector<SliceInfo>, m_sliceInfoStack, SliceInfoStack);
    CC_SYNTHESIZE_READONLY(ColorInfo, m_currentColor, CurrentColor);
    
public:
    GameLayer();
    virtual ~GameLayer();
    
    virtual bool initWithColorInfo(const ColorInfo& colorInfo);
    virtual void update(float dt);
    
    static GameLayer *create(const ColorInfo& colorInfo);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    void updateRipples();
    void createRipple(const CCPoint& globalPos);
    
    float m_totalAccuracy;
    float m_rippleTimer;
};

#endif /* defined(__CutGame__GameLayer__) */
