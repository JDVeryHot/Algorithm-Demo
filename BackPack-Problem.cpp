//
//  main.cpp
//  BackPack-Problem
//
//  Created by weida on 16/08/2019.
//  Copyright © 2019 weida. All rights reserved.
//

#include <iostream>
#include <map>

static const int COUNT = 10;
using namespace std;

typedef  struct mapKey{
    double maxWeight; //最大重量
    int index; //数组索引
    
    bool operator<(const mapKey & p) const{
        return (index * maxWeight) < (p.index * p.maxWeight);
    }
    
}mapKey;


typedef  struct object{
    double weight; //重量
    double value; //价值
}object;

object obj[COUNT] = {{23,10},{15,18},{2,5},{3,2},{5,4},{3,17},{13,10},{30,50},{15,10},{17,28}};

map<mapKey, double> globalMap;

/**
 从obj数组中第0个-第index个找出总重量不超过 maxWeight的最大价值
 
 @param maxWeight 最大总重量
 @param index 最后一个索引
 @return 从数组中第0个到第index中找到的总重量不超过 maxWeight的最大价值
 */
double maxValue(double maxWeight,int index){
   
    mapKey key = {maxWeight,index};
    
    if (globalMap.find(key) != globalMap.end()) {
        return globalMap[key];
    }
    
    
    if (index == 0) {
        double ret = 0;
        if (obj[index].weight <= maxWeight) {
             ret = obj[index].value;
        }
        
        globalMap[key] = ret;
        return ret;
    }
    
    //情况1，包含最后一个元素
    double containLast = 0;
    if (maxWeight >= obj[index].weight) {
        containLast = obj[index].value + maxValue(maxWeight-obj[index].weight, index-1);
    }
    //情况2，不包含最后一个元素
    double unContainLast = maxValue(maxWeight, index-1);

    //最后的结果必然是上面两种情况的最大值
    double maxValue = containLast>unContainLast?containLast:unContainLast;
    globalMap[key] = maxValue;
    
    return maxValue;
}

void printArry(){
    double sumWeight = 0;
    double sumValue  = 0;
    
    for (int i=0; i<COUNT; i++) {
        sumWeight += obj[i].weight;
        sumValue  += obj[i].value;
        printf("---重量:%f--价值:%f\n",obj[i].weight,obj[i].value);
    }
    
    printf("总重量--%f-总价值--%f\n",sumWeight,sumValue);
}

int main(int argc, char * argv[]) {
    
    printArry();
    
    double maxWeight = 2;
    
    printf("总重量不超过%lf---的最大价值为:%f",maxWeight,maxValue(maxWeight, COUNT-1));
    
    return 0;
}
