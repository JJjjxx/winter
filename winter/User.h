#ifndef USER
#define USER
#include<string>
using namespace std;



typedef struct{

	string uid ; //用户id
	string u_name ; //用户名
	string u_code ; //用户密码
	string u_phone ; //用户电话号码
	string u_address ; //用户地址
	string credit_money; //余额
	string u_state ; //用户存在状态
	
}User;


class users{
	
	public:

		//下划线的功能已在别的模块中实现，没有固定作为users的类成员函数

		void User_login(User u, int x);

		void info_menu();
		//void Search_good(); //查找商品
		
		void Check_info(); //查看信息 
		bool Modify_info( int x ); //修改信息
		bool Modify_money(int x);  //充钱
		//bool Modify_name(); //改名
		//void Modify_phone(User& person); //修改联系方式
		//void Modify_address(User& person); //修改地址
		//void Modify_code(User& person);//修改密码
		string uid; //用户id
		friend void communicate(int x); //用户聊天室
	protected:
		
		string u_name; //用户名
		string u_code; //用户密码
		string u_phone; //用户电话号码
		string u_address; //用户地址
		string credit_money; //余额
		bool u_state = true; //用户存在状态
		int u_index;

};

void ReadUser();   //读取用户信息
void PrintUsers();
void PrintUser(int x);

void writeuser();  //将用户信息写入文件

extern User Users[50];
//static read_line lin[50] ;

extern int num_User;

extern int index_user;


void user_menu();

void printbiaotou_u();

extern char target_u[100];

string getTime(); //获取时间

bool user_mode(); //用户登录

void Self_manage_mode(int x); //个人信息管理

void communicate(int x);

#endif
