#include "teacher.h"
#include "order.h"

Teacher::Teacher() {}

Teacher::Teacher(int tid, string name, string password) {
    this->tid = tid;
    this->name = name;
    this->password = password;
}

//��ʾ��ʦ����
void Teacher::show_view() {
    cout << endl;
    cout << "��ӭ��ʦ��" << this->name << "��¼��" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.�鿴����ԤԼ          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.���ԤԼ              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.ע����¼              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << endl;
    cout << "��ѡ�����Ĳ����� " << endl;
}

//�鿴����ԤԼ
void Teacher::queryAllOrder() {
    Order order;
    if (order.size < 1) {
        cout << "����ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < order.size; ++i) {
        cout << endl;
        cout << i + 1 << "�� ";
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

//���ԤԼ
void Teacher::AuditingOrder() {
    Order order;
    if (order.size < 1) {
        cout << "ԤԼ��¼Ϊ��" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "�����Ǵ���˵�ԤԼ��¼��" << endl;
    cout << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < order.size; ++i) {

        if (order.orderData[i]["status"] == "1") {
            //�˴�����Ǹ����������ļ��е��к�
            v.push_back(i);
            cout << endl;
            cout << index++ << "�� ";
            cout << "ԤԼ���ڣ� ��" << order.orderData[i]["date"];
            cout << " ʱ�Σ�" << (order.orderData[i]["interval"] == "1" ? "����" : "����");
            cout << "ѧ��ѧ�ţ�" << order.orderData[i]["stuId"];
            cout << "ѧ��������" << order.orderData[i]["stuName"];
            cout << " ������" << order.orderData[i]["roomId"];
            cout << " ״̬�� δ���" << endl;  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
        }
    }
    cout << "������Ҫ��˵�ԤԼ��ţ�0�����أ�" << endl;
    int select = 0;
    int ret = 0;
    while (true) {
        cin >> select;
        if (select >= 0 && select <= v.size()) {
            if (select == 0) {
                break;
            } else {
                cout << "��������˽����" << endl;
                cout << "1�����ͨ��" << endl;
                cout << "2������ԤԼ" << endl;
                while (true) {
                    cin >> ret;
                    if (ret > 0 && ret < 3) {
                        if (ret == 1) {
                            order.orderData[v[select - 1]]["status"] = "2";
                        } else {
                            order.orderData[v[select - 1]]["status"] = "-1";
                        }
                        order.updateOrder();
                        cout << "�����ϣ�" << endl;
                        system("pause");
                        system("cls");
                        return;
                    }
                    cout << "��������������������" << endl;
                }
            }
        } else {
            cout << "��������������������" << endl;
        }
    }
    system("pause");
    system("cls");
}