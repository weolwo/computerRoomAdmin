#include<iostream>
#include <string>
#include <fstream>
#include "globalHeader.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"

using namespace std;

//����Ա,����c++�ڴ��εĹ����У�ָ�루����ָ�����ã�&����������ġ�
//https://www.cnblogs.com/urahyou/p/11841124.html
void adminManager(Identity *&user) {
    //��ʾ����Ա��������
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
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
        }
    }

}

void studentManager(Identity *&user) {
    //��ʾ����Ա��������
    Student *student = (Student *) user;
    while (true) {
        student->show_view();
        int select = 0;
        cin >> select;
        switch (select) {
            case 1:
                student->applyOrder();//����ԤԼ
                break;
            case 2:
                student->queryOrder();//�鿴�ҵ�ԤԼ
                break;
            case 3:
                student->queryAllOrder();//�鿴����ԤԼ
                break;
            case 4:
                student->cancelOrder();//ȡ��ԤԼ
                break;
            default:
                delete student;
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
        }
    }
}

void teacherManager(Identity *&user) {
    //��ʾ����Ա��������
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
                cout << "ע���ɹ���" << endl;
                system("pause");
                system("cls");
                return;
        }
    }
}

//��¼
void loginIn(string fileName, int type) {
    ifstream ifs(fileName, ios::in);
    //�ļ������ڵ����
    if (!ifs.is_open()) {
        cout << "�ļ������ڣ�" << endl;
        ifs.close();
        return;
    }
    Identity *user = NULL;
    int id;
    string name;
    string password;
    if (type == 1) {
        cout << "���������ѧ�ţ�" << endl;
        cin >> id;
    } else if (type == 2) {
        cout << "��������Ľ�ʦ��ţ�" << endl;
        cin >> id;
    }
    cout << "���������������" << endl;
    cin >> name;

    cout << "������������룺" << endl;
    cin >> password;

    //У�����������
    if (type == 1) {
        //ѧ����¼��֤
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == password) {
                cout << "У��ɹ���" << endl;
                user = new Student(id, name, password);
                system("pause");
                system("cls");
                //�������Ա����
                studentManager(user);
                return;
            }
        }
    } else if (type == 2) {
        //��ʦ��¼��֤
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == password) {
                cout << "У��ɹ���" << endl;
                user = new Teacher(id, name, password);
                system("pause");
                system("cls");
                teacherManager(user);
                return;
            }
        }
    } else {
        //����Ա��¼��֤
        string fName = "";
        string fPwd = "";
        while (ifs >> fName && ifs >> fPwd) {
            if (fName == name && fPwd == password) {
                cout << "У��ɹ���" << endl;
                user = new Admin(name, password);
                system("pause");
                system("cls");
                adminManager(user);
                return;
            }
        }
    }
    cout << "��֤��¼ʧ�ܣ�" << endl;
    system("pause");
    system("cls");
    return;
}

int main() {

    int choice = 0;

    while (true) {
        cout << endl;
        cout << "======================  ��ӭ��������ԤԼϵͳ  ====================="
             << endl;
        cout << endl;
        cout << endl << "�������������" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.ѧ������           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.��    ʦ           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.�� �� Ա           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.��    ��           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << endl;
        cout << "��������ѡ��: ";

        cin >> choice;

        switch (choice) {
            case 1:  //ѧ�����
                loginIn(STUDENT_FILE, 1);
                break;
            case 2:  //��ʦ���
                loginIn(TEACHER_FILE, 2);
                break;
            case 3:  //����Ա���
                loginIn(ADMIN_FILE, 3);
                break;
            case 0:  //�˳�ϵͳ
                cout << "�˳��ɹ�����ӭ�´�ʹ�ã�" << endl;
                system("pause");
                return 0;
            default:
                cout << "��������������ѡ��" << endl;
                system("pause");
                system("cls");
                break;
        }

    }

    system("pause");

    system("pause");
    return 0;
}