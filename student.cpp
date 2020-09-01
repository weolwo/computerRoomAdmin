#include "student.h"
#include "order.h"

Student::Student() {

}

Student::Student(int id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;
    //��ʼ��������Ϣ
    ifstream ifs(COMPUTER_FILE, ios::in);
    ComputerRoom cr;
    while (ifs >> cr.id && ifs >> cr.capacity) {
        cv.push_back(cr);
    }
    cout << "��ǰ��������Ϊ��" << cv.size() << endl;
    ifs.close();
}

//��ʾѧ�����ܲ˵�
void Student::show_view() {
    cout << endl;
    cout << "��ӭѧ������" << this->name << endl;
    cout << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.����ԤԼ              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.�鿴����ԤԼ          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.ȡ��ԤԼ              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.ע����¼              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << endl;
    cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Student::applyOrder() {
    cout<<endl;
    cout << "��ܰ��ʾ����������ʱ��Ϊ��һ�����壡" << endl;
    cout << "����������ԤԼ��ʱ��" << endl;
    cout << "1������һ" << endl;
    cout << "2�����ڶ�" << endl;
    cout << "3��������" << endl;
    cout << "4��������" << endl;
    cout << "5��������" << endl;
    cout<<endl;
    int date = 0;
    int interval = 0;
    int roomId = 0;
    while (true) {
        cin >> date;
        if (date >= 1 && date <= 5) {
            break;
        } else {
            cout << "������������������" << endl;
        }
    }
    cout << "������ԤԼʱ��Σ�" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;
    while (true) {
        cin >> interval;
        if (interval >= 1 && interval <= 2) {
            break;
        } else {
            cout << "������������������" << endl;
        }
    }
    cout << "��ѡ�������" << endl;
    cout << endl;
    for (int i = 0; i < cv.size(); ++i) {
        cout<<endl;
        cout << "������ţ�" << cv[i].id << "\t ���������������" << cv[i].capacity << endl;
    }
    while (true) {
        cin >> roomId;
        if (roomId >= 1 && roomId <= 3) {
            break;
        } else {
            cout << "������������������" << endl;
        }
    }
    cout << "ԤԼ�ɹ������������..." << endl;
    //����ԤԼ��Ϣ���ļ�
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

//�鿴�Լ���ԤԼ
void Student::queryOrder() {
    Order order;
    if (order.size < 1) {
        cout << "����ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        //���ַ���תΪint,�Ȱ�c++����ַ���תΪc����ַ�������תΪint
        if (atoi(order.orderData[i]["stuId"].c_str()) == this->id) {
            cout<<endl;
            cout << "ԤԼ���ڣ� ��" << order.orderData[i]["date"];
            cout << " ʱ�Σ�" << (order.orderData[i]["interval"] == "1" ? "����" : "����");
            cout << " ������" << order.orderData[i]["roomId"];
            string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
            if (order.orderData[i]["status"] == "1") {
                status += "�����";
            } else if (order.orderData[i]["status"] == "2") {
                status += "ԤԼ�ɹ�";
            } else if (order.orderData[i]["status"] == "-1") {
                status += "���δͨ����ԤԼʧ��";
            } else {
                status += "ԤԼ��ȡ��";
            }
            cout << status << endl;
        }
    }
    system("pause");
    system("cls");
}

//�鿴����ԤԼ
void Student::queryAllOrder() {
    Order order;
    if (order.size < 1) {
        cout << "����ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        cout<<endl;
        cout << "ԤԼ���ڣ� ��" << order.orderData[i]["date"];
        cout << " ʱ�Σ�" << (order.orderData[i]["interval"] == "1" ? "����" : "����");
        cout << " ������" << order.orderData[i]["roomId"];
        cout << " ѧ�ţ�" << order.orderData[i]["stuId"];
        cout << " ������" << order.orderData[i]["stuName"];
        string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
        if (order.orderData[i]["status"] == "1") {
            status += "�����";
        } else if (order.orderData[i]["status"] == "2") {
            status += "ԤԼ�ɹ�";
        } else if (order.orderData[i]["status"] == "-1") {
            status += "���δͨ����ԤԼʧ��";
        } else {
            status += "ԤԼ��ȡ��";
        }
        cout << status << endl;

    }
    system("pause");
    system("cls");
}

//ȡ��ԤԼ
void Student::cancelOrder() {
    Order order;
    if (order.size < 1) {
        cout << "ԤԼ��¼Ϊ��" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "��ܰ��ʾ��ֻ֧��״̬������к�ԤԼ�ɹ��Ķ���ȡ��" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < order.size; ++i) {
        if (this->id == atoi(order.orderData[i]["stuId"].c_str())) {
            if (order.orderData[i]["status"] == "1" || order.orderData[i]["status"] == "2") {
                //�˴�����Ǹ����������ļ��е��к�
                v.push_back(i);
                cout << index++ << "�� ";
                cout << "ԤԼ���ڣ� ��" << order.orderData[i]["date"];
                cout << " ʱ�Σ�" << (order.orderData[i]["interval"] == "1" ? "����" : "����");
                cout << " ������" << order.orderData[i]["roomId"];
                string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
                if (order.orderData[i]["status"] == "1") {
                    status += "�����";
                } else if (order.orderData[i]["status"] == "2") {
                    status += "ԤԼ�ɹ�";
                }
                cout << status << endl;
            }
        }
    }
    cout << "������Ҫȡ���Ķ������,0�����أ�" << endl;
    int select = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                //ȡ�������б������ʵ�к� v[select - 1]
                order.orderData[v[select - 1]]["status"] = "0";
                order.updateOrder();
                cout << "ԤԼȡ���ɹ���" << endl;
                break;
            }
        } else {
            cout << "��������������������" << endl;
        }
    }
    system("pause");
    system("cls");
}