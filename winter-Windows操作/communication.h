#pragma once
#include<string>

using namespace std;

typedef struct {

	string u_id;  //�û� id 
	string u_name;  //�û���
	string c_time;  //����ʱ��
	string c_content;  //��������

} communication;

extern int num_commodity;

void PrintCommunication(int x);

void print_baiotou_co();

void PrintCommunications();

void ReadCommunication();

void writeCommunication();

extern int num_communication;

extern communication communications[100];