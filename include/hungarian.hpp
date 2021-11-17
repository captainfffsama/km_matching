#ifndef _HUNGARIAN_H
#define _HUNGARIAN_

#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "debug.hpp"

using namespace cv;

namespace hungarian {

// NOTE: 因为 opencv 的 point 不给力
using ZeroPoint=std::pair<int,int>;

class Hungarian
{
public:
    explicit Hungarian() {}
    /*!
     * @brief 针对给出的代价矩阵,计算最小匹配和最小匹配代价, 
     *
     * @param costMatrix Mat类型,代价矩阵,要求是方阵,且元素均大于等于0,在处理之前会将类型转化为CV_32F
     * @param matchResult 输出参数,匹配结果
     * @return 最小匹配的cost
     */
    float Solve(Mat& costMatrix,std::map<int,int>& matchResult); 
    void FindCoverLine(Mat& matrix,std::set<int>& hLines,std::set<int>& vLines);
    void FixMatrix(Mat& matrix,const std::set<int>& hLines,const std::set<int>& vLines);
private:
    void PreprocessCostMatrix(Mat& matrix);
    void getMatch(Mat& matrix,std::map<int,int>& matchResult);
    float getCost(const Mat& matrix,const std::map<int,int>& matchResult);
};

template<typename T> 
bool isInSet(const T& value,const std::set<T>& set)
{
    return !(set.find(value)==set.end());
}

void addLineInfo(int key,int value_e,std::map<int,std::set<int>>& linesInfo );
struct LineInfo{
    bool isH;
    std::vector<int> pts;


};


}

#endif
