#pragma once
#include"User.h"

class buyer : public users
{
public:
	void Buyer_manu(); //��ҹ��ܲ˵� 
	bool Buying();  //������Ʒ 
	//void DeSelling(User& person);  //�¼���Ʒ 
	//void Modify_Good(User& person);  //�޸���Ʒ��Ϣ 
	bool Buyer_Check_Goods(); //�鿴�ѷ�����Ʒ
	void Buyer_Check_Order(); //�鿴���׳ɹ����� 

};

void buyer_mode();  //��Ұ��
