#pragma once
#include<string>

using namespace std;

typedef struct {

	string g_id;  //��Ʒ id 
	string g_name;  //��Ʒ���� 
	string g_price; //��Ʒ�۸� 
	string g_sum; //���� 
	string g_descr; //��Ʒ����
	string seller_id;  //����id 
	string g_time;  //��Ʒ�ϼ�ʱ�� 
	string g_state;  //��Ʒ״̬ 

} commodity;

void PrintCommodity(int x);

void PrintCommoditys(); //��ӡ������Ʒ

void ReadCommodity(); //���ļ�

void writecommodity();  //д�ļ�

extern char tem[1000];
extern commodity commoditys[50];

//static read_line lin[50] ;

extern int num_commodity ;

void print_baiotou_g();

extern char target_c[100];

void Goods_search(); //������Ʒ