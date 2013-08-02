//
//  SettingsScene.h
//  segment
//
//  Created by 이일재 on 13. 7. 27..
//
//

#ifndef __segment__SettingsScene__
#define __segment__SettingsScene__

#include <cocos2d.h>

using namespace cocos2d;

class SettingsScene : public CCScene
{
public:
    static SettingsScene* create();
    
    SettingsScene();
    
    virtual bool init();
    virtual void update(float dt);
};

#endif /* defined(__segment__SettingsScene__) */
