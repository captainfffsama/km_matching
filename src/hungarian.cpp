#include "hungarian.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/imgproc.hpp>

namespace hungarian {
float Hungarian::Solve(Mat& costMatrix, std::map<int,int>& matchResult)
{
    Mat dealCostMatrix=costMatrix.clone();
    dealCostMatrix.convertTo(dealCostMatrix, CV_32F);
    PreprocessCostMatrix(dealCostMatrix);
    std::set<int> hLines,vLines;
    FindCoverLine(dealCostMatrix,hLines,vLines);
    while((hLines.size()+vLines.size())<dealCostMatrix.rows)
    {
        // FixMatrix
        FixMatrix(dealCostMatrix,hLines,vLines);
        FindCoverLine(dealCostMatrix,hLines,vLines);
    }
    // Final
    debug::showSet(hLines);
    debug::showSet(vLines);

    std::cout<<dealCostMatrix<<std::endl;
    getMatch(dealCostMatrix,matchResult);
    float cost=getCost(costMatrix,matchResult);
    return cost;
} 

void Hungarian::PreprocessCostMatrix(Mat& matrix)
{
    int rowNum {matrix.rows};
    int colNum {matrix.cols};
    std::vector<float> eachRowMin (rowNum,HUGE_VALF);
    std::vector<float> eachColMin (colNum,HUGE_VALF);

    for(int i=0;i<rowNum;i++)
    {
        float* rowDataPtr=matrix.ptr<float> (i);
        for(int j=0;j<colNum;j++)
        {
            if(rowDataPtr[j]<eachRowMin[i])
            {
                eachRowMin[i]=rowDataPtr[j];
            }
        }
    }

    for(int i=0;i<rowNum;i++)
    {
        float* rowDataPtr=matrix.ptr<float> (i);
        for(int j=0;j<colNum;j++)
        {
            rowDataPtr[j]-=eachRowMin[i];
            if(rowDataPtr[j]<eachColMin[j])
            {
                eachColMin[j]=rowDataPtr[j];
            }
        }
    }

    for(int i=0;i<rowNum;i++)
    {
        float* rowDataPtr=matrix.ptr<float> (i);
        for(int j=0;j<colNum;j++)
        {
            rowDataPtr[j]-=eachColMin[j];
        }
    }
}

void Hungarian::FindCoverLine(Mat& matrix,std::set<int>& skipRow,std::set<int>& skipCol)
{
    int rowNum {matrix.rows};
    int colNum {matrix.cols};

    // int 负表示横线,正表述竖线,数值是索引
    // set表示哪些列或者行是零值
    // 注意这里存的数值索引是从1开始的
    std::map<int,std::set<int>> linesInfo;

    skipCol.clear();
    skipRow.clear();

    for(int i=0;i<rowNum;i++)
    {
        float* rowDataPtr=matrix.ptr<float> (i);
        for(int j=0;j<colNum;j++)
        {
            // 当前行遍历第一次发现0,然后遍历下所在的行列,确定选哪条线覆盖
            if(0.0==rowDataPtr[j])
            {
                addLineInfo(j+1,i+1,linesInfo);
                addLineInfo(-(i+1),j+1,linesInfo);
            }
        }
    }

    while(!linesInfo.empty())
    {
        int maxLineNum {0};
        int linesIdx {0};
        std::vector<int> emptyLine;
        for(auto it=linesInfo.begin();it!=linesInfo.end();it++)
        {
            if((*it).second.size()>maxLineNum)
            {
                maxLineNum=(*it).second.size();
                linesIdx=(*it).first;
            }
        }

        std::cout<<"linesIdx:"<<linesIdx<<std::endl;
        debug::showLineInfo(linesInfo);
        if(linesIdx<0)
        {
            skipRow.insert((-linesIdx)-1);
        }
        else
        {skipCol.insert(linesIdx-1);}
        auto needDelpt=linesInfo[linesIdx];
        linesInfo.erase(linesIdx);

        //fix linesinfo
        for(auto it=linesInfo.begin();it!=linesInfo.end();it++)
        {
            auto idx=(*it).first;
            if(linesIdx * idx<0)
            {
                auto rmIdx=linesIdx>0?linesIdx:-linesIdx;
                (*it).second.erase(rmIdx);
            }
            if((*it).second.size()==0)
            {
                emptyLine.push_back((*it).first);
            }
        }
        for(auto it=emptyLine.begin();it!=emptyLine.end();it++)
        {
            linesInfo.erase(*it);
        }
    }
}

void Hungarian::FixMatrix(Mat& matrix,const std::set<int>& hLines,const std::set<int>& vLines)
{
    //确定交点
    std::vector<ZeroPoint> crossPoints;
    for(auto i=hLines.begin();i!=hLines.end();i++)
    {
        for(auto j=vLines.begin();j!=vLines.end();j++)
        {
            ZeroPoint tmp_pt (*i,*j);
            crossPoints.push_back(tmp_pt);
        }
    }
    float minValue=HUGE_VALF;
    //找最小
    for(auto i=0;i<matrix.rows;i++)
    {
        if(isInSet(i,hLines))
        {
            continue;}
        float* data=matrix.ptr<float> (i);
        for(auto j=0;j<matrix.cols;j++)
        {
            if(isInSet(j, vLines))
            {continue;}
            if(minValue>data[j])
            {
                minValue=data[j];
            }

        }
    }

    for(auto i=0;i<matrix.rows;i++)
    {
        if(isInSet(i,hLines))
        {continue;}
        float* data=matrix.ptr<float> (i);
        for(auto j=0;j<matrix.cols;j++)
        {
            if(isInSet(j, vLines))
            {continue;}
            data[j] -= minValue;
        }
    }

    for(auto i=crossPoints.begin();i!=crossPoints.end();i++)
    {
        matrix.at<float> ((*i).first,(*i).second) +=minValue;
    }
}

// FIXME::这里计算有问题
void Hungarian::getMatch(Mat& matrix,std::map<int,int>& matchResult)
{
    int rowNum {matrix.rows};
    int colNum {matrix.cols};

    matchResult.clear();

    // int 负表示横线,正表述竖线,数值是索引
    // set表示哪些列或者行是零值
    // 注意这里存的数值索引是从1开始的
    std::map<int,std::set<int>> linesInfo;

    for(int i=0;i<rowNum;i++)
    {
        float* rowDataPtr=matrix.ptr<float> (i);
        for(int j=0;j<colNum;j++)
        {
            // 当前行遍历第一次发现0,然后遍历下所在的行列,确定选哪条线覆盖
            if(0.0==rowDataPtr[j])
            {
                addLineInfo(j+1,i+1,linesInfo);
                addLineInfo(-(i+1),j+1,linesInfo);
            }
        }
    }

    while(!linesInfo.empty())
    {
        int minLineNum {INT_MAX};
        int linesIdx {0};
        std::vector<int> emptyLine;
        for(auto it=linesInfo.begin();it!=linesInfo.end();it++)
        {
            if((*it).second.size()<minLineNum)
            {
                minLineNum=(*it).second.size();
                linesIdx=(*it).first;
            }
        }

        // 确定点
        auto pt_idx=*(linesInfo[linesIdx].begin());
        // std::cout<<"current lineInfo"<<std::endl;
        // 
        // for(auto it=linesInfo[linesIdx].begin();it!=linesInfo[linesIdx].end();it++)
        // {
        //     std::cout<<*it<<" ";
        // }
        // std::cout<<"\n=============================="<<std::endl;
        // linesIdx <0 表示存的行信息,pt_idx 此时表示列上的0的位置
        pt_idx= linesIdx<0 ? pt_idx:-pt_idx;
        // std::cout<<linesIdx<<pt_idx<<std::endl;
        auto NeedDelpt1=linesInfo[linesIdx];
        auto NeedDelpt2=linesInfo[pt_idx];

        auto ptRowIdx= linesIdx<0 ? linesIdx: pt_idx;
        ptRowIdx=-ptRowIdx-1;
        auto ptColIdx=linesIdx>0 ? linesIdx: pt_idx;
        ptColIdx=ptColIdx-1;

        // std::cout<<"DEBUG  "<<ptRowIdx<<" "<<ptColIdx<<std::endl;
        
        matchResult[ptRowIdx]=ptColIdx;

        linesInfo.erase(linesIdx);
        linesInfo.erase(pt_idx);

        //fix linesinfo
        for(auto it=linesInfo.begin();it!=linesInfo.end();it++)
        {
            auto idx=(*it).first;
            if(linesIdx * idx<0)
            {
                auto rmIdx=linesIdx>0?linesIdx:-linesIdx;
                (*it).second.erase(rmIdx);
            }
            if(pt_idx*idx<0)
            {
                auto rmIdx=pt_idx>0?pt_idx:-pt_idx;
                (*it).second.erase(rmIdx);
            }
            if((*it).second.size()==0)
            {
                emptyLine.push_back((*it).first);
            }
        }
        for(auto it=emptyLine.begin();it!=emptyLine.end();it++)
        {
            linesInfo.erase(*it);
        }
    }


}

float Hungarian::getCost(const Mat& matrix,const std::map<int,int>& matchResult)
{
    float cost {0};
    for(auto it=matchResult.begin();it!=matchResult.end();it++)
    {
        cost += matrix.at<float> ((*it).first,(*it).second);
    }
    return cost;
}

void addLineInfo(int key,int value_e,std::map<int,std::set<int>>& linesInfo )
{
    if(linesInfo.find(key)==linesInfo.end())
    {
        linesInfo.emplace(key,std::set<int> {value_e});
    }
    else
    {
        linesInfo[key].insert(value_e);
    }
}


}



