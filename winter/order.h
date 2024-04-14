#ifndef _ORDER_H_
#define _ORDER_H_

#include<string>

using namespace std;

typedef struct {
	string o_id;  //订单id 
	string good_id;  //商品id 
	string o_price;  //交易单价 
	string o_sum;  //交易数量 
	string o_time;  //交易时间 
	string seller_id;  //卖家id 
	string buyer_id; 	//买家id 
} Order;


typedef struct {
	char line[50];
	string h1;
} read_line;


void ReadOrders();    //从文件读入订单信息

void writeorder();   //把订单信息写至文件


//int addOrder(Order* o);   //向订单中加入新的订单

void PrintOrders();   //打印所有订单，即管理员打印订单

void PrintOrder(int x);

void printOrders4Seller(const char* id);   //用于卖家打印订单

 
void printOrders4Buyer(const char* id);    //用于买家打印订单

void print_biaotou_o(); //打印订单表头

extern int num_order ;
extern Order orders[20];
#endif
