#include "admin.h"
#include "computerRoom.h"

Admin::Admin() {

}

Admin::Admin(string name, string password) {
    this->name = name;
    this->password = password;
    this->initVector();
    //��ʼ��������Ϣ
    ifstream ifs(COMPUTER_FILE, ios::in);
    ComputerRoom cr;
    while (ifs >> cr.id && ifs >> cr.capacity) {
        cv.push_back(cr);
    }
    cout << "��ǰ��������Ϊ��" << cv.size() << endl;
    ifs.close();
}

//��ʾ����Ա����
void Admin::show_view() {
    cout << endl;
    cout << "��ӭ����Ա��" << this->name << endl;
    cout << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.����˺�              |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.�鿴�˺�              |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.�鿴����             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.���ԤԼ             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.ע����¼             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << endl;
    cout << "��ѡ�����Ĳ����� " << endl;
    cout << endl;
}

//����˺�
void Admin::addUser() {
    cout << "������Ҫ��ӵ��û�����" << endl;
    cout << "1��ѧ��" << endl;
    cout << "2����ʦ" << endl;
    string fileName = "";
    string tip = "";
    string errorTip = "";
    int select = 0;
    while (true) {
        cin >> select;
        if (select == 1) {
            fileName = STUDENT_FILE;
            tip = "������ѧ�ţ�";
            errorTip = "��ѧ���Ѵ��ڣ�����������";
            break;
        } else if (select == 2) {
            fileName = TEACHER_FILE;
            tip = "�������ʦ��ţ�";
            errorTip = "�ù����Ѵ��ڣ�����������";
            break;
        } else {
            cout << "������������������" << endl;
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

    cout << "������������" << endl;
    cin >> name;

    cout << "���������룺" << endl;
    cin >> pwd;

    ofstream ofs(fileName, ios::out | ios::app);//ʹ��׷�ӵķ�ʽд���ļ�
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "�û���ӳɹ���" << endl;
    ofs.close();
    initVector();
    system("pause");
    system("cls");
}

//��ʾ�û�
void Admin::showUser() {
    cout << "��ѡ��鿴����" << endl;
    cout << "1��ѧ��" << endl;
    cout << "2����ʦ" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        if (stu_v.size() < 1) {
            cout << endl;
            cout << "ѧ����¼Ϊ��" << endl;
			system("pause");
			system("cls");
            return;
        }
        for (int i = 0; i < stu_v.size(); ++i) {
            cout << "ѧ�ţ�" << stu_v[i].id << "\t ������" << stu_v[i].name << endl;
        }
    } else {
        if (tea_v.size() < 1) {
            cout << endl;
            cout << "��ʦ��¼Ϊ��" << endl;
			system("pause");
			system("cls");
            return;
        }
        for (int i = 0; i < tea_v.size(); ++i) {
            cout << "���ţ�" << tea_v[i].tid << "\t ������" << tea_v[i].name << endl;
        }
    }

    system("pause");
    system("cls");
}

//�鿴������Ϣ
void Admin::queryComputerInfo() {
    if (cv.size() < 1) {
        cout << endl;
        cout << "������ϢΪ�գ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < cv.size(); ++i) {
        cout << "������ţ�" << cv[i].id << "\t ���������������" << cv[i].capacity << endl;
    }
    system("pause");
    system("cls");
}

//���ԤԼ��¼
void Admin::clearAllOrder() {
    ofstream ofs(ORDER_FILE, ios::trunc);
    cv.clear();
    ofs.close();
    cout<<"��ճɹ���"<<endl;
    system("pause");
    system("cls");
}

//���ڳ�ʼ����ʦ��ѧ����Ϣ
void Admin::initVector() {
    ifstream ifs(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "�ļ�������" << endl;
        return;
    }
    stu_v.clear();
    tea_v.clear();
    Student stu;
    while (ifs >> stu.id && ifs >> stu.name && ifs >> stu.password) {
        stu_v.push_back(stu);
    }
    cout << "��ǰѧ��������Ϊ��" << stu_v.size() << endl;
    ifs.close();

    //��ʼ����ʦ����
    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "�ļ�������" << endl;
        return;
    }

    Teacher t;
    while (ifs >> t.tid && ifs >> t.name && ifs >> t.password) {
        tea_v.push_back(t);
    }
    cout << "��ǰ��ʦ������Ϊ��" << tea_v.size() << endl;
    ifs.close();
}

//����ѧ������ʦ��ͬ����ظ���id
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