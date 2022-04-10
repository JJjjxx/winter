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
	//程序运行之前先要读取文件

	window_login();
	

	//SQL("SELECT * FROM commodity");

	/*
	double a1 = 18888.0;
	string a = std::to_string(a1);
	int t =a.find(".");
	a.erase(t + 2, -1);
	cout << a;*/
	//在所有涉及到存入浮点数的地方 用此方法来保留一位有效数字！
	

	//writecommodity();
	//writeorder();
	//writeuser();
	
}
