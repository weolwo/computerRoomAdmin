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

    //��¼ԤԼ������
    int size;

    //����ԤԼ��״̬
    void updateOrder();

    //��ų�ʼ��ԤԼ���ݣ�key��ʾ������value��ʾԤԼ����
    map<int, map<string, string>> orderData;
};