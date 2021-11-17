#include <algorithm>
#include <iostream>
#include "hungarian.hpp"
#include "debug.hpp"


int main()
{
    auto hungarianSolver=hungarian::Hungarian();
    // cv::Mat testMat=(Mat_<float> (4,4) <<0, 4, 0, 2,1, 4, 0, 5,2, 0, 0, 0,2, 4, 0, 5);
    cv::Mat testMat=(Mat_<float> (4,4)<< 0, 4, 1, 2, 0, 3, 0, 4, 2, 0, 1, 0,  1, 3, 0, 4);
    std::cout<<"need deal mat: \n"<<testMat<<std::endl;

    std::set<int> vline,hline;
    hungarianSolver.FindCoverLine(testMat,hline,vline);
    std::cout<<"find line"<<std::endl;
    debug::showSet(vline);
    debug::showSet(hline);
    hungarianSolver.FixMatrix(testMat,hline,vline);
    std::cout<<"final result:\n";
    std::cout<<"v line"<<std::endl;
    debug::showSet(vline);
    debug::showSet(hline);
    std::cout<<testMat<<std::endl;
    std::cout<<"++++++++++"<<std::endl;

    return 0;
}
