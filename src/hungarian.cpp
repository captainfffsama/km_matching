#include "hungarian.hpp"
#include <math.h>
#include <limits.h>

namespace hungarian
{
    int Hungarian::Solve(const Int2DMatrix &c_m, std::vector<int> &matchResult)
    {
        costMatrix = c_m;
        ptPairNum = costMatrix.size();
        matchResult.clear();
        if (ptPairNum < 1 || (c_m[0].size() != ptPairNum))
        {
            std::cout << "ERROR: Matrix maybe not square or is empty!!!" << std::endl;
            return 0;
        }
        xpts.clear();
        ypts.clear();
        for (auto i = 0; i < ptPairNum; ++i)
        {
            xpts.push_back(PointInfo());
            ypts.push_back(PointInfo());
            matchResult.push_back(0);
        }
        InitVertexWeight();

        for (int x_idx = 0; x_idx < ptPairNum; x_idx++)
        {
            while (true)
            {
                clearPointsVisitFlag(xpts);
                clearPointsVisitFlag(ypts);

                if (DFS(x_idx))
                {
                    break;
                }

                int d{INT_MAX};
                for (auto xit = xpts.begin(); xit != xpts.end(); ++xit)
                {
                    if ((*xit).isVisit)
                    {
                        for (auto yit = ypts.begin(); yit != ypts.end(); ++yit)
                        {
                            if (!(*yit).isVisit)
                            {
                                d = std::min(d, (*xit).weight + (*yit).weight - costMatrix[(*xit).idx][(*yit).idx]);
                            }
                        }
                    }
                }

                if (INT_MAX == d)
                {
                    return INT_MAX;
                }

                for (auto xit = xpts.begin(); xit != xpts.end(); ++xit)
                {
                    // 在树内
                    if ((*xit).isVisit)
                    {
                        (*xit).weight -= d;
                    }
                }
                for (auto yit = ypts.begin(); yit != ypts.end(); ++yit)
                {
                    // 在树内
                    if ((*yit).isVisit)
                    {
                        (*yit).weight += d;
                    }
                }
            }
        }

        int totalCost{0};
        for (auto xit = xpts.begin(); xit != xpts.end(); ++xit)
        {
            totalCost += costMatrix[(*xit).idx][(*xit).matchPointIdx];
            matchResult[(*xit).idx] = (*xit).matchPointIdx;
        }
        return totalCost;
    }

    void Hungarian::InitVertexWeight()
    {
        for (int i = 0; i < ptPairNum; ++i)
        {
            int maxWeight{INT_MIN};
            for (int j = 0; j < ptPairNum; ++j)
            {
                maxWeight = std::max(maxWeight, costMatrix[i][j]);
            }
            xpts[i].weight = maxWeight;
            xpts[i].idx = i;
            ypts[i].idx = i;
        }
    }

    // 深度优先建立交错树
    bool Hungarian::DFS(int x_idx)
    {
        xpts[x_idx].isVisit = true;
        for (auto i = 0; i < ptPairNum; ++i)
        {
            if (!ypts[i].isVisit)
            {

                if ((xpts[x_idx].weight + ypts[i].weight) == costMatrix[xpts[x_idx].idx][ypts[i].idx])
                {
                    ypts[i].isVisit = true;
                    if (-1 == ypts[i].matchPointIdx || DFS(ypts[i].matchPointIdx))
                    {
                        xpts[x_idx].matchPointIdx = ypts[i].idx;
                        ypts[i].matchPointIdx = xpts[x_idx].idx;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void clearPointsVisitFlag(PointsInfoVec &pts)
    {
        for (auto it = pts.begin(); it != pts.end(); ++it)
        {
            (*it).isVisit = false;
        }
    }
}
