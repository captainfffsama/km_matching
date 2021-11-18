#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
#include "hungarian.hpp"

namespace debug{
    void showMatchingResult(const std::vector<int>& a);
    void showPointInfo(const hungarian::PointInfo& ptinfo);
    void showMatrix(const hungarian::Flt2DMatrix& matrix);
    void showPairVec(const std::vector<std::pair<int,int>>& a);
}
#endif
