#ifndef _HUNGARIAN_H
#define _HUNGARIAN_H

#include <iostream>
#include <ostream>
#include <vector>

namespace hungarian
{

    struct PointInfo
    {
        bool isVisit;
        int weight;
        int matchPointIdx;
        int idx;

        PointInfo(bool is_v = false, int w = 0, int mPI = -1, int indix = -1) : isVisit(is_v), weight(w), matchPointIdx(mPI), idx(indix) {}
    };

    using PointsInfoVec = std::vector<PointInfo>;
    using Int2DMatrix = std::vector<std::vector<int>>;

    void clearPointsVisitFlag(PointsInfoVec &pts);

    class Hungarian
    {
    public:
        explicit Hungarian() {}
        int Solve(const Int2DMatrix &c_m, std::vector<int> &matchResult);

    private:
        int ptPairNum;
        PointsInfoVec xpts;
        PointsInfoVec ypts;
        Int2DMatrix costMatrix;

        void InitVertexWeight();

        bool DFS(int x_idx);
    };

}

#endif
