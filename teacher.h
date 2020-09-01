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

    //显示教师界面
    void show_view();

    //查看所有预约
    void queryAllOrder();

    //审核预约
    void AuditingOrder();

    //教师id
    int tid;
};