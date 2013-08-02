//
//  RippleNode.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 20..
//
//

#include "RippleNode.h"
#include "Rig.h"
#include "Global.h"

RippleNode* RippleNode::create()
{
    RippleNode* pRet = new RippleNode();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool RippleNode::init()
{
    return true;
}

void RippleNode::draw()
{
    CCNodeRGBA::draw();
    
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ccDrawInit();
    
    ccDrawColor4B(getColor().r, getColor().g, getColor().b, getOpacity());
    
    glLineWidth(3.f * SCREEN_SCALE());
    ccPointSize(3.f * SCREEN_SCALE() * 0.5f);
    
    Rig rig;
    rig.reserve(RIG_VERTEXES());
    for(int i = 0; i < RIG_VERTEXES(); i++)
    {
        CCPoint vertex = ccpRotateByAngle(CCPointMake(0, 200.f * SCREEN_SCALE()), CCPointZero, M_PI * 2 * i / RIG_VERTEXES() + getRotation());
        rig.push_back(vertex);
    }
    
    ccDrawPoly(&rig[0], rig.size(), true);
    
    ccDrawPoint(CCPointZero);
    
    ccDrawFree();
    
    ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    
    CC_INCREMENT_GL_DRAWS(1);
}