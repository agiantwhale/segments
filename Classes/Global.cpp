//
//  Global.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 12..
//
//

#include "Global.h"
#include "HSL2RGB.h"
#include <cocos2d.h>

using namespace cocos2d;

float g_screenScale = 0.f;
ScoreInfo g_scoreInfo;

std::string NamePolygon( unsigned int numberOfSides ) {
    std::string name;
    
    return name + "gon";
}

/*
 
 Color Chart
 
 fill		-	L: 0.5	-	S: 0.5
 outline	-	L: 0.35	-	S: 0.9
 arrow		-	L: 0.8	-	S: 0.5
 piece		-	L: 0.55	-	S: 0.3
 background	-	L: 0.4	-	S: 0.4
 
 */

ColorInfo RandomColorScheme()
{
    ColorInfo randomScheme;
    
    int hValue = (int)360 * CCRANDOM_0_1();
    
    randomScheme.setFillColor(HSLtoColor(hValue, 50, 50));
    randomScheme.setOutlineColor(HSLtoColor(hValue, 90, 35));
    randomScheme.setArrowColor(HSLtoColor(hValue, 50, 80));
    randomScheme.setPieceColor(HSLtoColor(hValue, 30, 55));
    randomScheme.setBackgroundColor(HSLtoColor(hValue, 40, 40));
    
    return randomScheme;
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