//
//  PolygonNode.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 1..
//
//

#include "Global.h"
#include "PolygonNode.h"

PolygonNode::PolygonNode()
{
    m_rig.clear();
    m_fill = true;
}

PolygonNode* PolygonNode::createWithRig(const Rig &rig, const ccColor4B& fillColor, const ccColor4B& outlineColor, bool fill)
{
    PolygonNode* pRet = new PolygonNode();
    if (pRet && pRet->initWithRig(rig, fillColor, outlineColor, fill))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool PolygonNode::initWithRig(const Rig &rig, const ccColor4B& fillColor, const ccColor4B& outlineColor, bool fill)
{
    m_rig = rig;
    
    m_fillColor = fillColor;
    m_outlineColor = outlineColor;
    
    m_fill = fill;
    
    RigTriangulate(m_rig,m_triangleRigs);

    return true;
}

void PolygonNode::draw()
{
    CCNodeRGBA::draw();
    
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //ccGLBlendFunc(GL_ONE, GL_ONE);
    
    ccDrawInit();
    
    CCPoint rigCenter = RigCenter(m_rig);
    
    Rig rotatedRig;
    rotatedRig.reserve(m_rig.size());
    for(int i = 0; i < m_rig.size(); i++)
    {
        CCPoint rotatedPoint = ccpRotateByAngle(m_rig[i], rigCenter, getRotation());
        rotatedRig.push_back(rotatedPoint);
    }
    
    std::vector<Rig> rotatedTriangles;
    rotatedTriangles.reserve(m_triangleRigs.size());
    for(int i = 0; i < m_triangleRigs.size(); i++)
    {
        Rig singleTriangle = m_triangleRigs[i];
        for(int v = 0; v < 3; v++)
        {
            singleTriangle[v] = ccpRotateByAngle(singleTriangle[v], rigCenter, getRotation());
        }
        
        rotatedTriangles.push_back(singleTriangle);
    }
    
    glLineWidth(3.f * SCREEN_SCALE());
    ccPointSize(3.f * SCREEN_SCALE() * 0.5f);
    
    ccDrawColor4B(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, getOpacity());
    
    ccDrawPoly(&rotatedRig[0], m_rig.size(), true);
    ccDrawPoints(&rotatedRig[0], m_rig.size());
    
    if(m_fill)
    {
        m_fillColor.a = getOpacity();
     
        for(int i = 0; i < rotatedTriangles.size(); i++)
        {
            ccDrawSolidPoly(&rotatedTriangles[i][0], rotatedTriangles[i].size(), ccc4FFromccc4B(m_fillColor));
        }
    }
    
    //Glow
    //ccDrawColor4B(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, getOpacity());
    
    ccDrawFree();
    
    ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    
    CC_INCREMENT_GL_DRAWS(1);
}