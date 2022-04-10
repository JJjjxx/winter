#ifndef _ORDER_H_
#define _ORDER_H_

#include<string>

using namespace std;

typedef struct {
	string o_id;  //����id 
	string good_id;  //��Ʒid 
	string o_price;  //���׵��� 
	string o_sum;  //�������� 
	string o_time;  //����ʱ�� 
	string seller_id;  //����id 
	string buyer_id; 	//���id 
} Order;


typedef struct {
	char line[50];
	string h1;
} read_line;


void ReadOrders();    //���ļ����붩����Ϣ

void writeorder();   //�Ѷ�����Ϣд���ļ�


//int addOrder(Order* o);   //�򶩵��м����µĶ���

void PrintOrders();   //��ӡ���ж�����������Ա��ӡ����

void PrintOrder(int x);

void printOrders4Seller(const char* id);   //�������Ҵ�ӡ����

 
void printOrders4Buyer(const char* id);    //������Ҵ�ӡ����

void print_biaotou_o(); //��ӡ������ͷ

extern int num_order ;
extern Order orders[20];
#endif
