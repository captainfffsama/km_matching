#include "debug.hpp"
#include <iomanip>

namespace debug{

void showMatchingResult(const std::vector<int>& a)
{
    for(auto i=0;i<a.size();++i)
    {
        std::cout<<"("<<i<<" "<<a[i]<<"), ";
    }
    std::cout<<std::endl;
}

void showPointInfo(const hungarian::PointInfo& ptinfo)
{
    std::cout<<"("<<ptinfo.isVisit<<","<<ptinfo.weight<<","<<ptinfo.matchPointIdx<<","<<ptinfo.idx<<")"<<std::endl;
}

void showMatrix(const hungarian::Int2DMatrix &matrix)
{
    for(auto row=matrix.begin();row!=matrix.end();row++)
    {
        std::cout<<"{";
        for(auto col=(*row).begin();col!=(*row).end();col++)
        {
            std::cout<<std::setw(9)<<(*col);
            std::cout<<",";
        }
        std::cout<<"}"<<std::endl;
    }
}

void showPairVec(const std::vector<std::pair<int, int>> &a)
{
    for(auto& it:a)
    {
        std::cout<<"("<<it.first<<","<<it.second<<")"<<"  ";
    }
    std::cout<<std::endl;
}
}
