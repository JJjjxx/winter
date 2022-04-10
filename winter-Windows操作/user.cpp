#include<iostream>
#include<string.h>
#include <iomanip>
#include <fstream> 
#include <cassert>

#include"User.h"
#include"Buyer.h"
#include"Seller.h"
#include"commodity.h"
#include"communication.h"
#include"sql.h"

using namespace std;

char tem2[500];
User Users[50];
//static read_line lin[50] ;

int num_User = 0;
int index_user = 0;  //用户索引；

char target_u[100] = "C:\\Users\\LJX\\Desktop\\winter project\\user.txt";

void PrintUser(int x) {
	
	cout<<setw(8)<<std::left<<Users[x].uid; 
	cout<<setw(8)<<std::left<<Users[x].u_name;
	cout<<setw(15)<<std::left<<Users[x].u_phone;
	cout<<setw(20)<<std::left<<Users[x].u_address;
	cout<<setw(12)<<std::left<<Users[x].credit_money;
	cout<<setw(12)<<std::left<<Users[x].u_state<< endl;
	
}
 
void printbiaotou_u() {
	cout << "*******************************************************************************" << endl;
	cout << setw(8) << std::left << "用户ID";
	cout << setw(8) << std::left << "用户名";
	cout << setw(15) << std::left << "联系方式";
	cout << setw(20) << std::left << "地址";
	cout << setw(12) << std::left << "钱包余额";
	cout << setw(12 )<< std::left <<"用户状态"<< endl;
}
   
void PrintUsers() {

	printbiaotou_u();
	
	for (int i = 0; i < num_User; i++) {
		PrintUser(i);
	}
	cout << "*******************************************************************************" << endl;

}

void ReadUser(){

	ifstream fs;
	
	fs.open(target_u);
	
	assert(fs.is_open() && "文件打开失败");

	fs.getline(tem2,500);
	
	for(int i = 0; !fs.eof(); i++){
			
		fs.getline(tem2,500);
		string s1(tem2);  //先将第一行存在 s1（string）类型中 
		//cout<<s1<<endl;
		//cout<<s1<<endl;
		int t1 = s1.find_first_of(",",1);
		Users[i].uid=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		Users[i].u_name=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		Users[i].u_code=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		Users[i].u_phone=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",",1);
		Users[i].u_address=s1.substr(0,t1);
		s1.erase(0,t1+1);
	
		t1 = s1.find_first_of(",",1);
		Users[i].credit_money=s1.substr(0,t1);
		s1.erase(0,t1+1);
		
		t1 = s1.find_first_of(",", 1);
		Users[i].u_state = s1.substr(0, t1);
		s1.erase(0, t1 + 1);
		
		num_User++;

	}
} 

void user_menu() {
	cout << "请选择你需要的操作"<<endl ;
	cout << "================================================================"<<endl;
	cout << "1.我是买家  2.我是卖家  3.个人信息管理  4.小小聊天室  5.注销登录"<<endl;
	cout << "================================================================" << endl;
	cout << "请输入操作数：";
}

bool user_mode() {

	bool login = false;

	while (true) {
		cout << "请输入用户名: ";
		string u_name;
		cin >> u_name;

		bool without_name = false;
		index_user = 0;

		for (; index_user < num_User; index_user++) {
			if (u_name == Users[index_user].u_name)
				break;
			else if (index_user == num_User - 1)
			{
				without_name = true;  break;
			}
		}
		//循环扫描 用户名是否存在于文件中

		if (without_name)
		{
			cout << "未找到用户名,请重新输入或注册账户" << endl;
			return false;
		}

		cout << "请输入密码: ";
		string u_code;
		cin >> u_code;
		int mistake_cin = 0;

		while (u_code != Users[index_user].u_code) {

			if (mistake_cin == 2) {
				cout << "密码错误次数达最大限制，登陆失败！"<<endl;
				return false;
			}
				
			cout << "密码错误！！！请重新输入：\n";
			mistake_cin++;
			cin >> u_code;

		}

		//if (mistake_cin >=2 ) { cout << "密码错误次数已达最大，登陆失败！"; return false; }

		if (Users[index_user].u_state == "封禁") {

			cout << endl<<"error!登陆失败！" << endl;
			cout << "您的账户已被管理员封禁！在解除封印之前！暂时无法登陆！" << endl<<endl;
			return false;
		}




		cout << endl << "----登陆成功----" << endl;
		login = true;
		break;

	}

		while (login ==true) {

			user_menu();
			string opt_u;

			cin >> opt_u;


			if (opt_u == "1") {
				buyer_mode();  //进入买家模块
				continue;
			}

			else if (opt_u == "2") {
				seller_mode();  //进入买家模块
				continue;
			}

			else if (opt_u == "3") {
				Self_manage_mode(index_user);  //进入自我信息管理模块
				continue;
			}

			else if (opt_u == "4") {
				communicate(index_user);  //进入自我信息管理模块
				continue;
			}

			else if (opt_u == "5") {
				login = false;  //退出登录模块
				return false;
			}

			else {
				cout << "请您输入正确的操作数！！！！"<<endl;
			}

		}
}

void users::User_login(User u, int x) {

	uid = Users[x].uid; //用户id
	u_name = Users[x].u_name; //用户名
	u_code = Users[x].u_code; //用户密码
	u_phone = Users[x].u_phone; //用户电话号码
	u_address = Users[x].u_address; //用户地址
	credit_money = Users[x].credit_money; //余额

	u_state = "正常"; //用户存在状态

	u_index = x;

}

void writeuser() {
		ofstream fs;

		fs.open(target_u);
		assert(fs.is_open() && "文件打开失败");
		fs << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态" << endl;
		for (int i = 0; i < num_User; i++) {

				fs << Users[i].uid <<",";
				fs << Users[i].u_name << ",";
				fs << Users[i].u_code << ",";  
				fs << Users[i].u_phone << ",";
				fs << Users[i].u_address << ",";
				fs << Users[i].credit_money << ",";
				fs << Users[i].u_state;
				if (i < num_User  - 1)
					fs << endl;
		}
		fs.close();
}

string getTime()
{
	time_t timep;
	time(&timep); //获取time_t类型的当前时间
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&timep));//对日期和时间进行格式化
	return tmp;
}

void Self_manage_mode(int x) {
	users u1;
	u1.User_login(Users[index_user], index_user);
	
	
	while (true) {

		u1.info_menu();
		string opt_u;
		cin >> opt_u;

		if (opt_u == "1") {
			u1.Check_info();
			continue;
		}

		else if (opt_u == "2") {
			u1.Modify_info(index_user);
			continue;
		}

		else if (opt_u == "3") {
			u1.Modify_money(index_user);
			continue;
		}
		else if (opt_u == "4")
			break;
		else continue;
	}
}

void users::info_menu() {
	cout << "================================================"<<endl;
	cout << "1.查看信息  2.修改信息  3.充值  4.返回用户主界面"<<endl;
	cout << "================================================"<<endl<<endl;
	cout << "请选择操作数：";
}

void users::Check_info(){

	cout << "****************************"<<endl;
	cout << "用户名：" << u_name<<endl;
	cout << "联系方式：" << u_phone<<endl;
	cout << "地址：" << u_address<<endl;
	cout << "钱包余额：" << credit_money<<endl;
	cout << "****************************" << endl;

}

bool users::Modify_info(int x) {
	while (true) {
		cout << "请选择修改的属性(1.用户名 2.联系方式  3.地址  4.密码  5.取消修改): ";
		string opt;
		cin >> opt;
		if (opt == "1") {
			cout << "请输入要修改的用户名（请注意不要包含空格符号）："<<endl;
			string m_name;
			cin >> m_name;
			Users[x].u_name = m_name;
			u_name = m_name;
			writeuser(); 
			continue;
		}
		
		else if (opt == "2") {
			cout << "请输入要修改的联系方式（请注意不要包含空格符号）：" << endl;
			string m_phone;
			cin >> m_phone;
			Users[x].u_phone = m_phone;
			u_phone = m_phone;
			writeuser();
			continue;

		}
		else if (opt == "3") {
			cout << "请输入要修改的地址（请注意不要过长）：" << endl;
			string m_address;
			cin >> m_address;
			Users[x].u_address = m_address;
			u_address = m_address;
			writeuser();
			continue;
		}
		else if (opt == "4") {
			cout << "请输入要修改的密码（请注意不要过长）：" << endl;
			string m_code;
			cin >> m_code;
			Users[x].u_code = m_code;
			u_code = m_code;
			writeuser();
			continue;
		}
		else if (opt == "5") {
			return false;

		}
		return false;
	}

}

bool users::Modify_money(int x) {
	cout << "请输入要充值的金额：";
	double m_money;
	cin >> m_money;	

	double all_money = m_money + atof(Users[x].credit_money.c_str());

	string all_m = std::to_string(all_money);
	int point = all_m.find(".");
	all_m.erase(point + 2, -1);

	cout << "充值成功！当前余额："<<all_m<<endl;

	Users[x].credit_money = all_m;

	credit_money = all_m;//改变当前类成员的money

	writeuser();
	return true;

}

void communicate(int x){
	users u1;
	u1.User_login(Users[index_user], index_user);
	while (true) {
		cout << endl;
		cout << "=========================================" << endl;
		cout << "1.查看聊天室内容  2.发起聊天  3退出聊天室" << endl;
		cout << "=========================================" << endl;
		cout << "请输入你的选择： ";
		string opt_co;
		cin >> opt_co;


		if (opt_co == "1") {
			PrintCommunications();
		continue;
		}

		else if (opt_co == "2") {
			cout << endl << "(请注意不要输入英文逗号，如果你执意输入，会被替换成空格符）";
			cout << endl << "请输入聊天内容：";

			string co_content;
			getchar();
			getline(cin,co_content);

			string kg = " ";
			while (co_content.find(',') != -1) {
				int dex = co_content.find(',');
				co_content.replace(dex, 1, kg);
			}

			communications[num_communication].c_time=getTime();
			communications[num_communication].u_name = u1.u_name;
			communications[num_communication].u_id = u1.uid;
			communications[num_communication].c_content = co_content;
			num_communication++;
			cout << "发送成功!!" << endl;
			PrintCommunications();

			writeCommunication();
			continue;
		}
		else if(opt_co == "3") {

			break;
		}
		else continue;

	}
}