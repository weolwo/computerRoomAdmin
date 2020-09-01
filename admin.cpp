#include "admin.h"
#include "computerRoom.h"

Admin::Admin() {

}

Admin::Admin(string name, string password) {
    this->name = name;
    this->password = password;
    this->initVector();
    //初始化机房信息
    ifstream ifs(COMPUTER_FILE, ios::in);
    ComputerRoom cr;
    while (ifs >> cr.id && ifs >> cr.capacity) {
        cv.push_back(cr);
    }
    cout << "当前机房数量为：" << cv.size() << endl;
    ifs.close();
}

//显示管理员界面
void Admin::show_view() {
    cout << endl;
    cout << "欢迎管理员：" << this->name << endl;
    cout << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号              |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号              |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << endl;
    cout << "请选择您的操作： " << endl;
    cout << endl;
}

//添加账号
void Admin::addUser() {
    cout << "请输入要添加的用户类型" << endl;
    cout << "1、学生" << endl;
    cout << "2、老师" << endl;
    string fileName = "";
    string tip = "";
    string errorTip = "";
    int select = 0;
    while (true) {
        cin >> select;
        if (select == 1) {
            fileName = STUDENT_FILE;
            tip = "请输入学号：";
            errorTip = "该学号已存在，请重新输入";
            break;
        } else if (select == 2) {
            fileName = TEACHER_FILE;
            tip = "请输入教师编号：";
            errorTip = "该工号已存在，请重新输入";
            break;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    int id = 0;
    string name = "";
    string pwd = "";
    cout << tip << endl;
    while (true) {
        cin >> id;
        bool ret = checkDuplication(id, select);
        if (ret) {
            cout << errorTip << endl;
        } else {
            break;
        }
    }

    cout << "请输入姓名：" << endl;
    cin >> name;

    cout << "请输入密码：" << endl;
    cin >> pwd;

    ofstream ofs(fileName, ios::out | ios::app);//使用追加的方式写入文件
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "用户添加成功！" << endl;
    ofs.close();
    initVector();
    system("pause");
    system("cls");
}

//显示用户
void Admin::showUser() {
    cout << "请选择查看类型" << endl;
    cout << "1、学生" << endl;
    cout << "2、老师" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        if (stu_v.size() < 1) {
            cout << endl;
            cout << "学生记录为空" << endl;
			system("pause");
			system("cls");
            return;
        }
        for (int i = 0; i < stu_v.size(); ++i) {
            cout << "学号：" << stu_v[i].id << "\t 姓名：" << stu_v[i].name << endl;
        }
    } else {
        if (tea_v.size() < 1) {
            cout << endl;
            cout << "老师记录为空" << endl;
			system("pause");
			system("cls");
            return;
        }
        for (int i = 0; i < tea_v.size(); ++i) {
            cout << "工号：" << tea_v[i].tid << "\t 姓名：" << tea_v[i].name << endl;
        }
    }

    system("pause");
    system("cls");
}

//查看机房信息
void Admin::queryComputerInfo() {
    if (cv.size() < 1) {
        cout << endl;
        cout << "机房信息为空！" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < cv.size(); ++i) {
        cout << "机房编号：" << cv[i].id << "\t 机房计算机数量：" << cv[i].capacity << endl;
    }
    system("pause");
    system("cls");
}

//清空预约记录
void Admin::clearAllOrder() {
    ofstream ofs(ORDER_FILE, ios::trunc);
    cv.clear();
    ofs.close();
    cout<<"清空成功！"<<endl;
    system("pause");
    system("cls");
}

//用于初始化老师和学生信息
void Admin::initVector() {
    ifstream ifs(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在" << endl;
        return;
    }
    stu_v.clear();
    tea_v.clear();
    Student stu;
    while (ifs >> stu.id && ifs >> stu.name && ifs >> stu.password) {
        stu_v.push_back(stu);
    }
    cout << "当前学生的数量为：" << stu_v.size() << endl;
    ifs.close();

    //初始化老师数据
    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在" << endl;
        return;
    }

    Teacher t;
    while (ifs >> t.tid && ifs >> t.name && ifs >> t.password) {
        tea_v.push_back(t);
    }
    cout << "当前老师的数量为：" << tea_v.size() << endl;
    ifs.close();
}

//根据学生和老师不同检查重复的id
bool Admin::checkDuplication(int id, int type) {

    if (type == 1) {
        for (int i = 0; i < stu_v.size(); ++i) {
            if (stu_v[i].id == id) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < tea_v.size(); ++i) {
            if (tea_v[i].tid == id) {
                return true;
            }
        }
    }
    return false;
}