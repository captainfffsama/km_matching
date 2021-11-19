#ifndef _OBJECT_MATCH_H
#define _OBJECT_MATCH_H

#include "hungarian.hpp"

namespace object_match {

const int LABEL_COST=10000;
const int APPEND_COST=-50000;
struct ObjInfo
{
    std::string label;

    //xmin,ymin,xmax,ymax
    std::vector<int> pos;
};
class ObjectMatcher
{
public:
    explicit ObjectMatcher() {matcher=hungarian::Hungarian();}

    int MatchObject(const std::vector<ObjInfo>& objsA,const std::vector<ObjInfo>& objsB,std::vector<std::pair<int,int>>& A2BMatchResult,std::vector<int>& noMatchObjs);
private:
    hungarian::Hungarian matcher;

    void GenerateCostMatrix(const std::vector<ObjInfo>& objsa,const std::vector<ObjInfo>& objsb,const std::pair<int,int>& appendInfo,hungarian::Int2DMatrix& costMatrix);

    float CountObjCost(const ObjInfo& obj1,const ObjInfo& obj2);

};

}

#endif
