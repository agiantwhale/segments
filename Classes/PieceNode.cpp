//
//  PieceNode.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 5..
//
//

#include "Global.h"
#include "PieceNode.h"
#include "PolygonNode.h"
#include "GameLayer.h"

PieceNode* PieceNode::create(const ccColor4B& color)
{
    PieceNode* pRet = new PieceNode();
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

bool PieceNode::initWithColor(const ccColor4B &color)
{
    m_pieceColor = color;
    
    return true;
}

void PieceNode::draw()
{
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ccDrawInit();
    
    glLineWidth(3.f * SCREEN_SCALE());
    ccPointSize(3.f * SCREEN_SCALE() * 0.5f);
    
    for(int i = 0; i < m_sliceInfoStack.size(); i++)
    {
        //Hard-reference it... Make sure not to modify anything!
        const SliceInfo& info = m_sliceInfoStack[i];
        
        CCPoint startPoint = CCPointApplyAffineTransform( info.beginPoint, worldToNodeTransform());
        CCPoint endPoint = CCPointApplyAffineTransform( info.endPoint, worldToNodeTransform());
        
        PolygonNode* slicePolygon = static_cast<PolygonNode*>(getParent());
        
        std::vector<Rig> rigStack;
        if(RigSplit(startPoint, endPoint, slicePolygon->getRig(), rigStack))
        {
            int closestRigNum = 0;
            for(int v = 0; v < rigStack.size(); v++)
            {
                if(RigArea(rigStack[v]) > RigArea(rigStack[closestRigNum]))
                {
                    closestRigNum = v;
                }
            }
            
            for(int v = 0; v < rigStack.size(); v++)
            {
                if(closestRigNum == v) continue;
                
                Rig& curRig = rigStack[v];
                
                ccColor4B outlineColor = slicePolygon->getOutlineColor();
                ccDrawColor4B(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
                
                ccDrawPoly(&curRig[0], curRig.size(), true);
                ccDrawPoints(&curRig[0], curRig.size());
                
                std::vector<Rig> triangulatedRigs;
                RigTriangulate(curRig, triangulatedRigs);
                
                for(int i = 0; i < triangulatedRigs.size(); i++)
                {
                    ccDrawSolidPoly(&triangulatedRigs[i][0], triangulatedRigs[i].size(), ccc4FFromccc4B(m_pieceColor));
                }
            }
        }
    }
    
    ccDrawFree();
    
    ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    
    CC_INCREMENT_GL_DRAWS(1);
}