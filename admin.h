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
    //��ʾ����Ա����
    void show_view();

    //����˺�
    void addUser();

    //��ʾ�û�
    void showUser();

    //�鿴������Ϣ
    void queryComputerInfo();

    //���ԤԼ��¼
    void clearAllOrder();

    //���ڳ�ʼ����ʦ��ѧ����Ϣ
   void initVector();

   //����ѧ������ʦ��ͬ����ظ���id
   bool checkDuplication(int id,int type);

   //ѧ������
   vector<Student> stu_v;

   //�����ʦ����
   vector<Teacher> tea_v;

   //��ʼ��ʱ��Ż�������
   vector<ComputerRoom> cv;
};