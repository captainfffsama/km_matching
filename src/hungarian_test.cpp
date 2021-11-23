#include <algorithm>
#include <iostream>
#include "hungarian.hpp"
#include "debug.hpp"

int main()
{
    auto hungarianSolver = hungarian::Hungarian();

    hungarian::Int2DMatrix costMatrix = {{10, 19, 8, 15},
                                         {10, 18, 7, 17},
                                         {13, 16, 9, 14},
                                         {12, 19, 8, 18}};
    // hungarian::Flt2DMatrix costMatrix = {{0, 1, 0, 1},
    //                                      {1, 0, 0, 1},
    //                                      {1, 1, 1, 0},
    //                                      {1, 0, 1, 1}};
    //
    std::vector<int> result;
    float cost = hungarianSolver.Solve(costMatrix, result);
    debug::showMatchingResult(result);
    std::cout << "cost is:" << cost << std::endl;

    return 0;
}
