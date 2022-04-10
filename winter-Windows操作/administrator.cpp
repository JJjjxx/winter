#include"Administrator.h"
#include<string>
#include<iostream>
#include"order.h"
#include"commodity.h"
#include"User.h"
#include <iomanip>

#include"sql.h"
using namespace std;

Administrator::Administrator() {
	ad_state = false;
}

void Administrator::Boss_manu(){
	cout <<endl;
	cout << "===============================================================================================" << endl;
	cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.解封用户 8.注销" << endl;
	cout << "===============================================================================================" << endl;
	cout <<endl<< "请输入你想要的操作数：\n";
}

void Administrator::Boss_login (){

	cout << "============已进入管理员登陆界面==============" << endl;
	
	cout << "请输入管理员名字：";

	string name;
	cin >> name;
	string bn(boss_name);
	while ( name != bn) {
		cout << "请重新输入名字: ";
		cin >> name;
	}

	cout << "请输入密码: ";
	string code;
	string bc(boss_code);
	cin >> code;
	
	while (code != bc) {
		cout << "请重新输入密码：";
		cin >> code;
	}

	ad_state = true;
	
	cout<<endl<< "      -----管理员登陆成功-----"<<endl<<endl;
	
}

void administrator_mode(){

	Administrator ad1;
	if (not ad1.ad_state) {
		ad1.Boss_login();
	} //登陆 管理员账号
		
	ad1.Boss_manu(); //展示管理员菜单

	while(true){

		//std::string opt;
		//getline(std::cin, opt);

		string opt;
		cin >> opt;


		if (opt == "1") { PrintCommoditys();  ad1.Boss_manu(); continue;}
		else if (opt == "2") { Goods_search(); ad1.Boss_manu(); continue; }
		else if (opt == "3") { ad1.Good_del(); ad1.Boss_manu(); continue; }
		else if (opt == "4") { SQL("SELECT * FROM order");   ad1.Boss_manu(); continue; }
		else if (opt == "5") { SQL("SELECT * FROM user");	 ad1.Boss_manu(); continue; }
		else if (opt == "6") { ad1.User_del();  ad1.Boss_manu(); continue; }
		else if (opt == "7") { ad1.User_deblock();  ad1.Boss_manu(); continue; }
		else if (opt == "8") { break; }
		else { cout << "请重新输入你想要的操作数：\n"; continue; }

	}
} 

void Administrator::All_Users  () const {

	cout << "*********************************************************************"<<endl;
	cout << setw(8) << std::left << "用户ID";
	cout << setw(8) << std::left << "用户名";
	cout << setw(12) << std::left << "联系方式";
	cout << setw(20) << std::left << "地址";
	cout << setw(12) << std::left << "钱包余额";
	cout << setw(8) << std::left << "用户状态" <<endl;

	for (int i = 0; i < num_User; i++) {
		this->PrintU(i);
	}
	cout << "*********************************************************************" << endl;
}

void Administrator::PrintU(int x)const {
	cout << setw(8) << std::left << Users[x].uid;
	cout << setw(8) << std::left << Users[x].u_name;
	cout << setw(12) << std::left << Users[x].u_phone;
	cout << setw(20) << std::left << Users[x].u_address;
	cout << setw(12) << std::left << Users[x].credit_money;
	cout << setw(8) << std::left << Users[x].u_state<< endl;
}

bool Administrator::Good_del() {

	cout << "请输入要下架的商品ID：";
	string m_id;
	cin >> m_id;


	int d_index = 0;

	for (; d_index < num_commodity; ) {
		if (m_id == commoditys[d_index].g_id )
			break;
		d_index++;
	}
	if (d_index == num_commodity)
	{
		cout << "未找到此商品!";
		return false;
	}


	PrintCommodity(d_index);

	cout << "请确认要下架该商品吗？输入 y/n";
	string y_n;
	cin >> y_n;
	if (y_n == "y") {

		string sq = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品 ID = " + m_id;
		SQL(sq);
		cout << "下架成功！";
		writecommodity();
		return true;
	}
	else {
		cout << "修改取消！";
		return false;
	}
}

void Administrator::All_Goods() const {
	PrintCommoditys();
	}//查看所有商品 

void Administrator::All_orders() const { 
	PrintOrders();
	} //查看所有订单

bool Administrator::User_del() {

	cout << "请输入要封禁的用户ID：";
	string m_id;
	cin >> m_id;
	
	int d_index = 0;

	for (; d_index < num_User; ) {
		if (m_id == Users[d_index].uid)
			break;
		d_index++;
	}
	if (d_index == num_User)
	{
		cout << "未找到此用户!";
		return false;
	}

	printbiaotou_u();
	PrintUser(d_index);
	cout << "***********************************************************************"<<endl;

	cout << "请确认要封禁该用户吗？输入 y/n"<<endl;
	string y_n;
	cin >> y_n;

	if (y_n == "y") {

		string sq = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = " + m_id;
		SQL(sq);

		cout << "封禁成功！";
		writeuser();
		return true;
	}

	else {
		cout << "封禁取消！";
		return false;
	}

}

bool Administrator::User_deblock() {

	cout << "请输入要解封用户ID：";
	string m_id;
	cin >> m_id;

	int d_index = 0;

	for (; d_index < num_User; ) {
		if (m_id == Users[d_index].uid)
			break;
		d_index++;
	}
	if (d_index == num_User)
	{
		cout << "未找到此用户!";
		return false;
	}

	printbiaotou_u();
	PrintUser(d_index);
	cout << "***********************************************************************" << endl;

	cout << "请确认要解封该用户吗？输入 y/n" << endl;

	string y_n;
	cin >> y_n;

	if (y_n == "y") {

		Users[d_index].u_state = "正常";
		cout << "解封成功！";
		writeuser();
		return true;
	}

	else {
		cout << "解封取消！";
		return false;
	}

}

