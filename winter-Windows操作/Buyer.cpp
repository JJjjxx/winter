#include"Buyer.h"
#include<iostream>
#include"User.h"
#include"commodity.h"
#include"order.h"
#include <stdlib.h>

#include"sql.h"
using namespace std;

//�����û���Ϣ���Ѿ�����Users������
void buyer_mode() {

	buyer b1;
	
	b1.User_login(Users[index_user], index_user);
	

	while (true) {
		b1.Buyer_manu();
		cout << "�����������";
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
			b1.Buyer_Check_Goods();//�鿴��Ʒ��ϸ��Ϣ
			continue;
		}
		else if (b_opt == "6")
			break;
		else {
			cout << "��������ȷ�Ĳ�����������";
			continue;
		}



	}
}

void buyer::Buyer_manu() {

	cout <<endl<< "=======================================================================================";
	cout <<endl<< "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������";
	cout <<endl<< "======================================================================================="<<endl;

}

void buyer::Buyer_Check_Order() {
	//SELECT * FROM order
	string sq = "SELECT * FROM order WHERE ���ID = " + uid ;
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

	cout << "��������ƷID��";
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
		cout << "δ�ҵ�����Ʒ!";
		return false;
	}
	else if (uid == commoditys[m_index].seller_id) {
		cout << "�������Լ���������Ʒ����";
		return false;
	}
	if (commoditys[m_index].g_state == "���¼�") {
		cout <<endl<< "����ʧ�ܣ�"<<endl;
		cout << "sorry����������Ʒ���¼ܣ���"<<endl;
		return false;

	}

	int all_sum = atoi(commoditys[m_index].g_sum.c_str());

	if (all_sum ==0) {
		cout << endl << "����Ʒ��ʱ���ۿգ���" << endl;
		return false;
		
	}
	cout << "*****************************************" << endl;
	cout << "��ƷID��" << commoditys[m_index].g_id << endl;
	cout << "��Ʒ���ƣ�" << commoditys[m_index].g_name << endl;
	cout << "��Ʒ�۸�" << commoditys[m_index].g_price << endl;
	cout << "�ϼ�ʱ�䣺" << commoditys[m_index].g_time << endl;
	cout << "��Ʒ������" << commoditys[m_index].g_descr << endl;
	cout << "��Ʒ���ң�" << commoditys[m_index].seller_id << endl;
	cout << "*****************************************" << endl;

	//SELECT * FROM commodity where ��ƷID CONTAINS M001

	//string sq = "SELECT * FROM commodity where ��ƷID =" + b_id;
	//SQL(sq);

	cout << "����������: ";

	int b_sum;
	cin >> b_sum;

	while (b_sum > all_sum) {
		cout << "������������Ʒ����ֻ��" << all_sum << "����������ѡ����Ʒ����! "<<endl;
		cin >> b_sum; }

	string b_time = getTime();

	double b_money = atof(credit_money.c_str()) - b_sum * atof(commoditys[m_index].g_price.c_str());
	string b_m = std::to_string(b_money);
	int point = b_m.find(".");
	b_m.erase(point + 2, -1);

	if (b_money < 0) {
		cout << "�����㣡�����ߣ����������ˣ�������ȥ��ֵ��"<<endl;
		return false;
	}

	cout << "***************************"<<endl;
	cout << "�������ѣ�"<<endl;
	cout << "����ʱ�䣺" << b_time<<endl;
	cout << "���׵��ۣ�" << commoditys[m_index].g_price << endl;
	cout << "����������" << b_sum << endl;
	cout << "����״̬�����׳ɹ�" << endl;
	cout << "������" << b_m<<endl;
	cout << "***************************" << endl;
	
	//���ɶ�������order
	

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

	//�ı�community

	int ss_um = all_sum -b_sum;
	commoditys[m_index].g_sum = std::to_string(ss_um);

	//writecommonity
	writecommodity();
	//�ı�buyer_info

	credit_money = b_m;
	
	//�ı�use����
	Users[index_user].credit_money = b_m;
	
	//readuse

	writeuser();
	ReadUser();

	//�����Ҵ�Ǯ

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
	cout << "����������Ҫ�鿴����ƷID: ";
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
		cout << "δ�ҵ�����Ʒ!";
		return false;
	}

	//string sq = "SELECT * FROM commodity WHERE ��ƷID = " + b_id;
	//SQL(sq);
	
	cout << "*****************************************"<<endl;
	cout << "��ƷID��" << commoditys[m_index].g_id << endl;
	cout << "��Ʒ���ƣ�" << commoditys[m_index].g_name << endl;
	cout << "��Ʒ�۸�" << commoditys[m_index].g_price << endl;
	cout << "�ϼ�ʱ�䣺" << commoditys[m_index].g_time << endl;
	cout << "��Ʒ������" << commoditys[m_index].g_descr << endl;
	cout << "��Ʒ���ң�" << commoditys[m_index].seller_id << endl;
	cout << "*****************************************" << endl;
	
	return true;
	
}