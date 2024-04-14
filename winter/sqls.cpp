#include<iostream>
#include"sqls.h"
#include<time.h>

#include"User.h"
#include"commodity.h"
#include"order.h"
#include"Administrator.h"
#include <fstream> 
#include <cassert>

using namespace std;
char target_s[100] = "command.txt";
char tem_s[1000];
string commands[100];
int num_command = 0;

bool select_commodity(std::string s) {

	if (s.find("WHERE") == -1)
	{
		PrintCommoditys();
		return true;
	}
	if (s.find("CONTAINS") != -1) {
		select_contain(s);
		return true;
	}
	if (s.find("WHERE")!=-1 &&s.find("=")!= -1 ){

		int opt = s.find("=");
		s.erase(0, opt + 2);
		print_baiotou_g();
		for (int i = 0; i < num_commodity; i++) {
			if (commoditys[i].seller_id == s)
				PrintCommodity(i);
		}
		cout << endl << "**********************************************************************************" << endl;
		return true;
}

	if (s.find("CONTAINS") == -1 && s.find("=") != -1) {

		int opt = s.find("=");
		s.erase(0, opt + 2);

		int m_index = 0;
		for (; m_index < num_commodity; ) {
			if (s == commoditys[m_index].g_id)
				break;
			m_index++;
		}

		cout << "*****************************************" << endl;
		cout << "商品ID：" << commoditys[m_index].g_id << endl;
		cout << "商品名称：" << commoditys[m_index].g_name << endl;
		cout << "商品价格：" << commoditys[m_index].g_price << endl;
		cout << "上架时间：" << commoditys[m_index].g_time << endl;
		cout << "商品描述：" << commoditys[m_index].g_descr << endl;
		cout << "商品卖家：" << commoditys[m_index].seller_id << endl;
		cout << "*****************************************" << endl;

		return true;
	}

	return true;

}

bool select_order(string s) {

	if (s.find("WHERE") == -1){
		PrintOrders();
		return true;
	}
	if (s.find("WHERE")!=  -1 && s.find("买家")!= -1    ) {

		int opt = s.find("=");
		s.erase(0, opt + 2);

		print_biaotou_o();

		for (int i = 0; i < num_order; i++) {
			if (orders[i].buyer_id == s)
				PrintOrder(i);
		}
		cout << endl << "****************************************************************" << endl;
		return true;
	}
	if (s.find("WHERE") != -1 && s.find("卖家") != -1) {

		int opt = s.find("=");
		s.erase(0, opt + 2);

		print_biaotou_o();

		for (int i = 0; i < num_order; i++) {
			if (orders[i].seller_id == s)
				PrintOrder(i);
		}
		cout << endl << "****************************************************************" << endl;
		return true;
	}
	return true;
}

bool select_user(string s) {

	if (s.find("WHERE") == -1)
	{
		PrintUsers();
		return true;
	}
	return true;
}

void SELECT_MODE(string s) {

	string t1 = getTime_s();
	commands[num_command] = t1 + s;
	num_command++;
	writecommand();

	if (s.find("commodity") != -1)
		select_commodity(s);
	else if (s.find("order") != -1)
		select_order(s);
	else if (s.find("user") != -1)
		select_user(s);
	}

void UPDATE_MODE(string s) {

	string t1 = getTime_s();
	commands[num_command] = t1 + s;
	num_command++;
	writecommand();
	if (s.find("user") != -1) {
		update_user(s);
	}
	else if (s.find("commodity") != -1) {
		update_commodity(s);
	}

}

bool update_commodity(string s) {
	if (s.find("商品状态") != -1) {
		int opt = s.find("ID");
		s.erase(0, opt + 5);


		int d_index = 0;
		for (; d_index < num_commodity; ) {
			if (s == commoditys[d_index].g_id)
				break;
			d_index++;
		}
		commoditys[d_index].g_state = "已下架";
		return true;
	}
	return true;
}

bool update_user(string s) {
	
	int opt = s.find("ID");
	s.erase(0, opt + 5);

	int d_index = 0;
	for (; d_index < num_User; ) {
		if (s == Users[d_index].uid)
			break;
		d_index++;
	}

	Users[d_index].u_state = "封禁";

	return true;

}

void INSERT_INTO_MODE(string s) {
	string t1 = getTime_s();
	commands[num_command] = t1 + s;
	num_command++;
	writecommand();
	if (s.find("order") != -1) {
		insert_order(s);
	}
	if (s.find("commodity") != -1) {
		insert_commodity(s);
	}
}

bool insert_commodity(string s) {
	int opt = s.find("(");
	s.erase(0, opt + 1);

	int t1 = s.find_first_of(",", 1);
	string name = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string price = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string num = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string descr = s.substr(0, t1);
	s.erase(0, t1 + 1);

	return true;
}

bool insert_order(string s) {
	int opt = s.find("(");
	s.erase(0, opt + 1);

	int t1 = s.find_first_of(",", 1);
	string c_id = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string o_price = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string o_num = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string o_time = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string b_id = s.substr(0, t1);
	s.erase(0, t1 + 1);

	t1 = s.find_first_of(",", 1);
	string s_id = s.substr(0, t1);
	s.erase(0, t1 + 1);

	return true;
}

void readcommand() {

	ifstream fs;

	fs.open(target_s);

	assert(fs.is_open() && "文件打开失败");

	num_command = 0;

	while (!fs.eof()) {

		fs.getline(tem_s, 1000);
		string s1(tem_s);
		commands[num_command] = s1;
		num_command++;
	}
}

void writecommand() {

	ofstream fs;

	fs.open(target_s);

	assert(fs.is_open() && "文件打开失败");

	for (int i = 0; i < num_command; i++) {

		fs << commands[i];
		

		if (i < num_command - 1)
			fs << endl;
	}
	fs.close();

}

void select_contain(string s) {

	int opt = s.find("CONTAINS");
	s.erase(0, opt + 9);

	print_baiotou_g();
	for (int i = 0; i < num_commodity; i++) {
		if (commoditys[i].g_name.find(s) != -1)
			PrintCommodity(i);
	}
	cout << endl << "**********************************************************************************" << endl;


}

void SQL(string s) {

	if (s.find("SELECT") != -1)
		SELECT_MODE(s);
	if (s.find("UPDATE") != -1)
		UPDATE_MODE(s);
	if (s.find("INSERT INTO") != -1)
		INSERT_INTO_MODE(s);
}

//SELECT * FROM commodity   管理员查看所有商品
		//SELECT * FROM commodity WHERE 名称 CONTAINS  //搜索商品
	//UPDATE commodity SET 商品状态 = 已下架 WHERE 商品 ID = M001 //下架商品
//SELECT * FROM order //查看所有订单
//SELECT * FROM user //查看所有用户
	//UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = U001   //封禁用户
	//UPDATE commodity SET 商品状态 = 已下架 WHERE 卖家ID = U001 //下架商品

//卖家
	//INSERT INTO commodity VALUES (东奥会纪念币，10.0,10，冬奥会纪念品)
		//SELECT * FROM commodity //查看发布商品
	//UPDATE commodity SET 价格=12.0 WHERE 商品 ID =M001
	//UPDATE commodity SET 商品状态 = 已下架 WHERE 商品 ID =M001
		//SELECT * FROM order

//买家
//SELECT * FROM commodity   
	//INSERT INTO order VALUES(T001,M001,10.0,2,2022-02=13,U002,U001)  
	//UPDATE commodity SET 数量 = ？ WHERE 商品ID =M001
		//SELECT * FROM commodity WHERE 名称 CONTAINS 纪念币
		//SELECT * FROM order
		//SELECT * FROM commodity where 商品ID CONTAINS M001

string getTime_s()
{
	time_t timep;
	time(&timep); //获取time_t类型的当前时间
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %T: ", localtime(&timep));//对日期和时间进行格式化
	return tmp;
}
