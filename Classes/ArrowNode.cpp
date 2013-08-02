//
//  ArrowNode.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 5..
//
//

#include "Global.h"
#include "ArrowNode.h"

ArrowNode* ArrowNode::create(const ccColor4B& color)
{
    ArrowNode* pRet = new ArrowNode();
    if (pRet && pRet->initWithColor(color))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool ArrowNode::initWithColor(const ccColor4B &color)
{
    m_arrowColor = color;
    
    return true;
}

void ArrowNode::draw()
{
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ccDrawInit();
    
    glLineWidth(3.f * SCREEN_SCALE());
    ccPointSize(3.f * SCREEN_SCALE() * 0.5f);
    
    ccDrawColor4B(255, 255, 255, 255);
    
    for(int i = 0; i < m_sliceInfoStack.size(); i++)
    {
        //Hard-reference it... Make sure not to modify anything!
        const SliceInfo& info = m_sliceInfoStack[i];
        
        CCPoint startPoint = CCPointApplyAffineTransform( info.beginPoint, worldToNodeTransform());
        CCPoint endPoint = CCPointApplyAffineTransform( info.endPoint, worldToNodeTransform());
        
        CCPoint dirPoint = ccpNormalize(ccpSub(endPoint, startPoint));
        CCPoint perpPoint = ccpNormalize(ccpPerp(dirPoint));
        
        CCPoint points[4];
        points[0] = startPoint;
        points[1] = ccpAdd(endPoint, ccpMult(perpPoint, 5.f));
        points[2] = ccpAdd(endPoint, ccpMult(dirPoint, 5.f));
        points[3] = ccpAdd(endPoint, ccpMult(perpPoint, -5.f));
        
        ccDrawPoly(points, 4, true);
        ccDrawPoints(points, 4);
        
        ccDrawSolidPoly(points, 4, ccc4FFromccc4B(m_arrowColor));
    }
    
    ccDrawFree();
    
    ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
}