#include "order.h"

//组装数据
void assembleData(string &data, map <string, string> &m) {
    string key;
    string value;
    int pos = data.find(":");
    if (pos != -1) {
        key = data.substr(0, pos);
        value = data.substr(pos + 1, data.size() - pos - 1);
        m.insert(make_pair(key, value));
    }
}

Order::Order() {
//初始化预约数据
    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;
    this->size = 0;
    ifstream ifs(ORDER_FILE, ios::in);
    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status) {
        //测试代码
        /*  cout << date << endl;
          cout << interval << endl;
          cout << stuId << endl;
          cout << stuName << endl;
          cout << roomId << endl;
          cout << status << endl;*/
        //date:2121

        //解析从文件中读取到的数据，存入map
        map <string, string> m;
        assembleData(date, m);
        assembleData(interval, m);
        assembleData(stuId, m);
        assembleData(stuName, m);
        assembleData(roomId, m);
        assembleData(status, m);
        this->orderData.insert(make_pair(this->size, m));
        this->size++;
    }
    ifs.close();
    //测试代码
    /*for (map<int, map<string, string>>::iterator it = orderData.begin(); it != orderData.end();it++)
    {
    	cout << "key = " << it->first << " value = " << endl;
    	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
    	{
    		cout << mit->first << " " << mit->second << " ";
    	}
    	cout << endl;
    }*/
}

void Order::updateOrder() {
    if (this->size == 0) {
        return;
    }

    //把以前的删掉后，重新写入
    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < size; i++) {
        ofs << "date:" << this->orderData[i]["date"] << " ";
        ofs << "interval:" << this->orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->orderData[i]["roomId"] << " ";
        ofs << "status:" << this->orderData[i]["status"] << endl;
    }
    ofs.close();
}