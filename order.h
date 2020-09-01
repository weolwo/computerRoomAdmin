#pragma once

#include<iostream>
#include<string>
#include<map>
#include "globalHeader.h"
#include <fstream>
#include "computerRoom.h"
#include <algorithm>

using namespace std;

class Order {
public:
    Order();

    //记录预约的条数
    int size;

    //更新预约的状态
    void updateOrder();

    //存放初始化预约数据，key表示条数，value表示预约数据
    map<int, map<string, string>> orderData;
};