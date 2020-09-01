#include "student.h"
#include "order.h"

Student::Student() {

}

Student::Student(int id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;
    //初始化机房信息
    ifstream ifs(COMPUTER_FILE, ios::in);
    ComputerRoom cr;
    while (ifs >> cr.id && ifs >> cr.capacity) {
        cv.push_back(cr);
    }
    cout << "当前机房数量为：" << cv.size() << endl;
    ifs.close();
}

//显示学生功能菜单
void Student::show_view() {
    cout << endl;
    cout << "欢迎学生代表：" << this->name << endl;
    cout << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.申请预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.查看我的预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.查看所有预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.取消预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << endl;
    cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder() {
    cout<<endl;
    cout << "温馨提示：机房开放时间为周一到周五！" << endl;
    cout << "请输入申请预约的时间" << endl;
    cout << "1、星期一" << endl;
    cout << "2、星期二" << endl;
    cout << "3、星期三" << endl;
    cout << "4、星期四" << endl;
    cout << "5、星期五" << endl;
    cout<<endl;
    int date = 0;
    int interval = 0;
    int roomId = 0;
    while (true) {
        cin >> date;
        if (date >= 1 && date <= 5) {
            break;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    cout << "请输入预约时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while (true) {
        cin >> interval;
        if (interval >= 1 && interval <= 2) {
            break;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    cout << "请选择机房：" << endl;
    cout << endl;
    for (int i = 0; i < cv.size(); ++i) {
        cout<<endl;
        cout << "机房编号：" << cv[i].id << "\t 机房计算机数量：" << cv[i].capacity << endl;
    }
    while (true) {
        cin >> roomId;
        if (roomId >= 1 && roomId <= 3) {
            break;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    cout << "预约成功，正在审核中..." << endl;
    //保存预约信息到文件
    ofstream ofs(ORDER_FILE, ios::out | ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->id << " ";
    ofs << "stuName:" << this->name << " ";
    ofs << "roomId:" << roomId << " ";
    ofs << "status:" << 1 << endl;
    ofs.close();
    system("pause");
    system("cls");

}

//查看自己的预约
void Student::queryOrder() {
    Order order;
    if (order.size < 1) {
        cout << "暂无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        //把字符串转为int,先把c++风格字符串转为c风格字符串，再转为int
        if (atoi(order.orderData[i]["stuId"].c_str()) == this->id) {
            cout<<endl;
            cout << "预约日期： 周" << order.orderData[i]["date"];
            cout << " 时段：" << (order.orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 机房：" << order.orderData[i]["roomId"];
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
    }
    system("pause");
    system("cls");
}

//查看所有预约
void Student::queryAllOrder() {
    Order order;
    if (order.size < 1) {
        cout << "暂无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        cout<<endl;
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

//取消预约
void Student::cancelOrder() {
    Order order;
    if (order.size < 1) {
        cout << "预约记录为空" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "温馨提示：只支持状态是审核中和预约成功的订单取消" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < order.size; ++i) {
        if (this->id == atoi(order.orderData[i]["stuId"].c_str())) {
            if (order.orderData[i]["status"] == "1" || order.orderData[i]["status"] == "2") {
                //此处存的是该条数据再文件中的行号
                v.push_back(i);
                cout << index++ << "、 ";
                cout << "预约日期： 周" << order.orderData[i]["date"];
                cout << " 时段：" << (order.orderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << " 机房：" << order.orderData[i]["roomId"];
                string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
                if (order.orderData[i]["status"] == "1") {
                    status += "审核中";
                } else if (order.orderData[i]["status"] == "2") {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    cout << "请输入要取消的订单编号,0代表返回：" << endl;
    int select = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                //取出集合中保存的真实行号 v[select - 1]
                order.orderData[v[select - 1]]["status"] = "0";
                order.updateOrder();
                cout << "预约取消成功！" << endl;
                break;
            }
        } else {
            cout << "你输入有误，请重新输入" << endl;
        }
    }
    system("pause");
    system("cls");
}