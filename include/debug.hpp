#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
#include "opencv2/opencv.hpp"
#include "hungarian.hpp"

namespace debug{
    void showLineInfo(const std::map<int,std::set<int>>& linesInfo);
    void showSet(const std::set<int>& a);
    void showMatchingResult(const std::vector<int>& a);
    void showPointInfo(const hungarian::PointInfo& ptinfo);
}
#endif
