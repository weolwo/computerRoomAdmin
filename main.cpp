#include<iostream>
#include <string>
#include <fstream>
#include "globalHeader.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"

using namespace std;

//管理员,关于c++在传参的过程中，指针（）和指针引用（&）是有区别的。
//https://www.cnblogs.com/urahyou/p/11841124.html
void adminManager(Identity *&user) {
    //显示管理员操作界面
    Admin *admin = (Admin *) user;
    while (true) {
        admin->show_view();
        int select = 0;
        cin >> select;
        switch (select) {
            case 1:
                admin->addUser();
                break;
            case 2:
                admin->showUser();
                break;
            case 3:
                admin->queryComputerInfo();
                break;
            case 4:
                admin->clearAllOrder();
                break;
            default:
                delete admin;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
        }
    }

}

void studentManager(Identity *&user) {
    //显示管理员操作界面
    Student *student = (Student *) user;
    while (true) {
        student->show_view();
        int select = 0;
        cin >> select;
        switch (select) {
            case 1:
                student->applyOrder();//申请预约
                break;
            case 2:
                student->queryOrder();//查看我的预约
                break;
            case 3:
                student->queryAllOrder();//查看所有预约
                break;
            case 4:
                student->cancelOrder();//取消预约
                break;
            default:
                delete student;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
        }
    }
}

void teacherManager(Identity *&user) {
    //显示管理员操作界面
    Teacher *teacher = (Teacher *) user;
    while (true) {
        teacher->show_view();
        int select = 0;
        cin >> select;
        switch (select) {
            case 1:
                teacher->queryAllOrder();
                break;
            case 2:
                teacher->AuditingOrder();
                break;
            default:
                delete teacher;
                cout << "注销成功！" << endl;
                system("pause");
                system("cls");
                return;
        }
    }
}

//登录
void loginIn(string fileName, int type) {
    ifstream ifs(fileName, ios::in);
    //文件不存在的情况
    if (!ifs.is_open()) {
        cout << "文件不存在！" << endl;
        ifs.close();
        return;
    }
    Identity *user = NULL;
    int id;
    string name;
    string password;
    if (type == 1) {
        cout << "请输入你的学号：" << endl;
        cin >> id;
    } else if (type == 2) {
        cout << "请输入你的教师编号：" << endl;
        cin >> id;
    }
    cout << "请输入你的姓名：" << endl;
    cin >> name;

    cout << "请输入你的密码：" << endl;
    cin >> password;

    //校验输入的数据
    if (type == 1) {
        //学生登录验证
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == password) {
                cout << "校验成功！" << endl;
                user = new Student(id, name, password);
                system("pause");
                system("cls");
                //进入管理员界面
                studentManager(user);
                return;
            }
        }
    } else if (type == 2) {
        //教师登录验证
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == password) {
                cout << "校验成功！" << endl;
                user = new Teacher(id, name, password);
                system("pause");
                system("cls");
                teacherManager(user);
                return;
            }
        }
    } else {
        //管理员登录验证
        string fName = "";
        string fPwd = "";
        while (ifs >> fName && ifs >> fPwd) {
            if (fName == name && fPwd == password) {
                cout << "校验成功！" << endl;
                user = new Admin(name, password);
                system("pause");
                system("cls");
                adminManager(user);
                return;
            }
        }
    }
    cout << "验证登录失败！" << endl;
    system("pause");
    system("cls");
    return;
}

int main() {

    int choice = 0;

    while (true) {
        cout << endl;
        cout << "======================  欢迎来到机房预约系统  ====================="
             << endl;
        cout << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学生代表           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.老    师           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管 理 员           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退    出           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << endl;
        cout << "输入您的选择: ";

        cin >> choice;

        switch (choice) {
            case 1:  //学生身份
                loginIn(STUDENT_FILE, 1);
                break;
            case 2:  //老师身份
                loginIn(TEACHER_FILE, 2);
                break;
            case 3:  //管理员身份
                loginIn(ADMIN_FILE, 3);
                break;
            case 0:  //退出系统
                cout << "退出成功，欢迎下次使用！" << endl;
                system("pause");
                return 0;
            default:
                cout << "输入有误，请重新选择！" << endl;
                system("pause");
                system("cls");
                break;
        }

    }

    system("pause");

    system("pause");
    return 0;
}