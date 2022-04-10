#include"Buyer.h"
#include<iostream>
#include"User.h"
#include"commodity.h"
#include"order.h"
#include <stdlib.h>

#include"sql.h"
using namespace std;

//所有用户信息都已经存在Users数组里
void buyer_mode() {

	buyer b1;
	
	b1.User_login(Users[index_user], index_user);
	

	while (true) {
		b1.Buyer_manu();
		cout << "请输入操作：";
		string b_opt;
		cin >> b_opt;

		if (b_opt == "1") {
			SQL("SELECT * FROM commodity");
			continue;
		}
		else if (b_opt == "2") {
			b1.Buying();
			
			continue;
		}
		else if (b_opt == "3") {
			Goods_search(); 

			continue;
		}
		else if (b_opt == "4") {
			b1.Buyer_Check_Order();
			continue;
		}
		else if (b_opt == "5") {
			b1.Buyer_Check_Goods();//查看商品详细信息
			continue;
		}
		else if (b_opt == "6")
			break;
		else {
			cout << "请输入正确的操作数！！！";
			continue;
		}



	}
}

void buyer::Buyer_manu() {

	cout <<endl<< "=======================================================================================";
	cout <<endl<< "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面";
	cout <<endl<< "======================================================================================="<<endl;

}

void buyer::Buyer_Check_Order() {
	//SELECT * FROM order
	string sq = "SELECT * FROM order WHERE 买家ID = " + uid ;
	SQL(sq);
	/*
	print_biaotou_o();
	for (int i = 0; i < num_order; i++) {
		if (orders[i].buyer_id == uid)
			PrintOrder(i);
	}

	cout << endl << "****************************************************************" << endl;*/
}

bool buyer::Buying() {

	cout << "请输入商品ID：";
	string b_id;
	cin >> b_id;


	int m_index = 0;
	for (; m_index < num_commodity; ) {
		if (b_id == commoditys[m_index].g_id)
			break;
		m_index++;
	}

	if (m_index == num_commodity)
	{
		cout << "未找到此商品!";
		return false;
	}
	else if (uid == commoditys[m_index].seller_id) {
		cout << "请勿购买自己售卖的商品！！";
		return false;
	}
	if (commoditys[m_index].g_state == "已下架") {
		cout <<endl<< "查找失败！"<<endl;
		cout << "sorry！！！该商品已下架！！"<<endl;
		return false;

	}

	int all_sum = atoi(commoditys[m_index].g_sum.c_str());

	if (all_sum ==0) {
		cout << endl << "该商品暂时已售空！！" << endl;
		return false;
		
	}
	cout << "*****************************************" << endl;
	cout << "商品ID：" << commoditys[m_index].g_id << endl;
	cout << "商品名称：" << commoditys[m_index].g_name << endl;
	cout << "商品价格：" << commoditys[m_index].g_price << endl;
	cout << "上架时间：" << commoditys[m_index].g_time << endl;
	cout << "商品描述：" << commoditys[m_index].g_descr << endl;
	cout << "商品卖家：" << commoditys[m_index].seller_id << endl;
	cout << "*****************************************" << endl;

	//SELECT * FROM commodity where 商品ID CONTAINS M001

	//string sq = "SELECT * FROM commodity where 商品ID =" + b_id;
	//SQL(sq);

	cout << "请输入数量: ";

	int b_sum;
	cin >> b_sum;

	while (b_sum > all_sum) {
		cout << "正在售卖的商品数量只有" << all_sum << "个，请重新选择商品数量! "<<endl;
		cin >> b_sum; }

	string b_time = getTime();

	double b_money = atof(credit_money.c_str()) - b_sum * atof(commoditys[m_index].g_price.c_str());
	string b_m = std::to_string(b_money);
	int point = b_m.find(".");
	b_m.erase(point + 2, -1);

	if (b_money < 0) {
		cout << "您余额不足！害羞羞，这来都来了，还不快去充值！"<<endl;
		return false;
	}

	cout << "***************************"<<endl;
	cout << "交易提醒！"<<endl;
	cout << "交易时间：" << b_time<<endl;
	cout << "交易单价：" << commoditys[m_index].g_price << endl;
	cout << "交易数量：" << b_sum << endl;
	cout << "交易状态：交易成功" << endl;
	cout << "您的余额：" << b_m<<endl;
	cout << "***************************" << endl;
	
	//生成订单存入order
	

	orders[num_order].buyer_id = uid;
	orders[num_order].o_time = b_time;
	orders[num_order].good_id = b_id;
	orders[num_order].seller_id = commoditys[m_index].seller_id;
	orders[num_order].o_price = commoditys[m_index].g_price;
	orders[num_order].o_sum = std::to_string(b_sum);
	if (num_order <= 8)
		orders[num_order].o_id = "T00" + std::to_string(num_order+1);
	else if (num_commodity <= 98)
		orders[num_order].o_id = "T0" + std::to_string(num_order+1);
	else orders[num_order].o_id = "T" + std::to_string(num_order+1);
	num_order++;

	//INSERT INTO order VALUES(T001,M001,10.0,2,2022-02=13,U002,U001)  
	string sq2 = "INSERT INTO order VALUES(" + orders[num_order].o_id + "," + b_id + "," + commoditys[m_index].g_price + "," + std::to_string(b_sum) + "," + b_time + "," + commoditys[m_index].seller_id + "," + uid + ")";
	SQL(sq2);

	//writeorder
	writeorder();

	//改变community

	int ss_um = all_sum -b_sum;
	commoditys[m_index].g_sum = std::to_string(ss_um);

	//writecommonity
	writecommodity();
	//改变buyer_info

	credit_money = b_m;
	
	//改变use数据
	Users[index_user].credit_money = b_m;
	
	//readuse

	writeuser();
	ReadUser();

	//给卖家打钱

	int s_index = 0;

	for (; s_index < num_User; s_index++) {
		if (commoditys[m_index].seller_id == Users[s_index].uid)
			break;
	}
	double s_money = atof(Users[s_index].credit_money.c_str()) + b_sum * atof(commoditys[m_index].g_price.c_str());
	string s_m = std::to_string(s_money);
	int point_s = s_m.find(".");
	s_m.erase(point + 2, -1);
	Users[s_index].credit_money = s_m;

	writeuser();

	


	return true;

}

bool buyer::Buyer_Check_Goods() {
	cout << "请输入你想要查看的商品ID: ";
	string b_id;
	cin >> b_id;

	int m_index = 0;
	for (; m_index < num_commodity; ) {
		if (b_id == commoditys[m_index].g_id)
			break;
		m_index++;
	}

	if (m_index == num_commodity)
	{
		cout << "未找到此商品!";
		return false;
	}

	//string sq = "SELECT * FROM commodity WHERE 商品ID = " + b_id;
	//SQL(sq);
	
	cout << "*****************************************"<<endl;
	cout << "商品ID：" << commoditys[m_index].g_id << endl;
	cout << "商品名称：" << commoditys[m_index].g_name << endl;
	cout << "商品价格：" << commoditys[m_index].g_price << endl;
	cout << "上架时间：" << commoditys[m_index].g_time << endl;
	cout << "商品描述：" << commoditys[m_index].g_descr << endl;
	cout << "商品卖家：" << commoditys[m_index].seller_id << endl;
	cout << "*****************************************" << endl;
	
	return true;
	
}