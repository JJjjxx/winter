#pragma once
#include<string>

using namespace std;

typedef struct {

	string g_id;  //商品 id 
	string g_name;  //商品名称 
	string g_price; //商品价格 
	string g_sum; //数量 
	string g_descr; //商品描述
	string seller_id;  //卖家id 
	string g_time;  //商品上架时间 
	string g_state;  //商品状态 

} commodity;

void PrintCommodity(int x);

void PrintCommoditys(); //打印所有商品

void ReadCommodity(); //读文件

void writecommodity();  //写文件

extern char tem[1000];
extern commodity commoditys[50];

//static read_line lin[50] ;

extern int num_commodity ;

void print_baiotou_g();

extern char target_c[100];

void Goods_search(); //搜索商品