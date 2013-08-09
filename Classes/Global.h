//
//  Global.h
//  segment
//
//  Created by 이일재 on 13. 7. 12..
//
//

#ifndef __segment__Global__
#define __segment__Global__

#include <cocos2d.h>
#include <algorithm>

using namespace cocos2d;

class ColorInfo
{
    CC_SYNTHESIZE(ccColor4B, m_fillColor, FillColor);
    CC_SYNTHESIZE(ccColor4B, m_outlineColor, OutlineColor);
    CC_SYNTHESIZE(ccColor4B, m_arrowColor, ArrowColor);
    CC_SYNTHESIZE(ccColor4B, m_pieceColor, PieceColor);
    CC_SYNTHESIZE(ccColor4B, m_backgroundColor, BackgroundColor);
    
public:
    ColorInfo(const ccColor4B& fill, const ccColor4B& outline, const ccColor4B& arrow, const ccColor4B& piece, const ccColor4B& background)
    {
        m_fillColor = fill;
        m_outlineColor = outline;
        m_arrowColor = arrow;
        m_pieceColor = piece;
        m_backgroundColor = background;
    }
    
    ColorInfo()
    {}
};

struct ScoreInfo
{
    ScoreInfo()
    {
        level = 0;
        cuts = 0;
        accuracy = 0.f;
    }
    
    int level;
    int cuts;
    float accuracy;
};

std::string NamePolygon( unsigned int numberOfSides );

void LoadColorSchemes();
ColorInfo RandomColorScheme();

void LoadScoreInfo();
void SaveScoreInfo(const ScoreInfo& info);

extern ScoreInfo g_scoreInfo;
extern float g_screenScale;

#define SCORE_INFO() g_scoreInfo
#define SCREEN_SCALE() g_screenScale

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    #define DEFAULT_FONT "AdventPro-Regular"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    #define DEFAULT_FONT "AdventPro-Regular.ttf"
#endif

#define DEFAULT_LABEL_SIZE 20.f

#endif /* defined(__segment__Global__) */
