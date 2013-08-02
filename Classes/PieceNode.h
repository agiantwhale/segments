//
//  PieceNode.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 5..
//
//

#ifndef __CutGame__PieceNode__
#define __CutGame__PieceNode__

#include <cocos2d.h>
#include "GameLayer.h"

using namespace cocos2d;

class PieceNode : public CCNode
{
    CC_SYNTHESIZE_PASS_BY_REF(std::vector<SliceInfo>, m_sliceInfoStack, SliceInfoStack);
    
public:
    static PieceNode* create(const ccColor4B& color);
    
    virtual bool initWithColor(const ccColor4B& color);
    virtual void draw();
    
private:
    ccColor4B m_pieceColor;
};

#endif /* defined(__CutGame__PieceNode__) */
