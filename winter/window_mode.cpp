#include"window_mode.h"
#include<iostream>
#include"Administrator.h"
#include<string.h>
#include"User.h"
#include"caculate2.h"
#include"sqls.h"
using namespace std;



void window_menu(){
	cout << "*********************************************" << endl;
	cout << "*       已进入东奥纪念品交易平台主窗口      *" << endl;
	cout << "*********************************************" << endl;
	cout<<endl<< "请选择你需要的操作" << endl;
	
	cout << "================================================================" << endl;
	cout << " 1.管理员登陆  2.用户注册  3.用户登录  4.退出程序  5.计算器测试 " << endl;
	cout << "================================================================" << endl;}

void window_login() {


	window_menu();//展示   “选项菜单 ” 


	while (true) {

		//system("cls");

		//system("color 0B");

		char opts[20];
		cin >> opts;
		string opt(opts);
		

		if (opt == "1") {
			administrator_mode();  window_menu();  //展示   “选项菜单 ”  
			continue;}
		else if (opt == "2") {
			User_register(); window_menu();  //展示   “选项菜单 ”  
			continue;
		}
		else if (opt == "3") { 
			user_mode(); window_menu();  //展示   “选项菜单 ”  
			continue;}

		else if (opt == "4") {
			exit(-1);
		}
		else if (opt == "5") {
			ca(); window_menu();
			continue;
		}

		else {
			cout << "请重新输入你想要的操作数：";
			continue;
		}


	}
}

bool User_register() {

	cout <<endl<< "欢迎注册东奥纪念品交易平台账号！！"<<endl;
	cout << "注意每次登录账号将依托于唯一用户名登陆！！"<<endl<<endl;

	bool c_n = false;
	
	cout << "请输入用户名：";
	string r_name;
	cin >> r_name;
	while (c_n == false) {
		int i = 0;
		for (; i < num_User; i++) {

			if (r_name == Users[i].u_name){
				cout << "该用户名已被使用！请重新输入：";
				cin >> r_name;
				c_n = false;
				break;

			}
			c_n = true;
		}

	}
	cout << "请输入不超过9位数的密码：";
	string r_code;
	cin >> r_code;

	string r_phone;
	cout << "请输入您的联系方式：";
	cin >> r_phone;

	string r_address;
	cout << "请输入您的地址：";
	cin >> r_address;



	double r_m;
	cout << "请充值适量金额";
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

	cout << "用户ID：" << r_uid << endl;
	cout << "用户名：" << r_name << endl;
	cout << "密码：" << r_code << endl;
	cout << "联系方式：" << r_phone << endl;
	cout << "地址：" << r_address << endl;
	cout << "账户余额：" << r_money << endl;
	
	cout << "*****************************"<<endl;

	cout << "   --创建成功--   "<<endl;

	Users[num_User].uid = r_uid;
	Users[num_User].u_name = r_name;
	Users[num_User].u_code = r_code;
	Users[num_User].u_phone = r_phone;
	Users[num_User].u_address = r_address;
	Users[num_User].credit_money = r_money;
	Users[num_User].u_state = "正常";
	num_User++;
	writeuser();
	

	return true;

}

