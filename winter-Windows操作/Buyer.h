#pragma once
#include"User.h"

class buyer : public users
{
public:
	void Buyer_manu(); //买家功能菜单 
	bool Buying();  //购买商品 
	//void DeSelling(User& person);  //下架商品 
	//void Modify_Good(User& person);  //修改商品信息 
	bool Buyer_Check_Goods(); //查看已发布商品
	void Buyer_Check_Order(); //查看交易成功订单 

};

void buyer_mode();  //买家板块
