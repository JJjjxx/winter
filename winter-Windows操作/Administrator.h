#ifndef ADMINISTRATOR_MODE_H
#define ADMINISTRATOR_MODE_H


class Administrator
{
	public:
		Administrator();
		void Boss_login (); //��½ 
		void Boss_manu();  //��ʾ���˵� 
		//void Users_search() ; //�����û� 
		bool Good_del();  //�¼���Ʒ 
		bool User_del();   //�����û� 
		void All_Users() const;   //�鿴�����û� 
		void All_Goods() const;    //�鿴������Ʒ 
		void All_orders() const;   //�鿴���ж��� 
		bool ad_state;
		void PrintU(int x)const;
		bool User_deblock(); //����û�

	private:
		const char boss_name[6] = "admin";   //����Ա���� 
		const char boss_code[8] = "1234567";  //����Ա���� 
		
};

void administrator_mode(); 

 
#endif