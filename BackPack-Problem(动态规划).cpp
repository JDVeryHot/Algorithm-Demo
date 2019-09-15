//
//  main.cpp
//  BackPack-Problem
//
//  Created by weida on 16/08/2019.
//  Copyright © 2019 weida. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <array>
#include <queue>
#include <vector>
#include <algorithm>

static const double unknow_value = -1;
static const int COUNT = 10;
using namespace std;

typedef  struct mapKey{
    int index; //数组索引
    double maxWeight; //最大重量
    bool operator==(const mapKey & p) const{
        return maxWeight==p.maxWeight && index==p.index;
    }
    
}mapKey;

struct KeyHasher
{
    std::size_t operator()(const mapKey& k) const
    {
        return (long)(k.maxWeight)
                 ^ k.index;
    }
};


typedef  struct object{
    double weight; //重量
    double value; //价值
}object;

object obj[COUNT] = {{23,10},{15,18},{2,5},{3,2},{5,4},{3,17},{13,10},{30,50},{15,10},{17,28}};


unordered_map<mapKey, double,KeyHasher> createMap(double maxWeight,int index){
    
    unordered_map<mapKey, double,KeyHasher> globalMap;
    queue<mapKey> globalQueue;
    
    mapKey key = {index,maxWeight};
    globalQueue.push(key);
    
    for (;!globalQueue.empty();globalQueue.pop()) {
        
        mapKey front = globalQueue.front();
        int idx = front.index;
        double mw = front.maxWeight;
        
        if (idx == 0) {
            double ret = 0;
            if (obj[idx].weight <= mw) {
                ret = obj[idx].value;
            }
            globalMap[front] = ret;
            continue;
        }
        
        if (globalMap.find(front) == globalMap.end()) {
            globalMap[front] = unknow_value;
        }
        
        //情况1，包含最后一个元素
        double wei = mw-obj[idx].weight;
        if (wei >= 0) {
            mapKey containLast = {idx-1,wei};
            globalQueue.push(containLast);
        }
        
        //情况2，不包含最后一个元素
        mapKey unContainLast = {idx-1,mw};
        globalQueue.push(unContainLast);
    }
    
    return globalMap;
}

bool compareMapKey(mapKey&a,mapKey&b){
    return a.index < b.index;
}

double maxValue(double maxWeight,int index){
   
    unordered_map<mapKey, double,KeyHasher> &&dict = createMap(maxWeight, index);
    vector<mapKey> array(dict.size());
    
    int i = 0;
    for (auto& d : dict) {
        array[i] = d.first;
        i++;
    }
    
    //排好序
    sort(array.begin(), array.end(),compareMapKey);
    
    //按顺序填表
    for (auto &a : array) {
        double value = dict[a];
        if (unknow_value == value) {
            
            //情况1，包含最后一个元素
            double containLast = 0;
            if (a.maxWeight >= obj[a.index].weight) {
                containLast = obj[a.index].value + dict[{a.index-1,a.maxWeight-obj[a.index].weight}];
            }
            
            
            //情况2，不包含最后一个元素
            double unContainLast = dict[{a.index-1,a.maxWeight}];
            
            //最后的结果必然是上面两种情况的最大值
            dict[a] = max(containLast, unContainLast);
        }
    }
    
    return dict[{index,maxWeight}];
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
    
    double maxWeight = 5;
    
    printf("总重量不超过%lf---的最大价值为:%f",maxWeight,maxValue(maxWeight, COUNT-1));
    
    return 0;
}
