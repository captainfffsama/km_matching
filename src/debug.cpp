#include "debug.hpp"
namespace debug{
void showLineInfo(const std::map<int,std::set<int>>& linesInfo)
{
    std::cout<<"{---"<<std::endl;;
    for(auto map_it=linesInfo.begin();map_it!=linesInfo.end();map_it++)
    {
        std::cout<<(*map_it).first<<" : ";
        std::cout<<"[";
        for(auto v_it=(*map_it).second.begin();v_it!=(*map_it).second.end();v_it++)
        {
            std::cout<<*v_it<<" ";
        }
        std::cout<<"]"<<std::endl;;
    }
    std::cout<<"---}"<<std::endl;
}

void showSet(const std::set<int>& a)
{
    std::cout<<"{";
    for(auto it=a.begin();it!=a.end();it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<"}"<<std::endl;
}

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
}
