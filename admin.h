#pragma once
#include<iostream>
#include<string>
#include"identity.h"
#include <fstream>
#include <vector>
#include "globalHeader.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
using namespace std;

class Admin: public Identity{

public:
    Admin();

    Admin(string name,string password);
    //显示管理员界面
    void show_view();

    //添加账号
    void addUser();

    //显示用户
    void showUser();

    //查看机房信息
    void queryComputerInfo();

    //清空预约记录
    void clearAllOrder();

    //用于初始化老师和学生信息
   void initVector();

   //根据学生和老师不同检查重复的id
   bool checkDuplication(int id,int type);

   //学生容器
   vector<Student> stu_v;

   //存放老师容器
   vector<Teacher> tea_v;

   //初始化时存放机房数据
   vector<ComputerRoom> cv;
};