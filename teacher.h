#pragma once
#include "identity.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

class Teacher:public Identity{

public:

    Teacher();

    Teacher(int tid,string name,string password);

    //��ʾ��ʦ����
    void show_view();

    //�鿴����ԤԼ
    void queryAllOrder();

    //���ԤԼ
    void AuditingOrder();

    //��ʦid
    int tid;
};