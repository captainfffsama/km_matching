#include "object_match.hpp"
#include <math.h>
#include "debug.hpp"

namespace object_match {
int ObjectMatcher::MatchObject(const std::vector<ObjInfo> &objsA, const std::vector<ObjInfo> &objsB, std::vector<std::pair<int,int>> &A2BMatchResult, std::vector<int> &noMatchObjs)
{

    //确定增补矩阵的信息
    //first若为0 表示无需增补 cost matrix
    //为1,表示A 多了,B需要补,costmatrix 的列需要补
    //为2 表示B多了,行需要补
    std::pair<int,int> appendInfo = std::make_pair(0,0);

    std::size_t a {objsA.size()-objsB.size()};
    if(a>0)
    {
        appendInfo.first=1;
    }
    else if (a<0) {
        appendInfo.first=2;
        a=-a;
    }
    else
    {appendInfo.first=0;}
    appendInfo.second=a;

    hungarian::Int2DMatrix costMatrix;
    GenerateCostMatrix(objsA,objsB,appendInfo,costMatrix);

    std::vector<int> kmReuslt;
    int cost=matcher.Solve(costMatrix,kmReuslt);
    debug::showMatrix(costMatrix);
    
    switch (appendInfo.first) {
        //A 多了
        case 1:
            {
                for(auto i=0;i<kmReuslt.size();++i)
                {
                    if(kmReuslt[i]>=objsB.size())
                    {
                        noMatchObjs.push_back(i);
                    }
                    else
                    {
                        A2BMatchResult.push_back(std::make_pair(i,kmReuslt[i]));
                    }
                }
                break;
            }
        //B 多了
        case 2:
            {
                for(auto i=0;i<kmReuslt.size();++i)
                {
                    if(i>=objsA.size())
                    {noMatchObjs.push_back(kmReuslt[i]);}
                    else
                    {
                        A2BMatchResult.push_back(std::make_pair(i,kmReuslt[i]));
                    }
                }
                break;
            }
        default:
            break;
    }
    return appendInfo.first;
    
};

void ObjectMatcher::GenerateCostMatrix(const std::vector<ObjInfo>& objsa,const std::vector<ObjInfo>& objsb,const std::pair<int,int>& appendInfo,hungarian::Int2DMatrix& costMatrix)
{
    for(auto ait=objsa.begin();ait!=objsa.end();ait++)
    {
        std::vector<int> a2bs;
        for(auto bit=objsb.begin();bit!=objsb.end();bit++)
        {
            a2bs.push_back(CountObjCost(*ait,*bit));
        }
        if(appendInfo.first==1)
        {
            for(auto i=0;i<appendInfo.second;i++)
            {
                a2bs.push_back(APPEND_COST);
            }
        }
        costMatrix.push_back(a2bs);
    }
    if(appendInfo.first==2)
    {
        std::vector<int> appendRow;
        for(auto i=0;i<objsb.size();i++)
        {appendRow.push_back(APPEND_COST);}
        for(auto i=0;i<appendInfo.second;i++)
        {
            costMatrix.push_back(appendRow);
        }
    }
};

float ObjectMatcher::CountObjCost(const ObjInfo& obj1,const ObjInfo& obj2)
{
    float obj1_x_c=(obj1.pos[2]+obj1.pos[0])/2.0;
    float obj1_y_c=(obj1.pos[1]+obj1.pos[3])/2.0;
    float obj2_x_c=(obj2.pos[2]+obj2.pos[0])/2.0;
    float obj2_y_c=(obj2.pos[1]+obj2.pos[3])/2.0;

    float distance=std::sqrt(std::pow((obj2_x_c-obj1_x_c),2)+std::pow((obj2_y_c-obj1_y_c),2));
    int distance_t=static_cast<int>(std::round(distance));

    if(obj1.label!=obj2.label)
    {
        return -(distance_t+LABEL_COST);
    }
    else
    {return -distance_t;}
}

}


