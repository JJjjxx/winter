#include<iostream>
#include"window_mode.h"
#include"order.h"
#include"User.h"
#include"Seller.h"
#include"sql.h"
#include"commodity.h"
#include"communication.h"
#include<string>




using namespace std;



int main(){
	
	
	ReadCommunication();
	ReadUser();
	ReadOrders();
	ReadCommodity();
	readcommand(); 
	//��������֮ǰ��Ҫ��ȡ�ļ�

	window_login();
	

	//SQL("SELECT * FROM commodity");

	/*
	double a1 = 18888.0;
	string a = std::to_string(a1);
	int t =a.find(".");
	a.erase(t + 2, -1);
	cout << a;*/
	//�������漰�����븡�����ĵط� �ô˷���������һλ��Ч���֣�
	

	//writecommodity();
	//writeorder();
	//writeuser();
	
}
