//
//  HudLayer.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 18..
//
//

#include "GameScene.h"
#include "HudLayer.h"
#include "Global.h"
#include "Rig.h"

HudLayer* HudLayer::create()
{
    HudLayer *pRet = new HudLayer();
    if (pRet && pRet->init())
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

HudLayer::HudLayer()
{
    m_cutCounter = 0;
    m_alignNode = NULL;
}

bool HudLayer::init()
{
    const CCSize& size = CCDirector::sharedDirector()->getWinSize();
    const CCPoint cutPos = ccp(size.width * 0.5f, size.height * 0.85f);
    
    m_alignNode = CCNode::create();
    m_alignNode->setPosition(cutPos);
    addChild(m_alignNode);
    
    m_cutCounter = RIG_CUT();
    
    scheduleUpdate();
    
    return true;
}

void HudLayer::update(float dt)
{
    while(RIG_CUT() < m_cutCounter)
    {
        CCArray* childArray = m_alignNode->getChildren();
        CCSprite* cutSprite = (CCSprite*)childArray->objectAtIndex(0);
        
        CCSequence* fadeSequence = CCSequence::create
        (
            CCSpawn::create(
                            CCFadeOut::create(0.25f),
                            CCScaleBy::create(0.25f, 2.5f),
                            NULL),
            CCRemoveSelf::create(),
            CCCallFunc::create(this, callfunc_selector(HudLayer::alignCuts)),
            NULL
        );
        cutSprite->runAction(fadeSequence);
        
        m_cutCounter--;
    }
}

void HudLayer::alignCuts()
{
    CCArray* children = m_alignNode->getChildren();
    
    float padding = 5.f * SCREEN_SCALE();
    float width = -padding;
    if (children && children->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(children, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                width += pChild->getContentSize().width * pChild->getScaleX() + padding;
            }
        }
    }
    
    float x = -width / 2.0f;
    if (children && children->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(children, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                pChild->runAction(CCMoveTo::create(0.3f, ccp(x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f, 0)));
                x += pChild->getContentSize().width * pChild->getScaleX() + padding;
            }
        }
    }
}

void HudLayer::link()
{
    const CCSize& size = CCDirector::sharedDirector()->getWinSize();
    const CCPoint pausePos = ccp(size.width * 0.5f, size.height * 0.15f);
    
    CCMenu* menu = CCMenu::create();
    menu->setPosition(pausePos);
    addChild(menu);
    
    {
        CCSprite* lightSprite = CCSprite::create("exit.png");
        lightSprite->setOpacity(100.f);
        
        CCSprite* darkSprite = CCSprite::create("exit.png");
        darkSprite->setOpacity(180.f);
        
        CCMenuItemSprite* button = CCMenuItemSprite::create(lightSprite, darkSprite, getParent(), menu_selector(GameScene::loseGame));
        menu->addChild(button);
    }
    
    menu->alignItemsHorizontally();
    
    while(RIG_CUT() != m_alignNode->getChildrenCount())
    {
        CCSprite* sprite = CCSprite::create("cut.png");
        m_alignNode->addChild(sprite);
    }
    
    alignCuts();
}