#include <iomanip>
#include<iostream>
#include<string>
#include <fstream> 
#include"order.h"
#include <cassert>

#include"sqls.h"
using namespace std;

static read_line lin[20];

int num_order = 0;
Order orders[20];

char target_o[100] = "order.txt";

void ReadOrders() {
	

	FILE* fp = fopen(target_o, "r");

	if (fp == NULL) { cout << "打开失败";  exit(-1); }
	if (fp) {
		fscanf(fp, "%s", lin[num_order].line);
		while (fscanf(fp, "%s", lin[num_order].line) != EOF)
			num_order++;
		fclose(fp);}
	
	
	for (int i = 0; i < num_order; i++) {
		
		string s1(lin[i].line);  //先将第一行存在 s1（string）类型中 
		
		int t1 = s1.find_first_of(",", 1);
		orders[i].o_id = s1.substr(0, t1);
		s1.erase(0, t1 + 1);
		
		t1 = s1.find_first_of(",", 1);
		orders[i].good_id = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		orders[i].o_price = s1.substr(0, t1);
		s1.erase(0, t1 + 1);
		
		t1 = s1.find_first_of(",", 1);
		orders[i].o_sum = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		orders[i].o_time = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		orders[i].seller_id = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		orders[i].buyer_id = s1.substr(0, t1);
		s1.erase(0, t1 + 1);
	}
}

void PrintOrder(int x) {
	cout << setw(12) << std::left << orders[x].o_id;
	cout << setw(12) << std::left << orders[x].good_id;
	cout << setw(12) << std::left << orders[x].o_price;
	cout << setw(12) << std::left << orders[x].o_sum;
	cout << setw(12) << std::left << orders[x].o_time;
	cout << setw(12) << std::left << orders[x].seller_id;
	cout << setw(12) << std::left << orders[x].buyer_id << endl;
}

void print_biaotou_o() {
	cout << endl << "****************************************************************" << endl;
	cout << setw(12) << std::left << "订单ID";
	cout << setw(12) << std::left << "商品ID";
	cout << setw(12) << std::left << "交易单价";
	cout << setw(12) << std::left << "数量";
	cout << setw(12) << std::left << "交易时间";
	cout << setw(12) << std::left << "卖家ID";
	cout << setw(12) << std::left << "买家ID" << endl;
}

void PrintOrders() {
	print_biaotou_o();
	for (int i = 0; i < num_order; i++) {
		PrintOrder(i);
	}
}

void writeorder() {

	ofstream fs;

	fs.open(target_o);
	assert(fs.is_open() && "文件打开失败");

	fs << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID" << endl;
	for (int i = 0; i < num_order; i++) {
		fs << orders[i].o_id << ",";
		fs << orders[i].good_id << ",";
		fs << orders[i].o_price << ",";
		fs << orders[i].o_sum << ",";
		fs << orders[i].o_time << ",";
		fs << orders[i].seller_id << ",";
		fs << orders[i].buyer_id ;
		if (i < num_order - 1)
			fs << endl;
	}
	fs.close();
}
