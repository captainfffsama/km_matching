#ifndef _HUNGARIAN_H
#define _HUNGARIAN_H

#include <iostream>
#include <ostream>
#include <vector>


namespace hungarian {

struct PointInfo
{
    bool isVisit;
    float weight;
    int matchPointIdx;
    int idx;

    PointInfo(bool is_v=false,float w=0.0,int mPI=-1,int indix=-1):isVisit(is_v),weight(w),matchPointIdx(mPI),idx(indix) {}
};

using PointsInfoVec=std::vector<PointInfo>;
using Flt2DMatrix=std::vector<std::vector<float>>;

void clearPointsVisitFlag(PointsInfoVec& pts);

class Hungarian
{
public:
    explicit Hungarian() {}
    float Solve(const std::vector<std::vector<float>>& c_m,std::vector<int>& matchResult); 
private:
    int ptPairNum;
    PointsInfoVec xpts;
    PointsInfoVec ypts;
    Flt2DMatrix costMatrix;

    void InitVertexWeight();

    bool DFS(int x_idx);
};


}

#endif
