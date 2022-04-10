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
		cout << "�����������";
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
			cout << "��������ȷ�Ĳ�����������";
			continue;
		}



	}
}

void seller::Seller_manu() {

	cout << endl << "===================================================================================";
	cout << endl << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������";
	cout << endl << "===================================================================================" << endl;
}

bool seller::Selling() {
	cout << "��������Ʒ���ƣ�";
	string g_name;
	cin >> g_name;

	cout << "��������Ʒ�۸�";
	double price;
	cin >> price;
	string g_price = std::to_string(price);
	int point = g_price.find(".");
	g_price.erase(point + 2, -1);

	cout << "��������Ʒ������";
	int sum;
	cin >> sum;
	string g_num= std::to_string(sum);
	

	cout << "��������Ʒ������";
	string g_descr;
	cin >> g_descr;

	cout << endl<< "��ȷ�Ϸ�������Ʒ��Ϣ����"<<endl;
	cout << "***********************************" << endl;
	cout << "��Ʒ���ƣ�" << g_name<< endl;
	cout << "��Ʒ�۸�" << g_price<< endl;
	cout << "��Ʒ������" << g_num<< endl;
	cout << "��Ʒ������" << g_descr<< endl;
	cout << "***********************************" << endl<<endl;
	cout << "��ȷ��Ҫ������Ʒ�룿(y/n): ";



	string y_n;
	cin >> y_n;
	while (y_n != "y" && y_n != "n") {
		cout << "������(y/n)��ȷ�����Ƿ񷢲���Ʒ��"<<endl;
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
		commoditys[num_commodity].g_state = "������";
		
		cout << "��Ʒ�����ɹ���";
		num_commodity++;
		writecommodity();


		//INSERT INTO commodity VALUES (���»����ң�10.0,10�����»����Ʒ)
		string sq = "INSERT INTO commodity VALUES (" + g_name +","+ g_price +","+ g_num +","+ g_descr + ")";
		SQL(sq);

		return true;

	}

	else if (y_n == "n") {
		cout << "����ȡ����" << endl;
		return false;
	}
	else
		return false;
}

void seller::Seller_Check_Goods(){

	string com = "SELECT * FROM commodity WHERE ����ID = " + uid;
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

	string com = "SELECT * FROM order WHERE ����ID = " + uid;
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

	cout << "�����뱻�޸ĵ���ƷID��";
	string m_id;
	cin >> m_id;

	int m_index = 0;
	for (; m_index < num_commodity; ) {
		if (m_id == commoditys[m_index].g_id && uid== commoditys[m_index].seller_id)
			break;
		m_index++;
	}
	if (m_index == num_commodity)
	{   cout << "δ�ҵ�����Ʒ!";
		return false;}


	cout << "�����뱻�޸ĵ���Ʒ����(1.�۸� 2.����)��";
	string m_opt;
	cin >> m_opt;

	while (m_opt != "1"&&m_opt != "2") {
		cout << "��������ȷ�Ĳ�����(1 �� 2)��";
		cin >> m_opt;
	}
	if (m_opt == "1") {

		cout << "�����뱻�޸���Ʒ�ļ۸�";
		double price;
		cin >> price;
		string m_price = std::to_string(price);
		int point = m_price.find(".");
		m_price.erase(point + 2, -1);

		cout << endl << "��ȷ�Ϸ�������Ʒ��Ϣ����"<<endl;
		cout << "***********************************" << endl;
		cout << "��ƷID��" << commoditys[m_index].g_id << endl;
		cout << "��Ʒ�۸�" << m_price << endl;
		cout << "��Ʒ������" << commoditys[m_index].g_sum << endl;
		cout << "��Ʒ������" << commoditys[m_index].g_descr << endl;
		cout << "***********************************" << endl << endl;
		cout << "��ȷ��Ҫ������Ʒ�룿(y/n): ";
		string y_n;
		cin >> y_n;
		if (y_n == "y") {
			commoditys[m_index].g_price = m_price;
			
			//UPDATE commodity SET �۸� = 12.0 WHERE ��Ʒ ID = M001
			string sq = "UPDATE commodity SET �۸� = " + m_price + "WHERE ��Ʒ ID = " + m_id;
			SQL(sq);

			cout << "�޸ĳɹ���";
			writecommodity();
			return true;
		}
		else {
			cout << "�޸�ȡ����";
			return false;
		}
	}

	else if (m_opt == "2") {
		cout << "�����뱻�޸���Ʒ��������";
		string m_descr;
		cin >> m_descr;
		cout << endl << "��ȷ�Ϸ�������Ʒ��Ϣ����" << endl;
		cout << "***********************************" << endl;
		cout << "��ƷID��" << commoditys[m_index].g_id << endl;
		cout << "��Ʒ�۸�" << commoditys[m_index].g_price << endl;
		cout << "��Ʒ������" << commoditys[m_index].g_sum << endl;
		cout << "��Ʒ������" << m_descr << endl;
		cout << "***********************************" << endl << endl;
		cout << "��ȷ��Ҫ������Ʒ�룿(y/n): ";
		string y_n;
		cin >> y_n;
		if (y_n == "y") {
			commoditys[m_index].g_descr = m_descr;
			cout << "�޸ĳɹ���";
			writecommodity();

			string sq = "UPDATE commodity SET ��Ʒ���� = " + m_descr + "WHERE ��Ʒ ID = " + m_id;
			SQL(sq);

			return true;
		}
		else {
			cout << "�޸�ȡ����";
			return false;
		}


	}
	else return false;

}  

bool seller::DeSelling(){

	cout << "������Ҫ�¼ܵ���ƷID��";
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
		cout << "δ�ҵ�����Ʒ!";
		return false;
	}

	
	PrintCommodity(d_index);

	cout << "��ȷ��Ҫ�¼ܸ���Ʒ������ y/n";
	string y_n;
	cin >> y_n;
	if (y_n == "y") {
		commoditys[d_index].g_state = "���¼�";
		cout << "�¼ܳɹ���";
		writecommodity();

		//UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��Ʒ ID =M001
		string sq = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��Ʒ ID = " + m_id;
		SQL(sq);
		return true;
	}
	else {
		cout << "�޸�ȡ����";
		return false;
	}



}