//
//  Global.cpp
//  segment
//
//  Created by 이일재 on 13. 7. 12..
//
//

#include "Global.h"
#include <cocos2d.h>
#include <document.h>

using namespace cocos2d;

float g_screenScale = 0.f;
ScoreInfo g_scoreInfo;
std::vector<ColorInfo> g_colorSchemes;

ccColor4B ArrayToColor(const rapidjson::Value& value) {
    return ccc4(    value[rapidjson::SizeType(0)].GetInt(),
                    value[rapidjson::SizeType(1)].GetInt(),
                    value[rapidjson::SizeType(2)].GetInt(),
                    value[rapidjson::SizeType(3)].GetInt()     );
}

void LoadColorSchemes()
{
    g_colorSchemes.clear();
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("colors.json");
    unsigned long bufferSize = 0;
    const char* fileData = (const char*)(CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize));
    
    if(fileData != NULL)
    {
        std::string clearData(fileData);
        size_t pos = clearData.rfind("}");
        clearData = clearData.substr(0, pos+1);
        
        rapidjson::Document document;
        document.Parse<0>(clearData.c_str());
        
        if(document.HasParseError()) {
            CCLOGERROR("Parser error: %s", document.GetParseError());
            return;
        }
        
        const rapidjson::Value& colors = document["colors"];
        
        for(rapidjson::SizeType i = 0; i < colors.Size(); i++ ) {
            ColorInfo info;
            
            info.setFillColor(ArrayToColor(colors[i]["fill"]));
            info.setOutlineColor(ArrayToColor(colors[i]["outline"]));
            info.setArrowColor(ArrayToColor(colors[i]["arrow"]));
            info.setPieceColor(ArrayToColor(colors[i]["piece"]));
            info.setBackgroundColor(ArrayToColor(colors[i]["background"]));
            
            g_colorSchemes.push_back(info);
        }
    }
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