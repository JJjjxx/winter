#include"Seller.h"
#include<iostream>
#include"User.h"
#include"commodity.h"
#include"order.h"
#include <time.h>
#include"sql.h"
using namespace std;

void seller_mode() {

	seller s1;

	s1.User_login(Users[index_user], index_user);
	s1.Seller_manu();

	while (true) {
		cout << "请输入操作：";
		string s_opt;
		cin >> s_opt;

		if (s_opt == "1") {
			s1.Selling() ;
			s1.Seller_manu();
			continue;
		}
		else if (s_opt == "2") {
			s1.Seller_Check_Goods();
			s1.Seller_manu();
			continue;
		}
		else if (s_opt == "3") {
			s1.Modify_Good();
			s1.Seller_manu();
			continue;
		}
		else if (s_opt == "4") {

			s1.DeSelling();
			s1.Seller_manu();
			continue;
		}
		else if (s_opt == "5") {
			s1.Seller_Check_Order();
			s1.Seller_manu();
			continue;
		}
		
		else if (s_opt == "6")
			break;
		else {
			cout << "请输入正确的操作数！！！";
			continue;
		}



	}
}

void seller::Seller_manu() {

	cout << endl << "===================================================================================";
	cout << endl << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面";
	cout << endl << "===================================================================================" << endl;
}

bool seller::Selling() {
	cout << "请输入商品名称：";
	string g_name;
	cin >> g_name;

	cout << "请输入商品价格：";
	double price;
	cin >> price;
	string g_price = std::to_string(price);
	int point = g_price.find(".");
	g_price.erase(point + 2, -1);

	cout << "请输入商品数量：";
	int sum;
	cin >> sum;
	string g_num= std::to_string(sum);
	

	cout << "请输入商品描述：";
	string g_descr;
	cin >> g_descr;

	cout << endl<< "请确认发布的商品信息无误！"<<endl;
	cout << "***********************************" << endl;
	cout << "商品名称：" << g_name<< endl;
	cout << "商品价格：" << g_price<< endl;
	cout << "商品数量：" << g_num<< endl;
	cout << "商品描述：" << g_descr<< endl;
	cout << "***********************************" << endl<<endl;
	cout << "您确认要发布商品码？(y/n): ";



	string y_n;
	cin >> y_n;
	while (y_n != "y" && y_n != "n") {
		cout << "请输入(y/n)以确定您是否发布商品！"<<endl;
		cin >> y_n;
	}


	if (y_n == "y") {

		commoditys[num_commodity].g_name = g_name;
		commoditys[num_commodity].g_price = g_price;
		commoditys[num_commodity].g_sum = g_num;
		commoditys[num_commodity].g_descr = g_descr;
		if (num_commodity<=8)
			commoditys[num_commodity].g_id = "M00"+std::to_string(num_commodity+1);
		else if(num_commodity<=98)
			commoditys[num_commodity].g_id = "M0" + std::to_string(num_commodity+1);
		else commoditys[num_commodity].g_id = "M" + std::to_string(num_commodity+1);

		commoditys[num_commodity].g_time = getTime();
		commoditys[num_commodity].seller_id = uid;
		commoditys[num_commodity].g_state = "销售中";
		
		cout << "商品发布成功！";
		num_commodity++;
		writecommodity();


		//INSERT INTO commodity VALUES (东奥会纪念币，10.0,10，冬奥会纪念品)
		string sq = "INSERT INTO commodity VALUES (" + g_name +","+ g_price +","+ g_num +","+ g_descr + ")";
		SQL(sq);

		return true;

	}

	else if (y_n == "n") {
		cout << "发布取消！" << endl;
		return false;
	}
	else
		return false;
}

void seller::Seller_Check_Goods(){

	string com = "SELECT * FROM commodity WHERE 卖家ID = " + uid;
	SQL(com);
	/*
	print_baiotou_g();
	for (int i = 0; i < num_commodity; i++) {
		if (commoditys[i].seller_id == uid)
			PrintCommodity(i);
	}
	cout << endl << "**********************************************************************************" << endl;
	*/
}

void seller::Seller_Check_Order() {

	string com = "SELECT * FROM order WHERE 卖家ID = " + uid;
	SQL(com);
	/*
	print_biaotou_o();
	for (int i = 0; i < num_order; i++) {
		if (orders[i].seller_id == uid)
			PrintOrder(i);
	}
	cout << endl << "****************************************************************" << endl;*/
}

bool seller::Modify_Good() {

	cout << "请输入被修改的商品ID：";
	string m_id;
	cin >> m_id;

	int m_index = 0;
	for (; m_index < num_commodity; ) {
		if (m_id == commoditys[m_index].g_id && uid== commoditys[m_index].seller_id)
			break;
		m_index++;
	}
	if (m_index == num_commodity)
	{   cout << "未找到此商品!";
		return false;}


	cout << "请输入被修改的商品属性(1.价格 2.描述)：";
	string m_opt;
	cin >> m_opt;

	while (m_opt != "1"&&m_opt != "2") {
		cout << "请输入正确的操作符(1 或 2)：";
		cin >> m_opt;
	}
	if (m_opt == "1") {

		cout << "请输入被修改商品的价格：";
		double price;
		cin >> price;
		string m_price = std::to_string(price);
		int point = m_price.find(".");
		m_price.erase(point + 2, -1);

		cout << endl << "请确认发布的商品信息无误！"<<endl;
		cout << "***********************************" << endl;
		cout << "商品ID：" << commoditys[m_index].g_id << endl;
		cout << "商品价格：" << m_price << endl;
		cout << "商品数量：" << commoditys[m_index].g_sum << endl;
		cout << "商品描述：" << commoditys[m_index].g_descr << endl;
		cout << "***********************************" << endl << endl;
		cout << "您确认要发布商品码？(y/n): ";
		string y_n;
		cin >> y_n;
		if (y_n == "y") {
			commoditys[m_index].g_price = m_price;
			
			//UPDATE commodity SET 价格 = 12.0 WHERE 商品 ID = M001
			string sq = "UPDATE commodity SET 价格 = " + m_price + "WHERE 商品 ID = " + m_id;
			SQL(sq);

			cout << "修改成功！";
			writecommodity();
			return true;
		}
		else {
			cout << "修改取消！";
			return false;
		}
	}

	else if (m_opt == "2") {
		cout << "请输入被修改商品的描述：";
		string m_descr;
		cin >> m_descr;
		cout << endl << "请确认发布的商品信息无误！" << endl;
		cout << "***********************************" << endl;
		cout << "商品ID：" << commoditys[m_index].g_id << endl;
		cout << "商品价格：" << commoditys[m_index].g_price << endl;
		cout << "商品数量：" << commoditys[m_index].g_sum << endl;
		cout << "商品描述：" << m_descr << endl;
		cout << "***********************************" << endl << endl;
		cout << "您确认要发布商品码？(y/n): ";
		string y_n;
		cin >> y_n;
		if (y_n == "y") {
			commoditys[m_index].g_descr = m_descr;
			cout << "修改成功！";
			writecommodity();

			string sq = "UPDATE commodity SET 商品描述 = " + m_descr + "WHERE 商品 ID = " + m_id;
			SQL(sq);

			return true;
		}
		else {
			cout << "修改取消！";
			return false;
		}


	}
	else return false;

}  

bool seller::DeSelling(){

	cout << "请输入要下架的商品ID：";
	string m_id;
	cin >> m_id;

	int d_index = 0;

	for (; d_index < num_commodity; ) {
		if (m_id == commoditys[d_index].g_id && uid == commoditys[d_index].seller_id)
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
		commoditys[d_index].g_state = "已下架";
		cout << "下架成功！";
		writecommodity();

		//UPDATE commodity SET 商品状态 = 已下架 WHERE 商品 ID =M001
		string sq = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品 ID = " + m_id;
		SQL(sq);
		return true;
	}
	else {
		cout << "修改取消！";
		return false;
	}



}