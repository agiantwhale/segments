//
//  GameLayer.cpp
//  CutGame
//
//  Created by 이일재 on 13. 6. 30..
//
//

#include "Global.h"
#include "GameLayer.h"
#include "PolygonNode.h"
#include "RippleNode.h"
#include "PieceNode.h"
#include "ArrowNode.h"
#include <SimpleAudioEngine.h>

void GameLayer::updateRipples() {
    for(int i = 0; i < m_sliceInfoStack.size(); i++) {
        createRipple(m_sliceInfoStack[i].beginPoint);
        createRipple(m_sliceInfoStack[i].endPoint);
    }
}

void GameLayer::createRipple(const CCPoint& globalPos)
{
    CCSprite* singleRippleNode = CCSprite::create("ripple.png");
    singleRippleNode->setScale(0.f);
    singleRippleNode->setPosition(globalPos);
    
    CCSpawn* rippleAction = CCSpawn::create
    (
        CCScaleTo::create(0.5f, 1.f),
        CCFadeOut::create(0.5f),
        NULL
    );
    
    CCSequence* rippleSequence = CCSequence::create(
        rippleAction,
        CCRemoveSelf::create(),
        NULL
    );
    
    singleRippleNode->runAction(rippleSequence);
    
    addChild(singleRippleNode, 2);
}

void FadePolygon(PolygonNode* polygon, const CCPoint& targetPos, float fadeTime)
{
    CCSequence* fadeSequence = CCSequence::create
    (
     CCSpawn::create(CCMoveTo::create(fadeTime, targetPos),
                     CCScaleBy::create(fadeTime, 1.25f),
                     CCFadeOut::create(fadeTime),
                     NULL),
     CCDelayTime::create(fadeTime),
     CCRemoveSelf::create(),
     NULL
    );
    
    polygon->runAction(fadeSequence);
}

PolygonNode* CreateFadingPolygon(const Rig& rig, const ccColor4B& fillColor, const ccColor4B& outlineColor, const CCPoint& oldPos, const CCPoint& targetPos, float fadeTime)
{
    PolygonNode* returnPolygon = PolygonNode::createWithRig(rig, fillColor, outlineColor);
    
    returnPolygon->setPosition(oldPos);
    FadePolygon(returnPolygon, targetPos, fadeTime);
    
    return returnPolygon;
}

struct RigAreaSort
{
    bool operator() (Rig i,Rig j) {return RigArea(i) < RigArea(j); }
};

GameLayer::GameLayer()
{
    m_totalAccuracy = 0.f;
    
    m_arrowNode = NULL;
    m_pieceNode = NULL;
    m_goalPolygon = NULL;
    m_slicePolygon = NULL;
}

GameLayer::~GameLayer()
{
}

void GameLayer::update(float dt)
{
    m_pieceNode->setSliceInfoStack(m_sliceInfoStack);
    m_arrowNode->setSliceInfoStack(m_sliceInfoStack);
}

bool GameLayer::initWithColorInfo(const ColorInfo& colorInfo)
{
    m_currentColor = colorInfo;
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    const CCSize windowsSize = CCDirector::sharedDirector()->getWinSize();
    const CCPoint midPoint = ccpMult(CCPointMake(windowsSize.width, windowsSize.height),0.5f);
    
    Rig randomRig;
    RigRandom(randomRig);
    
    while (RigArea(randomRig) < pow(RIG_MIN_RADIUS(), 2.f) * 10.f ) {
        randomRig.clear();
        RigRandom(randomRig);
    }
    
    //Create the slice polygon node.
    m_slicePolygon = PolygonNode::createWithRig(randomRig, m_currentColor.getFillColor(), m_currentColor.getOutlineColor());
    addChild(m_slicePolygon);
    m_slicePolygon->setPosition(midPoint);
    
    m_pieceNode = PieceNode::create(m_currentColor.getPieceColor());
    m_slicePolygon->addChild(m_pieceNode);
     
    m_arrowNode = ArrowNode::create(m_currentColor.getArrowColor());
    addChild(m_arrowNode, 1);
    
    const int MIN_CUTS = 1;
    const int MAX_CUTS = MIN(RIG_VERTEXES(), 5);
    g_rigCut = MIN_CUTS + static_cast<int>( (MAX_CUTS - MIN_CUTS) * CCRANDOM_0_1() );
    
    Rig goalRig = randomRig;
    std::vector<Rig> divRigs;
    for(int i = 0; i < RIG_CUT(); )
    {
        CCPoint cutStart = CCPointMake(CCRANDOM_MINUS1_1() * RIG_MAX_RADIUS(),CCRANDOM_MINUS1_1() * RIG_MAX_RADIUS());
        CCPoint cutEnd = CCPointMake(CCRANDOM_MINUS1_1() * RIG_MAX_RADIUS(),CCRANDOM_MINUS1_1() * RIG_MAX_RADIUS());
        
        
        if(RigSplit(cutStart, cutEnd, goalRig, divRigs))
        {
            int closestRigNum = 0;
            for(int v = 0; v < divRigs.size(); v++)
            {
                if( RigArea(divRigs[v]) > RigArea(divRigs[closestRigNum]))
                {
                    closestRigNum = v;
                }
            }
            
            goalRig = divRigs[closestRigNum];
            divRigs.clear();
            
            i++;
        }
    }
    
    const float MIN_SCALE = 0.5f;
    const float MAX_SCALE = 0.7f;
    
    m_goalPolygon = PolygonNode::createWithRig(goalRig, ccc4(255,255,255,255), ccc4(255,255,255,255), false);
    addChild(m_goalPolygon,1);
    m_goalPolygon->setPosition(ccpSub(midPoint, RigCenter(goalRig)));
    m_goalPolygon->setScale( (MIN_SCALE + (MAX_SCALE - MIN_SCALE) * CCRANDOM_0_1()) );
    
    CCRepeatForever* ripples = CCRepeatForever::create(
                                                       CCSequence::create(
                                                                          CCDelayTime::create(0.25f),
                                                                          
                                                                          CCCallFunc::create(this, callfunc_selector(GameLayer::updateRipples)
                                                                                             ),
                                                                          
                                                                          NULL
                                                                          )
                                                       );
    runAction(ripples);
    
    
    scheduleUpdate();
    
    return true;
}

GameLayer* GameLayer::create(const ColorInfo& colorInfo)
{
    GameLayer *pRet = new GameLayer();
    if (pRet && pRet->initWithColorInfo(colorInfo))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    GameScene* gameScene = (GameScene*)getParent();
    
    if( gameScene->getLevelState() != LEVEL_LOSE )
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bell.wav");
        
        SliceInfo info;
        info.touchId = pTouch->getID();
        info.beginPoint = pTouch->getStartLocation();
        info.endPoint = pTouch->getLocation();
        
        m_sliceInfoStack.push_back(info);
    }
    
    return true;
}
void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    for(int i = 0; i < m_sliceInfoStack.size(); i++)
    {
        SliceInfo& info = m_sliceInfoStack[i];
        if(info.touchId == pTouch->getID())
        {
            info.endPoint = pTouch->getLocation();
        }
    }
}

bool RigAreaCompare(Rig i, Rig j) { return RigArea(i)<RigArea(j); }

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    for(int i = 0; i < m_sliceInfoStack.size(); i++)
    {
        SliceInfo& info = m_sliceInfoStack[i];
        if(info.touchId == pTouch->getID())
        {
            m_sliceInfoStack.erase(m_sliceInfoStack.begin() + i);
            break;
        }
    }
    
    GameScene* gameScene = (GameScene*)getParent();
    if(gameScene->getLevelState() != LEVEL_GAME) return;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bell.wav");
    
    CCPoint startPoint = CCPointApplyAffineTransform( pTouch->getStartLocation(), m_slicePolygon->worldToNodeTransform());
    CCPoint endPoint = CCPointApplyAffineTransform( pTouch->getLocation(), m_slicePolygon->worldToNodeTransform());
    
    CCPoint oldPos = m_slicePolygon->getPosition();
    CCPoint oldCenter = RigCenter(m_slicePolygon->getRig());
    std::vector<Rig> splittedRigs;
    if(RigSplit(startPoint, endPoint, m_slicePolygon->getRig(), splittedRigs))
    {
        m_scoreInfo.cuts++;
        g_rigCut--;
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ding.wav");
        
        m_slicePolygon->removeFromParent();
        m_slicePolygon = NULL;
        
        std::vector<Rig>::iterator nextPolygon = std::max_element(splittedRigs.begin(), splittedRigs.end(), RigAreaCompare);
        
        m_slicePolygon = PolygonNode::createWithRig(*nextPolygon, m_currentColor.getFillColor(), m_currentColor.getOutlineColor() );
        m_slicePolygon->setPosition(oldPos);
        addChild(m_slicePolygon);
        
        m_pieceNode = PieceNode::create(m_currentColor.getPieceColor());
        m_slicePolygon->addChild(m_pieceNode);
        
        const CCSize windowsSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint midPoint = ccpMult(CCPointMake(windowsSize.width, windowsSize.height),0.5f);
        m_slicePolygon->runAction(CCMoveTo::create(0.25f, ccpSub(midPoint, RigCenter(*nextPolygon))));
        
        for(std::vector<Rig>::iterator iter = splittedRigs.begin(); iter != splittedRigs.end(); iter++) {
            if(iter == nextPolygon) continue;
            
            CCPoint center = RigCenter(*iter);
            PolygonNode* newPolygon = PolygonNode::createWithRig(*iter, m_currentColor.getPieceColor(), m_currentColor.getOutlineColor() );
            newPolygon->setPosition(oldPos);
            addChild(newPolygon);
            FadePolygon(newPolygon, ccpAdd(oldPos, ccpSub(oldCenter, center)), 0.6f);
        }
        
        float similarity = 0.f;
        if( RigSimilar(*nextPolygon, m_goalPolygon->getRig(), similarity) )
        {
            gameScene->setLevelState(LEVEL_WIN);
            
            m_scoreInfo.level = RIG_VERTEXES();
            m_scoreInfo.accuracy += similarity;
            
            gameScene->setScoreInfo(m_scoreInfo);
            
            g_rigVertexes++;
            
            const CCSize windowsSize = CCDirector::sharedDirector()->getWinSize();
            CCPoint midPoint = ccpMult(CCPointMake(windowsSize.width, windowsSize.height),0.5f);
            CCPoint rigCenter = RigCenter(m_slicePolygon->getRig());
            
            float slice = RigArea(m_slicePolygon->getRig());
            float goal = RigArea(m_goalPolygon->getRig());
            float scale = sqrtf(slice/goal);
            
            m_slicePolygon->stopAllActions();
            
            CCSequence* winSequence = CCSequence::create
            (
             //Move the slice node to the goal node.
             CCSpawn::create(CCMoveTo::create(0.25f, ccpSub(midPoint, rigCenter)),
                             CCRotateTo::create(0.25f, m_goalPolygon->getRotation()),
                             CCScaleTo::create(0.25f, m_goalPolygon->getScale() * scale),
                             NULL),
             
             //Wait 100 milliseconds.
             CCDelayTime::create(0.1f),
             
             //Spawn out the node.
             CCSpawn::create(CCScaleBy::create(0.5f, 1.25f),
                             CCFadeOut::create(0.5f),
                             NULL),
             
             CCDelayTime::create(0.25f),
             
             CCCallFunc::create(gameScene, callfunc_selector(GameScene::resetGame)),
             
             NULL
             );
            
            m_slicePolygon->runAction(winSequence);
            
            int percentage = static_cast<int>( similarity * 100.f );
            CCString* labelString = CCString::createWithFormat("%i%%", percentage);
            CCLabelTTF* label = CCLabelTTF::create(labelString->getCString(), DEFAULT_FONT, DEFAULT_LABEL_SIZE * g_screenScale);
            label->setPosition(midPoint);
            label->setVisible(false);
            addChild(label);
            
            CCSequence* labelSequence = CCSequence::create
            (
             //Wait 100 milliseconds.
             CCDelayTime::create(0.35f),
             
             CCShow::create(),
             
             //Spawn out the node.
             CCSpawn::create(CCScaleBy::create(0.5f, 1.25f),
                             CCFadeOut::create(0.5f),
                             NULL),
             
             NULL
             );
            
            label->runAction(labelSequence);
            
            CCSequence* goalSequence = CCSequence::create
            (
             //Wait 100 milliseconds.
             CCDelayTime::create(0.35f),
             
             //Spawn out the node.
             CCSpawn::create(CCScaleBy::create(0.5f, 1.25f),
                             CCFadeOut::create(0.5f),
                             NULL),
             
             NULL
             );
            
            m_goalPolygon->runAction(goalSequence);
        }
        else if(RIG_CUT() <= 0)
        {
            gameScene->loseGame();
        }
    }
}

void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    for(int i = 0; i < m_sliceInfoStack.size(); i++)
    {
        SliceInfo& info = m_sliceInfoStack[i];
        if(info.touchId == pTouch->getID())
        {
            m_sliceInfoStack.erase(m_sliceInfoStack.begin() + i);
            break;
        }
    }
}