#include"User.h"

class seller: public users
{
	public:
		void Seller_manu(); //���ҹ��ܲ˵� 
		bool Selling();  //������Ʒ 
		bool DeSelling();  //�¼���Ʒ 
		bool Modify_Good();  //�޸���Ʒ��Ϣ 
		void Seller_Check_Goods(); //�鿴�ѷ�����Ʒ
		void Seller_Check_Order(); //�鿴���׳ɹ����� 

}; 



void seller_mode();