#include <algorithm>
#include <iostream>
#include "hungarian.hpp"
#include "object_match.hpp"
#include "debug.hpp"

using object_match::ObjInfo;

int main()
{
    std::vector<ObjInfo> objas {{"d",{10,10,20,20}},
                                {"d",{40,40,60,60}},
                                {"c",{40,40,60,60}},
                                {"d",{80,80,90,90}}};
    std::vector<ObjInfo> objbs {
                                {"d",{80,80,90,90}},
                               {"c",{10,10,20,20}}, };
    
    object_match::ObjectMatcher solver;
    std::vector<int> nomath;
    std::vector<std::pair<int,int>> result;
    std::cout<<"star"<<std::endl;
    int flag=solver.MatchObject(objas,objbs,result,nomath);

    std::cout<<"flag:"<<flag<<std::endl;
    std::cout<<"match result"<<std::endl;

    debug::showPairVec(result);
    
    std::cout<<"========\n"<<"no match idx"<<std::endl;

    for(auto it=nomath.begin();it!=nomath.end();it++)
    {
        std::cout<<(*it)<<", ";
    }
    std::cout<<"\n=========="<<std::endl;
    
    return 0;
}
