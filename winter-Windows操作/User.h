#pragma once
#include<string>
using namespace std;



typedef struct{

	string uid ; //�û�id
	string u_name ; //�û���
	string u_code ; //�û�����
	string u_phone ; //�û��绰����
	string u_address ; //�û���ַ
	string credit_money; //���
	string u_state ; //�û�����״̬
	
}User;


class users{
	
	public:

		//�»��ߵĹ������ڱ��ģ����ʵ�֣�û�й̶���Ϊusers�����Ա����

		void User_login(User u, int x);

		void info_menu();
		//void Search_good(); //������Ʒ
		
		void Check_info(); //�鿴��Ϣ 
		bool Modify_info( int x ); //�޸���Ϣ
		bool Modify_money(int x);  //��Ǯ
		//bool Modify_name(); //����
		//void Modify_phone(User& person); //�޸���ϵ��ʽ
		//void Modify_address(User& person); //�޸ĵ�ַ
		//void Modify_code(User& person);//�޸�����
		string uid; //�û�id
		friend void communicate(int x); //�û�������
	protected:
		
		string u_name; //�û���
		string u_code; //�û�����
		string u_phone; //�û��绰����
		string u_address; //�û���ַ
		string credit_money; //���
		bool u_state = true; //�û�����״̬
		int u_index;

};

void ReadUser();   //��ȡ�û���Ϣ
void PrintUsers();
void PrintUser(int x);

void writeuser();  //���û���Ϣд���ļ�

extern User Users[50];
//static read_line lin[50] ;

extern int num_User;

extern int index_user;


void user_menu();

void printbiaotou_u();

extern char target_u[100];

string getTime(); //��ȡʱ��

bool user_mode(); //�û���¼

void Self_manage_mode(int x); //������Ϣ����

void communicate(int x);