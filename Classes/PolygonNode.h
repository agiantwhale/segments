//
//  PolygonNode.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 1..
//
//

#ifndef __CutGame__PolygonNode__
#define __CutGame__PolygonNode__

#include <cocos2d.h>
#include "Rig.h"

using namespace cocos2d;

class PieceNode;

class PolygonNode : public CCNodeRGBA
{
    CC_SYNTHESIZE(ccColor4B, m_fillColor, FillColor);
    CC_SYNTHESIZE(ccColor4B, m_outlineColor, OutlineColor);
    CC_SYNTHESIZE_PASS_BY_REF(Rig, m_rig, Rig);
    CC_SYNTHESIZE_READONLY(bool, m_fill, Fill);
    
public:
    PolygonNode();
    
    static PolygonNode* createWithRig(const Rig& rig, const ccColor4B& fillColor, const ccColor4B& outlineColor, bool fill = true);
    virtual bool initWithRig(const Rig& rig, const ccColor4B& fillColor, const ccColor4B& outlineColor, bool fill);
    
    virtual void draw();
    
private:
    std::vector<Rig> m_triangleRigs;
};

#endif /* defined(__CutGame__PolygonNode__) */
