#ifndef ADMINISTRATOR_MODE
#define ADMINISTRATOR_MODE


class Administrator
{
	public:
		Administrator();
		void Boss_login (); //登陆 
		void Boss_manu();  //显示主菜单 
		//void Users_search() ; //查找用户 
		bool Good_del();  //下架商品 
		bool User_del();   //封锁用户 
		void All_Users() const;   //查看所有用户 
		void All_Goods() const;    //查看所有商品 
		void All_orders() const;   //查看所有订单 
		bool ad_state;
		void PrintU(int x)const;
		bool User_deblock(); //解封用户

	private:
		const char boss_name[6] = "admin";   //管理员姓名 
		const char boss_code[8] = "1234567";  //管理员密码 
		
};

void administrator_mode(); 

 
#endif
