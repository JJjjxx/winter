#ifndef SQLS
#define SQLS
#include<string>
using namespace std;

void SQL (string s);
//hehihei
void SELECT_MODE(string s); 

void UPDATE_MODE(string s);

void INSERT_INTO_MODE(string s);

void writecommand();

void readcommand();

string getTime_s();  //适合command的  gettime

bool select_commodity(string s);

bool select_user(string s);
bool select_order(string s);
void select_contain(string s);

bool update_user(string s);
bool update_commodity(string s);

bool insert_order(string s);
bool insert_commodity(string s);
#endif
