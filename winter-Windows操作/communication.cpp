#include"communication.h"
#include"commodity.h"
#include<iostream>

#include<cstdio> 
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream> 
#include<cassert>
using namespace std;


communication communications[100];

char tem_co[1000];

int num_communication = 0;

char target_co[100] = "C:\\Users\\LJX\\Desktop\\winter project\\communication.txt";

void PrintCommunication(int x) {

	cout << communications[x].c_time<<" ";
	cout << communications[x].u_id<<" ";
	cout << communications[x].u_name;
	
	cout <<" :"<< communications[x].c_content<<endl;

}

void print_baiotou_co() {
	cout << endl << "***********************************************************************************************" << endl;
	cout << endl << "欢迎来到聊天室，诶嘿！" << endl;

}

void PrintCommunications(){

	print_baiotou_co();
	for (int i = 0; i < num_communication; i++) {
		PrintCommunication(i);
	}
	cout << endl << endl;
}

void ReadCommunication() {

	ifstream fs;

	fs.open(target_co);

	assert(fs.is_open() && "文件打开失败");

	fs.getline(tem_co, 1000);

	for (int i = 0; !fs.eof(); i++) {

		fs.getline(tem_co, 1000);


		string s1(tem_co);  //先将第一行存在 s1（string）类型中 

		int t1 = s1.find_first_of(",", 1);
		communications[i].u_id = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		communications[i].u_name = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		communications[i].c_time = s1.substr(0, t1);
		s1.erase(0, t1 + 1);

		t1 = s1.find_first_of(",", 1);
		communications[i].c_content = s1.substr(0, t1);
		s1.erase(0, t1 + 1);



		num_communication++;
	}

}

void writeCommunication() {
	ofstream fs;

	fs.open(target_co);
	assert(fs.is_open() && "文件打开失败");
	fs << "用户id,用户名,时间,聊天内容" << endl;

	for (int i = 0; i < num_communication; i++) {

		fs << communications[i].u_id << ",";
		fs << communications[i].u_name << ",";
		fs << communications[i].c_time << ",";
		fs << communications[i].c_content;
		if (i < num_communication - 1)
			fs << endl;

	}
	fs.close();
}


