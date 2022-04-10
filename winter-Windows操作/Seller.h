#include"User.h"

class seller: public users
{
	public:
		void Seller_manu(); //卖家功能菜单 
		bool Selling();  //发布商品 
		bool DeSelling();  //下架商品 
		bool Modify_Good();  //修改商品信息 
		void Seller_Check_Goods(); //查看已发布商品
		void Seller_Check_Order(); //查看交易成功订单 

}; 



void seller_mode();