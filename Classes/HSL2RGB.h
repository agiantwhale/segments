#ifndef HSL2RGB_H
#define HSL2RGB_H

#include <cocos2d.h>

void RGBtoHSL(unsigned int color,unsigned int& h, unsigned int& s, unsigned int& l);
unsigned int HSLtoRGB(const unsigned int& h, const unsigned int& s, const unsigned int& l);
unsigned int BrightenColor(unsigned int color,unsigned int amount);
unsigned int DarkenColor(unsigned int color,unsigned int amount);

cocos2d::ccColor4B HSLtoColor(const unsigned int& h, const unsigned int& s, const unsigned int& l);

#endif
