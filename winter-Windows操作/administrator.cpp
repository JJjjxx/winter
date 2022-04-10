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
	cout << "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.����û� 8.ע��" << endl;
	cout << "===============================================================================================" << endl;
	cout <<endl<< "����������Ҫ�Ĳ�������\n";
}

void Administrator::Boss_login (){

	cout << "============�ѽ������Ա��½����==============" << endl;
	
	cout << "���������Ա���֣�";

	string name;
	cin >> name;
	string bn(boss_name);
	while ( name != bn) {
		cout << "��������������: ";
		cin >> name;
	}

	cout << "����������: ";
	string code;
	string bc(boss_code);
	cin >> code;
	
	while (code != bc) {
		cout << "�������������룺";
		cin >> code;
	}

	ad_state = true;
	
	cout<<endl<< "      -----����Ա��½�ɹ�-----"<<endl<<endl;
	
}

void administrator_mode(){

	Administrator ad1;
	if (not ad1.ad_state) {
		ad1.Boss_login();
	} //��½ ����Ա�˺�
		
	ad1.Boss_manu(); //չʾ����Ա�˵�

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
		else { cout << "��������������Ҫ�Ĳ�������\n"; continue; }

	}
} 

void Administrator::All_Users  () const {

	cout << "*********************************************************************"<<endl;
	cout << setw(8) << std::left << "�û�ID";
	cout << setw(8) << std::left << "�û���";
	cout << setw(12) << std::left << "��ϵ��ʽ";
	cout << setw(20) << std::left << "��ַ";
	cout << setw(12) << std::left << "Ǯ�����";
	cout << setw(8) << std::left << "�û�״̬" <<endl;

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

	cout << "������Ҫ�¼ܵ���ƷID��";
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
		cout << "δ�ҵ�����Ʒ!";
		return false;
	}


	PrintCommodity(d_index);

	cout << "��ȷ��Ҫ�¼ܸ���Ʒ������ y/n";
	string y_n;
	cin >> y_n;
	if (y_n == "y") {

		string sq = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��Ʒ ID = " + m_id;
		SQL(sq);
		cout << "�¼ܳɹ���";
		writecommodity();
		return true;
	}
	else {
		cout << "�޸�ȡ����";
		return false;
	}
}

void Administrator::All_Goods() const {
	PrintCommoditys();
	}//�鿴������Ʒ 

void Administrator::All_orders() const { 
	PrintOrders();
	} //�鿴���ж���

bool Administrator::User_del() {

	cout << "������Ҫ������û�ID��";
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
		cout << "δ�ҵ����û�!";
		return false;
	}

	printbiaotou_u();
	PrintUser(d_index);
	cout << "***********************************************************************"<<endl;

	cout << "��ȷ��Ҫ������û������� y/n"<<endl;
	string y_n;
	cin >> y_n;

	if (y_n == "y") {

		string sq = "UPDATE user SET �û�״̬ = ��� WHERE �û�ID = " + m_id;
		SQL(sq);

		cout << "����ɹ���";
		writeuser();
		return true;
	}

	else {
		cout << "���ȡ����";
		return false;
	}

}

bool Administrator::User_deblock() {

	cout << "������Ҫ����û�ID��";
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
		cout << "δ�ҵ����û�!";
		return false;
	}

	printbiaotou_u();
	PrintUser(d_index);
	cout << "***********************************************************************" << endl;

	cout << "��ȷ��Ҫ�����û������� y/n" << endl;

	string y_n;
	cin >> y_n;

	if (y_n == "y") {

		Users[d_index].u_state = "����";
		cout << "���ɹ���";
		writeuser();
		return true;
	}

	else {
		cout << "���ȡ����";
		return false;
	}

}

