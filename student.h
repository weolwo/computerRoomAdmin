 #pragma once
#include<iostream>
#include<string>
#include<vector>
#include "globalHeader.h"
#include <fstream>
#include"identity.h"
#include "computerRoom.h"
using namespace std;

class Student :public Identity {

public:
    Student();

    Student(int id,string name,string password);
	//显示学生功能菜单
	void show_view();

	//申请预约
	void applyOrder();

	//查看自己的预约
	void queryOrder();

	//查看所有预约
    void queryAllOrder();

    //取消预约
    void cancelOrder();

	//学生编号
	int id;

	//初始化机房信息
	vector<ComputerRoom> cv;
};