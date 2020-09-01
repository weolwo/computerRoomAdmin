#include "teacher.h"
#include "order.h"

Teacher::Teacher() {}

Teacher::Teacher(int tid, string name, string password) {
    this->tid = tid;
    this->name = name;
    this->password = password;
}

//显示教师界面
void Teacher::show_view() {
    cout << endl;
    cout << "欢迎教师：" << this->name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.查看所有预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.审核预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << endl;
    cout << "请选择您的操作： " << endl;
}

//查看所有预约
void Teacher::queryAllOrder() {
    Order order;
    if (order.size < 1) {
        cout << "暂无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        cout << endl;
        cout << i + 1 << "、 ";
        cout << "预约日期： 周" << order.orderData[i]["date"];
        cout << " 时段：" << (order.orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 机房：" << order.orderData[i]["roomId"];
        cout << " 学号：" << order.orderData[i]["stuId"];
        cout << " 姓名：" << order.orderData[i]["stuName"];
        string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (order.orderData[i]["status"] == "1") {
            status += "审核中";
        } else if (order.orderData[i]["status"] == "2") {
            status += "预约成功";
        } else if (order.orderData[i]["status"] == "-1") {
            status += "审核未通过，预约失败";
        } else {
            status += "预约已取消";
        }
        cout << status << endl;

    }
    system("pause");
    system("cls");
}

//审核预约
void Teacher::AuditingOrder() {
    Order order;
    if (order.size < 1) {
        cout << "预约记录为空" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "以下是待审核的预约记录：" << endl;
    cout << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < order.size; ++i) {

        if (order.orderData[i]["status"] == "1") {
            //此处存的是该条数据再文件中的行号
            v.push_back(i);
            cout << endl;
            cout << index++ << "、 ";
            cout << "预约日期： 周" << order.orderData[i]["date"];
            cout << " 时段：" << (order.orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << "学生学号：" << order.orderData[i]["stuId"];
            cout << "学生姓名：" << order.orderData[i]["stuName"];
            cout << " 机房：" << order.orderData[i]["roomId"];
            cout << " 状态： 未审核" << endl;  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
        }
    }
    cout << "请输入要审核的预约编号，0代表返回：" << endl;
    int select = 0;
    int ret = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                cout << "请输入审核结果：" << endl;
                cout << "1、审核通过" << endl;
                cout << "2、驳回预约" << endl;
                while (true) {
                    cin >> ret;
                    if (ret > 0 && ret < 3) {
                        if (ret == 1) {
                            order.orderData[v[select - 1]]["status"] = "2";
                        } else {
                            order.orderData[v[select - 1]]["status"] = "-1";
                        }
                        order.updateOrder();
                        cout << "审核完毕！" << endl;
                        system("pause");
                        system("cls");
                        return;
                    }
                    cout << "你输入有误，请重新输入" << endl;
                }
            }
        } else {
            cout << "你输入有误，请重新输入" << endl;
        }
    }
    system("pause");
    system("cls");
}