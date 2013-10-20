//
//  Rig.cpp
//  CutGame
//
//  Created by 이일재 on 13. 7. 1..
//
//

#include "Rig.h"
#include "Global.h"
#include "triangulate.h"
#include <algorithm>

#define calculate_determinant_2x2(x1,y1,x2,y2) x1*y2-y1*x2
#define calculate_determinant_2x3(x1,y1,x2,y2,x3,y3) x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1

float g_rigMinRadius = 0.f;
float g_rigMaxRadius = 0.f;

int g_rigVertexes = 3;
int g_rigCut = 1;

struct PositionSort
{
public:
    PositionSort(const CCPoint& start)
    {
        m_startPosition = start;
    }
    
    bool operator() (CCPoint i,CCPoint j) {return ccpDistanceSQ(i, m_startPosition) < ccpDistanceSQ(j, m_startPosition); }
private:
    CCPoint m_startPosition;
};

struct HorizontalSort
{
    bool operator() (CCPoint i,CCPoint j) {return i.x < j.x; }
};

struct ClockwiseSort
{
public:
    ClockwiseSort(const CCPoint& pos)
    {
        m_startPosition = pos;
    }
    
    bool operator() (CCPoint i,CCPoint j) {return ccpAngleSigned(ccpSub(i, m_startPosition), ccp(0,1)) < ccpAngleSigned(ccpSub(j, m_startPosition), ccp(0,1)); }
private:
    CCPoint m_startPosition;
};

bool PointToleranceEquals(CCPoint i, CCPoint j) {
    return (ccpDistance(i, j) < RIG_TOLERANCE());
}

void RigBoundingBox(const Rig& rig, CCPoint& min, CCPoint& max)
{
    for(int i = 0; i < rig.size(); i++)
    {
        CCPoint point = rig[i];
        
        min.x = MIN(point.x, min.x);
        min.y = MIN(point.y, min.y);
        
        max.x = MAX(point.x, max.x);
        max.y = MAX(point.y, max.y);
    }
}

void RigSideRandom(const Rig& rig, CCPoint& vertex, CCPoint& nVertex)
{
    const int vertexNum = rand() % rig.size();
    const int nextVertexNum = (vertexNum+1) % rig.size();
    
    vertex = rig[vertexNum];
    nVertex = rig[nextVertexNum];
}

CCPoint RigCenter(const Rig& rig)
{
    CCPoint rigCenter = CCPointZero;
    for(int i = 0; i < rig.size(); i++)
    {
        rigCenter = ccpAdd(rigCenter, rig[i]);
    }
    rigCenter = ccpMult(rigCenter, 1.f/rig.size());
    
    return rigCenter;
}

bool RigSegmentCollides(const Rig& targetRig, const CCPoint& newVertex, const CCPoint& oldVertex)
{
    if(targetRig.size() < 3)
    {
        return false;
    }
    
    for(int v = 0; v < targetRig.size(); v++)
    {
        CCPoint edgeStart = targetRig[v];
        CCPoint edgeEnd = targetRig[ (v+1) % targetRig.size() ];
        
        if(edgeStart.equals(oldVertex) || edgeEnd.equals(oldVertex))
        {
            continue;
        }
        
        if(ccpSegmentIntersect(edgeStart, edgeEnd, newVertex, oldVertex))
        {
            return true;
        }
    }
    
    return false;
}

void RigRandom(Rig& targetRig, int vertexes)
{
    //Other implementations can be found at:
    //http://pastebin.com/wdKmSrL3
    
    //Let's create the goal polygon first.
    //Due to preventing intersections, one more vertex maybe created that stated over here.
    unsigned int vertexNum = vertexes;
    
    //Now that we have the number of vertexes, let's create the number of angles needed.
    std::vector<float> angles;
    angles.reserve(vertexNum);
    for(int angleIter = 0; angleIter < vertexNum; angleIter++)
    {
        //angles.push_back(angleIter * (angleSize + CCRANDOM_0_1()));
        angles.push_back(GetRandomAngle());
    }
    
    std::sort(angles.begin(), angles.end());
    
    //Iterate over the angles, create a vertexes stack.
    targetRig.reserve(vertexNum);
    for(std::vector<float>::iterator iter = angles.begin(); iter != angles.end(); iter++)
    {
        float angle = (*iter);
        CCPoint highPoint = ccp(0, RIG_MIN_RADIUS() + (RIG_MAX_RADIUS()-RIG_MIN_RADIUS()) * CCRANDOM_0_1());
        targetRig.push_back(ccpRotateByAngle(highPoint, CCPointZero, angle));
    }
    
    //Make sure the first and last point doesn't intersect.
    for(int i = 0; i < targetRig.size()-1; i++) {
        CCPoint startPoint = targetRig[i];
        CCPoint endPoint = targetRig[i+1];
        if(ccpSegmentIntersect(startPoint, endPoint, targetRig.front(), targetRig.back())) {
            targetRig.push_back(CCPointZero);
            break;
        }
    }
}

bool RigSplit(const CCPoint& startPoint, const CCPoint& endPoint, const Rig& originalRig, std::vector<Rig>& finalRigs)
{
    std::vector<std::pair<Rig, CCPoint> > splitPolygons;
    std::pair<Rig, CCPoint>* currentRig = NULL;

    Rig intersections;
    Rig ignoreIntersections;
    CCPoint lastVert = originalRig[originalRig.size()-1];
    for(int i = 0; i < originalRig.size(); i++)
    {
        CCPoint intersectPoint = ccpIntersectPoint(startPoint, endPoint, lastVert, originalRig[i]);
        
        if( ccpSegmentIntersect(startPoint, endPoint, lastVert, originalRig[i]) )
        {
            intersections.push_back(intersectPoint);
        }
        
        lastVert = originalRig[i];
    }
    
    std::sort(intersections.begin(), intersections.end(), PositionSort(startPoint));
    
    //Check if the split line is valid.
    if(intersections.size() < 2)
    {
        return false;
    }
    
    if(RigCheckPoint(originalRig, startPoint))
    {
        ignoreIntersections.push_back(intersections[0]);
        intersections.erase(intersections.begin());
    }
    
    if(intersections.size() % 2 != 0)
    {
        ignoreIntersections.push_back(intersections[intersections.size()-1]);
        intersections.pop_back();
    }
    
    std::vector<std::pair<CCPoint, CCPoint> > intersectionPairs;
    intersectionPairs.reserve(intersections.size() / 2);
    for(int i = 0; i < intersections.size(); i += 2)
    {
        intersectionPairs.push_back(std::make_pair(intersections[i], intersections[i+1]));
    }
    
    splitPolygons.push_back(std::make_pair(Rig(), CCPoint()));
    currentRig = &splitPolygons[0];
    
    for(int y = 0; y < originalRig.size(); y++)
    {
        CCPoint edgeStart = originalRig[y];
        CCPoint edgeEnd = originalRig[ (y+1) % originalRig.size()];
        
        if(!RigContain(currentRig->first, edgeStart))
        {
            currentRig->first.push_back(edgeStart);
        }
        
        //Check for intersections with the split line:
        bool intersects = ccpSegmentIntersect(startPoint, endPoint, edgeStart, edgeEnd);
        
        if(intersects)
        {
            CCPoint intersectionPoint = ccpIntersectPoint(startPoint, endPoint, edgeStart, edgeEnd);
         
            //These points should be ignored.
            if(RigContain(ignoreIntersections, intersectionPoint))
            {
                continue;
            }
            
            //Add the intersection point to the current polygon.
            if(!RigContain(currentRig->first, intersectionPoint))
            {
                currentRig->first.push_back(intersectionPoint);
            }
            
            CCPoint pairs;
            //Find the intersction point in the intersection pairs.
            for(int f = 0; f < intersectionPairs.size(); f ++)
            {
                if(intersectionPairs[f].first.equals(intersectionPoint))
                {
                    pairs = intersectionPairs[f].second;
                    break;
                }
                
                if(intersectionPairs[f].second.equals(intersectionPoint))
                {
                    pairs = intersectionPairs[f].first;
                    break;
                }
            }
            
            assert(!pairs.equals(CCPointZero));
            
            if(!RigContain(currentRig->first, pairs))
            {
                currentRig->first.push_back(pairs);
            }
            
            //Set its partner as the crossback point for the current polygon.
            currentRig->second = pairs;
            
            
            bool found = false;
            for(int x = 0; x < splitPolygons.size(); x ++)
            {
                //If there is an existing polygon with a crossback for this edge
                if(&splitPolygons[x] != currentRig && (splitPolygons[x].second.equals(pairs) || splitPolygons[x].second.equals(intersectionPoint)) )
                {
                    //Set the current polygon to be that polygon
                    currentRig = &splitPolygons[x];
                    found = true;
                    break;
                }
            }
            
            //Else
            if(!found)
            {
                //Append a new polygon and new crossback point to the output lists and make it current
                splitPolygons.push_back(std::make_pair(Rig(), CCPoint()));
                currentRig = &splitPolygons[splitPolygons.size()-1];
            }
            
            if(!RigContain(currentRig->first, edgeEnd))
            {
                currentRig->first.push_back(edgeEnd);
            }
        }
    }
    
    for(int i = 0; i < splitPolygons.size(); i++)
    {
        Rig rig = splitPolygons[i].first;
        
        finalRigs.push_back(rig);
    }
    
    return true;
}

float RigArea(const Rig& rig)
{
    int i,j;
    float area = 0;
    
    for (i=0;i<rig.size();i++)
    {
        j = (i + 1) % rig.size();
        area += rig[i].x * rig[j].y;
        area -= rig[i].y * rig[j].x;
    }
    
    area /= 2.f;
    return(area < 0 ? -area : area);
}

bool RigSimilar(const Rig& compare, const Rig& index, float& similarity)
{
    // Calculate the difference between the two rigs being compared in size.
    int difference = abs(compare.size() - index.size());
    
    // Threshold of comparison = the bigger one.
    int del = MAX(compare.size(), index.size());

    float percentage = (float)difference / (float)del;
    
    // The below is basically found through trial and error, when there are over 25% difference in the number of vertexes it seems displeasing to the eye.
    if( percentage > 0.25 ) return false;

    // Ignore the BADLY NAMED variables below - the smaller/bigger rig has nothing to do with the results.
    Rig smallerRig = compare;
    Rig biggerRig = index;
    
    /*
    // This code has been commented out as I've updated the function so that it doesn't need to know which rig is smaller/bigger.
     
    for(Rig::iterator curPos = biggerRig.begin();
        curPos != biggerRig.end();)
    {
        Rig::iterator nextPos = curPos + 1;
        if(nextPos == biggerRig.end()) nextPos = biggerRig.begin();
        
        CCPoint curPoint = (*curPos);
        CCPoint nextPoint = (*nextPos);
        
        if(ccpDistance(curPoint, nextPoint) < tolerance)
        {
            curPos = biggerRig.erase(nextPos);
        }
        else
        {
            curPos++;
        }
    }
     */
    
    // Calculate the center of mass for the smaller rig.
    // RigCenter basically returns the coordinate of all points added divided by the number of vertexes.
    // Normalize the points to the center.
    const CCPoint smallerMid = RigCenter(smallerRig);
    for(int i = 0; i < smallerRig.size(); i++)
    {
        smallerRig[i] = ccpSub(smallerRig[i], smallerMid);
    }
    
    const CCPoint biggerMid = RigCenter(biggerRig);
    for(int i = 0; i < biggerRig.size(); i++)
    {
        biggerRig[i] = ccpSub(biggerRig[i], biggerMid);
    }
    
    // Rig area does some matrix magic to calculate the area of the rig.
    float smallerArea = RigArea(smallerRig);
    float biggerArea = RigArea(biggerRig);
    
    // Scale the rig so that there wouldn't be big differences in overlaps when comparing similar points.
    float scale = sqrtf(biggerArea/smallerArea);
    for(int i = 0; i < smallerRig.size(); i++)
    {
        smallerRig[i] = ccpMult(smallerRig[i], scale);
    }
    
    // FIXFIX:: The problem right now is that the Rig's centers are focus around the origin (0,0). That is retarded - fix this so that they will be focused around the centroid.
    int nearPoints = 0;
    for(int i = 0; i < smallerRig.size(); i++)
    {
        CCPoint curPoint = smallerRig[i];
        
        for(int v = 0; v < biggerRig.size(); v++)
        {
            if(PointToleranceEquals(biggerRig[v], curPoint))
            {
                nearPoints++;
                break;
            }
        }
    }
    
    // Double iteration to find the closest points
    Rig combination = biggerRig;
    for(int i = 0; i < smallerRig.size(); i++)
    {
        CCPoint curPoint = smallerRig[i];
        bool skip = false;
        
        for(int v = 0; v < combination.size(); v++)
        {
            // The function below is a very simple function that gives a bit of tolerence for equality when comparing nearby points. This accounts for humans not having perfect eyesight.
            if(PointToleranceEquals(combination[v], curPoint))
            {
                skip = true;
            }
        }
        
        if(!skip) combination.push_back(curPoint);
    }
    
    //Notice how I'm using smaller size instead of bigger rig's.
    //This is because rig2 is the goal polygon - (lol refactor this so it has better naming.)
    //return nearPoints == compare.size();
    
    similarity = (float)nearPoints / combination.size();
    
    // If the similarity is over 1, it means that the goal polygon is smaller than the comparing polygon.
    return similarity >= 0.75f && similarity <= 1.f;
}

bool RigHummingDistance(const Rig& rig1, const Rig& rig2)
{
    if(rig1.size() != rig2.size()) return false;
    
    float distance = 0.f;
    
    for(int i = 0; i < rig1.size(); i++)
    {
        distance += ccpDistance(rig1[i], rig2[i]);
    }
    
    return distance < RIG_MIN_RADIUS() * 2.f;
}

bool RigTriangulate(const Rig& rig, std::vector<Rig>& finalTriangles)
{
    Vector2dVector a;
    for(int i = 0; i < rig.size(); i++)
    {
        a.push_back(Vector2d(rig[i].x,rig[i].y));
    }
    Vector2dVector result;
    bool success = Triangulate::Process(a,result);
    
    // print out the results.
    int tcount = result.size()/3;
    for (int i=0; i<tcount; i++)
    {
        const Vector2d &p1 = result[i*3+0];
        const Vector2d &p2 = result[i*3+1];
        const Vector2d &p3 = result[i*3+2];
        
        Rig triangle;
        triangle.push_back(ccp(p1.GetX(),p1.GetY()));
        triangle.push_back(ccp(p2.GetX(),p2.GetY()));
        triangle.push_back(ccp(p3.GetX(),p3.GetY()));
        
        finalTriangles.push_back(triangle);
    }
    
    return success;
}

//Checks if a point is inside a polygon.
//http://alienryderflex.com/polygon/
bool RigCheckPoint(const Rig& rig, const CCPoint& point)
{
    int   i, j=rig.size()-1;
    bool  oddNodes=false;
    
    for (i=0; i<rig.size(); i++)
    {
        if ( ( (rig[i].y< point.y && rig[j].y>=point.y)
             ||   (rig[j].y< point.y && rig[i].y>=point.y) )
            &&  (rig[i].x<=point.x || rig[j].x<=point.x))
        {
            if (rig[i].x+(point.y-rig[i].y)/(rig[j].y-rig[i].y)*(rig[j].x-rig[i].x)<point.x)
            {
                oddNodes=!oddNodes;
            }
        }
        j=i;
    }
    
    return oddNodes;
}

bool RigContain(const Rig& rig, const CCPoint& point)
{
    for(int i = 0; i < rig.size(); i++)
    {
        if( rig[i].equals(point) )
        {
            return true;
        }
    }
    
    return false;
}