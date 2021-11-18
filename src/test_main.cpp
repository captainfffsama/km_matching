#include <algorithm>
#include <iostream>
#include <opencv2/core/types.hpp>
#include "hungarian.hpp"


int main()
{
    auto hungarianSolver=hungarian::Hungarian();
    // cv::Mat testMat=(Mat_<float> (4,4) <<0, 1, 2, 3,0, 1, 2, 3,1, 2, 0, 3,1, 2, 3, 4);

    cv::Mat testMat=(Mat_<float> (4,4) <<10, 19, 8, 15, 10, 18, 7, 17, 13, 16, 9, 14,12, 19, 8, 18);

    std::cout<<"test mat is:\n"<<testMat<<std::endl;
    std::map<int,int> match;
    auto cost=hungarianSolver.Solve(testMat,match);

    for(auto it= match.begin();it!=match.end();it++)
    {
        std::cout<<"["<<(*it).first<<","<<(*it).second<<"]  ";
    }
    std::cout<<std::endl;

    std::cout<<"cost is:"<<cost<<std::endl;



    return 0;
}
