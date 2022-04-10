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
int index_user = 0;  //�û�������

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
	cout << setw(8) << std::left << "�û�ID";
	cout << setw(8) << std::left << "�û���";
	cout << setw(15) << std::left << "��ϵ��ʽ";
	cout << setw(20) << std::left << "��ַ";
	cout << setw(12) << std::left << "Ǯ�����";
	cout << setw(12 )<< std::left <<"�û�״̬"<< endl;
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
	
	assert(fs.is_open() && "�ļ���ʧ��");

	fs.getline(tem2,500);
	
	for(int i = 0; !fs.eof(); i++){
			
		fs.getline(tem2,500);
		string s1(tem2);  //�Ƚ���һ�д��� s1��string�������� 
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
	cout << "��ѡ������Ҫ�Ĳ���"<<endl ;
	cout << "================================================================"<<endl;
	cout << "1.�������  2.��������  3.������Ϣ����  4.СС������  5.ע����¼"<<endl;
	cout << "================================================================" << endl;
	cout << "�������������";
}

bool user_mode() {

	bool login = false;

	while (true) {
		cout << "�������û���: ";
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
		//ѭ��ɨ�� �û����Ƿ�������ļ���

		if (without_name)
		{
			cout << "δ�ҵ��û���,�����������ע���˻�" << endl;
			return false;
		}

		cout << "����������: ";
		string u_code;
		cin >> u_code;
		int mistake_cin = 0;

		while (u_code != Users[index_user].u_code) {

			if (mistake_cin == 2) {
				cout << "������������������ƣ���½ʧ�ܣ�"<<endl;
				return false;
			}
				
			cout << "������󣡣������������룺\n";
			mistake_cin++;
			cin >> u_code;

		}

		//if (mistake_cin >=2 ) { cout << "�����������Ѵ���󣬵�½ʧ�ܣ�"; return false; }

		if (Users[index_user].u_state == "���") {

			cout << endl<<"error!��½ʧ�ܣ�" << endl;
			cout << "�����˻��ѱ�����Ա������ڽ����ӡ֮ǰ����ʱ�޷���½��" << endl<<endl;
			return false;
		}




		cout << endl << "----��½�ɹ�----" << endl;
		login = true;
		break;

	}

		while (login ==true) {

			user_menu();
			string opt_u;

			cin >> opt_u;


			if (opt_u == "1") {
				buyer_mode();  //�������ģ��
				continue;
			}

			else if (opt_u == "2") {
				seller_mode();  //�������ģ��
				continue;
			}

			else if (opt_u == "3") {
				Self_manage_mode(index_user);  //����������Ϣ����ģ��
				continue;
			}

			else if (opt_u == "4") {
				communicate(index_user);  //����������Ϣ����ģ��
				continue;
			}

			else if (opt_u == "5") {
				login = false;  //�˳���¼ģ��
				return false;
			}

			else {
				cout << "����������ȷ�Ĳ�������������"<<endl;
			}

		}
}

void users::User_login(User u, int x) {

	uid = Users[x].uid; //�û�id
	u_name = Users[x].u_name; //�û���
	u_code = Users[x].u_code; //�û�����
	u_phone = Users[x].u_phone; //�û��绰����
	u_address = Users[x].u_address; //�û���ַ
	credit_money = Users[x].credit_money; //���

	u_state = "����"; //�û�����״̬

	u_index = x;

}

void writeuser() {
		ofstream fs;

		fs.open(target_u);
		assert(fs.is_open() && "�ļ���ʧ��");
		fs << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬" << endl;
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
	time(&timep); //��ȡtime_t���͵ĵ�ǰʱ��
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&timep));//�����ں�ʱ����и�ʽ��
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
	cout << "1.�鿴��Ϣ  2.�޸���Ϣ  3.��ֵ  4.�����û�������"<<endl;
	cout << "================================================"<<endl<<endl;
	cout << "��ѡ���������";
}

void users::Check_info(){

	cout << "****************************"<<endl;
	cout << "�û�����" << u_name<<endl;
	cout << "��ϵ��ʽ��" << u_phone<<endl;
	cout << "��ַ��" << u_address<<endl;
	cout << "Ǯ����" << credit_money<<endl;
	cout << "****************************" << endl;

}

bool users::Modify_info(int x) {
	while (true) {
		cout << "��ѡ���޸ĵ�����(1.�û��� 2.��ϵ��ʽ  3.��ַ  4.����  5.ȡ���޸�): ";
		string opt;
		cin >> opt;
		if (opt == "1") {
			cout << "������Ҫ�޸ĵ��û�������ע�ⲻҪ�����ո���ţ���"<<endl;
			string m_name;
			cin >> m_name;
			Users[x].u_name = m_name;
			u_name = m_name;
			writeuser(); 
			continue;
		}
		
		else if (opt == "2") {
			cout << "������Ҫ�޸ĵ���ϵ��ʽ����ע�ⲻҪ�����ո���ţ���" << endl;
			string m_phone;
			cin >> m_phone;
			Users[x].u_phone = m_phone;
			u_phone = m_phone;
			writeuser();
			continue;

		}
		else if (opt == "3") {
			cout << "������Ҫ�޸ĵĵ�ַ����ע�ⲻҪ��������" << endl;
			string m_address;
			cin >> m_address;
			Users[x].u_address = m_address;
			u_address = m_address;
			writeuser();
			continue;
		}
		else if (opt == "4") {
			cout << "������Ҫ�޸ĵ����루��ע�ⲻҪ��������" << endl;
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
	cout << "������Ҫ��ֵ�Ľ�";
	double m_money;
	cin >> m_money;	

	double all_money = m_money + atof(Users[x].credit_money.c_str());

	string all_m = std::to_string(all_money);
	int point = all_m.find(".");
	all_m.erase(point + 2, -1);

	cout << "��ֵ�ɹ�����ǰ��"<<all_m<<endl;

	Users[x].credit_money = all_m;

	credit_money = all_m;//�ı䵱ǰ���Ա��money

	writeuser();
	return true;

}

void communicate(int x){
	users u1;
	u1.User_login(Users[index_user], index_user);
	while (true) {
		cout << endl;
		cout << "=========================================" << endl;
		cout << "1.�鿴����������  2.��������  3�˳�������" << endl;
		cout << "=========================================" << endl;
		cout << "���������ѡ�� ";
		string opt_co;
		cin >> opt_co;


		if (opt_co == "1") {
			PrintCommunications();
		continue;
		}

		else if (opt_co == "2") {
			cout << endl << "(��ע�ⲻҪ����Ӣ�Ķ��ţ������ִ�����룬�ᱻ�滻�ɿո����";
			cout << endl << "�������������ݣ�";

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
			cout << "���ͳɹ�!!" << endl;
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