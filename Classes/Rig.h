//
//  Rig.h
//  CutGame
//
//  Created by 이일재 on 13. 7. 1..
//
//

#ifndef __CutGame__Rig__
#define __CutGame__Rig__

#include <cocos2d.h>
#include <vector>

using namespace cocos2d;

extern float g_rigMinRadius;
extern float g_rigMaxRadius;

extern int g_rigVertexes;
extern int g_rigCut;

//Rig is a collection of points.
typedef std::vector<CCPoint> Rig;

void RigBoundingBox(const Rig& rig, CCPoint& min, CCPoint& max);
void RigSideRandom(const Rig& rig, CCPoint& vertex, CCPoint& nVertex);
CCPoint RigCenter(const Rig& rig);
void RigRandom(Rig& targetRig, int vertexes = g_rigVertexes);
bool RigSplit(const CCPoint& startPoint, const CCPoint& endPoint, const Rig& originalRig, std::vector<Rig>& finalRigs);
bool RigContain(const Rig& rig, const CCPoint& point);
bool RigHummingDistance(const Rig& rig1, const Rig& rig2);
bool RigSimilar(const Rig& compare, const Rig& index, float& similarity);
float RigArea(const Rig& rig);
bool RigTriangulate(const Rig& rig, std::vector<Rig>& finalTriangles);
bool RigCheckPoint(const Rig& rig, const CCPoint& point);

inline float GetRandomAngle()
{
    return CCRANDOM_0_1() * M_PI * 2.f;
}

#define RIG_MIN_RADIUS() g_rigMinRadius
#define RIG_MAX_RADIUS() g_rigMaxRadius

#define RIG_VERTEXES() g_rigVertexes
#define RIG_CUT()      g_rigCut

#define RIG_TOLERANCE() 20.f * SCREEN_SCALE()

#endif /* defined(__CutGame__Rig__) */
