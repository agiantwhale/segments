//
//  Global.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 12..
//
//

#include "Global.h"
#include <cocos2d.h>

using namespace cocos2d;

float g_screenScale = 0.f;
ScoreInfo g_scoreInfo;
std::vector<ColorInfo> g_colorSchemes;

void LoadColorSchemes()
{
    g_colorSchemes.clear();
}

ColorInfo RandomColorScheme()
{
    return g_colorSchemes[rand() % g_colorSchemes.size()];
}

void LoadScoreInfo()
{
    FILE* filePtr = NULL;
    std::string filePos = CCFileUtils::sharedFileUtils()->getWritablePath() + "score";
    
    if((filePtr = fopen(filePos.c_str(), "rb")) == NULL)
    {
        g_scoreInfo.level = 3;
        g_scoreInfo.accuracy = 0.f;
    }
    else
    {
        fread(&g_scoreInfo, sizeof(ScoreInfo), 1, filePtr);
        fclose(filePtr);
    }
}

void SaveScoreInfo(const ScoreInfo& info)
{
    FILE* filePtr = NULL;
    std::string filePos = CCFileUtils::sharedFileUtils()->getWritablePath() + "score";
    
    if((filePtr = fopen(filePos.c_str(), "wb")) == NULL)
    {
        CCLOG("Unable to open scores file!");
    }
    fwrite(&g_scoreInfo, sizeof(ScoreInfo), 1, filePtr);
    fclose(filePtr);
}