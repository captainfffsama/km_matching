#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
#include "opencv2/opencv.hpp"

namespace debug{
inline void showLineInfo(const std::map<int,std::set<int>>& linesInfo)
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

inline void showSet(const std::set<int>& a)
{
    std::cout<<"{";
    for(auto it=a.begin();it!=a.end();it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<"}"<<std::endl;
}

}
#endif
