#include"window_mode.h"
#include<iostream>
#include"Administrator.h"
#include<string.h>
#include"User.h"
#include"caculate2.h"
#include"sql.h"
using namespace std;



void window_menu(){
	cout << "*********************************************" << endl;
	cout << "*       �ѽ��붫�¼���Ʒ����ƽ̨������      *" << endl;
	cout << "*********************************************" << endl;
	cout<<endl<< "��ѡ������Ҫ�Ĳ���" << endl;
	
	cout << "================================================================" << endl;
	cout << " 1.����Ա��½  2.�û�ע��  3.�û���¼  4.�˳�����  5.���������� " << endl;
	cout << "================================================================" << endl;}

void window_login() {


	window_menu();//չʾ   ��ѡ��˵� �� 


	while (true) {

		//system("cls");

		//system("color 0B");

		char opts[20];
		cin >> opts;
		string opt(opts);
		

		if (opt == "1") {
			administrator_mode();  window_menu();  //չʾ   ��ѡ��˵� ��  
			continue;}
		else if (opt == "2") {
			User_register(); window_menu();  //չʾ   ��ѡ��˵� ��  
			continue;
		}
		else if (opt == "3") { 
			user_mode(); window_menu();  //չʾ   ��ѡ��˵� ��  
			continue;}

		else if (opt == "4") {
			exit(-1);
		}
		else if (opt == "5") {
			ca(); window_menu();
			continue;
		}

		else {
			cout << "��������������Ҫ�Ĳ�������";
			continue;
		}


	}
}

bool User_register() {

	cout <<endl<< "��ӭע�ᶫ�¼���Ʒ����ƽ̨�˺ţ���"<<endl;
	cout << "ע��ÿ�ε�¼�˺Ž�������Ψһ�û�����½����"<<endl<<endl;

	bool c_n = false;
	
	cout << "�������û�����";
	string r_name;
	cin >> r_name;
	while (c_n == false) {
		int i = 0;
		for (; i < num_User; i++) {

			if (r_name == Users[i].u_name){
				cout << "���û����ѱ�ʹ�ã����������룺";
				cin >> r_name;
				c_n = false;
				break;

			}
			c_n = true;
		}

	}
	cout << "�����벻����9λ�������룺";
	string r_code;
	cin >> r_code;

	string r_phone;
	cout << "������������ϵ��ʽ��";
	cin >> r_phone;

	string r_address;
	cout << "���������ĵ�ַ��";
	cin >> r_address;



	double r_m;
	cout << "���ֵ�������";
	cin >> r_m;
	string r_money = std::to_string(r_m);
	int point = r_money.find(".");
	r_money.erase(point + 2, -1);

	string r_uid;
	//cout << "num:" << num_User + 1 << endl;
	if (num_User <= 8)
		r_uid = "U00" + std::to_string(num_User + 1);
	else if (num_User <= 98)
		r_uid = "U0" + std::to_string(num_User + 1);
	else r_uid = "U" + std::to_string(num_User + 1);

	cout << "*****************************"<<endl;

	cout << "�û�ID��" << r_uid << endl;
	cout << "�û�����" << r_name << endl;
	cout << "���룺" << r_code << endl;
	cout << "��ϵ��ʽ��" << r_phone << endl;
	cout << "��ַ��" << r_address << endl;
	cout << "�˻���" << r_money << endl;
	
	cout << "*****************************"<<endl;

	cout << "   --�����ɹ�--   "<<endl;

	Users[num_User].uid = r_uid;
	Users[num_User].u_name = r_name;
	Users[num_User].u_code = r_code;
	Users[num_User].u_phone = r_phone;
	Users[num_User].u_address = r_address;
	Users[num_User].credit_money = r_money;
	Users[num_User].u_state = "����";
	num_User++;
	writeuser();
	

	return true;

}

