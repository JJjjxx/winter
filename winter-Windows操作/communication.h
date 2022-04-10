#pragma once
#include<string>

using namespace std;

typedef struct {

	string u_id;  //用户 id 
	string u_name;  //用户名
	string c_time;  //发表时间
	string c_content;  //发表内容

} communication;

extern int num_commodity;

void PrintCommunication(int x);

void print_baiotou_co();

void PrintCommunications();

void ReadCommunication();

void writeCommunication();

extern int num_communication;

extern communication communications[100];