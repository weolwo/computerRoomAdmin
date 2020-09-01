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
	//��ʾѧ�����ܲ˵�
	void show_view();

	//����ԤԼ
	void applyOrder();

	//�鿴�Լ���ԤԼ
	void queryOrder();

	//�鿴����ԤԼ
    void queryAllOrder();

    //ȡ��ԤԼ
    void cancelOrder();

	//ѧ�����
	int id;

	//��ʼ��������Ϣ
	vector<ComputerRoom> cv;
};