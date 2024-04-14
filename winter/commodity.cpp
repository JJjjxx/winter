#include<iostream>
#include<cstdio> 
#include<stdio.h>
#include<string.h>
#include <iomanip>
#include <fstream> 
#include <cassert>
#include"commodity.h"

#include"sqls.h"
using namespace std;


char tem[1000];
commodity commoditys[50];

//static read_line lin[50] ;

int num_commodity = 0;

char target_c[100] = "commodity.txt" ;

void PrintCommodity(int x) {
	
	cout<<setw(8)<<std::left<<commoditys[x].g_id; 
	cout<<setw(15)<<std::left<<commoditys[x].g_name;
	cout<<setw(8)<<std::left<<commoditys[x].g_price;
	cout<<setw(8)<<std::left<<commoditys[x].g_sum;
	cout<<setw(12)<<std::left<<commoditys[x].seller_id;
	cout<<setw(15)<<std::left<<commoditys[x].g_time;
	cout<<setw(15)<<std::left<<commoditys[x].g_state<<endl;
	
}
  
void print_baiotou_g() {
	cout << endl << "***********************************************************************************************" << endl;
	cout << setw(8) << std::left << "商品ID";
	cout << setw(15) << std::left << "名称";
	cout << setw(8) << std::left << "价格";
	cout << setw(8) << std::left << "数量";
	cout << setw(12) << std::left << "卖家ID";
	cout << setw(15) << std::left << "上架时间";
	cout << setw(15) << std::left << "商品状态" << endl;

}

void PrintCommoditys() {
	
	print_baiotou_g();
	for (int i = 0; i < num_commodity; i++) {
		PrintCommodity(i);
	}
	cout <<"***********************************************************************************************" << endl;
}

void ReadCommodity(){

	ifstream fs;

	fs.open(target_c);
	
	assert(fs.is_open() && "文件打开失败");

	fs.getline(tem,1000);
	
	for(int i = 0; !fs.eof(); i++){
		
		fs.getline(tem, 1000);

		
		string s1(tem);  //先将第一行存在 s1（string）类型中 
		
		int t1 = s1.find_first_of(",",1);
		commoditys[i].g_id=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_name=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_price=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_sum=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_descr=s1.substr(0,t1);
		s1.erase(0,t1+1);
	
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].seller_id=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_time = s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		commoditys[i].g_state=s1.substr(0,t1);
		s1.erase(0,t1+1);
		

		num_commodity++;
	}
	
} 

void writecommodity() {
	ofstream fs;

	fs.open(target_c);
	assert(fs.is_open() && "文件打开失败");
	fs << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态" << endl;
	
	for (int i = 0; i < num_commodity  ; i++) {

		fs << commoditys[i].g_id << ",";
		fs << commoditys[i].g_name << ",";
		fs << commoditys[i].g_price << ",";
		fs << commoditys[i].g_sum << ",";
		fs << commoditys[i].g_descr << ",";
		fs << commoditys[i].seller_id << ",";
		fs << commoditys[i].g_time << ",";
		fs << commoditys[i].g_state;
		if (i < num_commodity - 1)
			fs << endl;
		
	}
	fs.close();
}

void Goods_search() {
	cout << "请输入商品名称：";
	char g_name[10];
	cin >> g_name;
	

	string sea(g_name);
	string sq = "SELECT * FROM commodity WHERE 名称 CONTAINS " + sea;
	SQL(sq);
	/*
	print_baiotou_g();
	for (int i = 0; i < num_commodity; i++) {
		if (commoditys[i].g_name.find(g_name) != -1)
			PrintCommodity(i);
	}
	cout << endl << "**********************************************************************************" << endl;
	*/
}
