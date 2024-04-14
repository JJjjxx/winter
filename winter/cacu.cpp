#include<iostream>
#include <string>
#include <string.h>
#include <math.h> 
#include"caculate2.h"
using namespace std;

double num[20];
char symbol[20]={'\n'};
bool wrong = false;
double math = 0; 
int count_num = 0;
int count_symbol = 0;
int count_xsd = 0; //小数点位数； 
bool xsd = false ; //判断是否含有小数点； 

int kuohao_place[20]={0};  //左括号在symbol存放的位置；增加数组可以包含多种括号的情况 

int count_kuohao = 0;  //遇到左括号的数量
 
bool not_kuo = true;

bool is_num(char s){
	if(s<=57 && s>=48)
		return true;
	return false;	
}

bool is_operator(char s){
	if(s=='+'|| s=='-'||s=='*'||s=='/')
		return true;
	return false;	
}

bool report_wrong(char* str){
	
	int length = strlen(str);
	int i=0;
	int zuo = 0,you = 0;	
	for(; i<length; i++){
		if(str[i]==')' &&str[i+1]=='(')
			{cout<<"括号误用"; 
		wrong = true; break;
		
		}
		else if(is_operator(str[i])&&is_operator(str[i+1]))
			{cout<<"操作符误用";
		wrong = true; break;
		}
		if (is_operator(str[i]) && (!is_num(str[i+1])) &&str[i+1] !='('      )
			{cout<<"操作符误用";
		wrong = true; break;
		}
		if(is_operator(str[i])&&(str[i+1] == '\n'||str[i+1]==')')){
			cout<<"操作符误用";
			wrong = true; break;
		}
		if(str[i]=='(')
			zuo++;
		if(str[i]==')')
			you++;
		if(str[i]=='('&&str[i+1]==')'){
			cout<<"括号内无内容";
			wrong = true; break;
		}
		
	}
	if (zuo!= you)
		{cout<<"圆括号不匹配";
	wrong = true;
	}
	return true;
}  
  
void kuohao_off(char* str,char* str1){
	int j = 0;
	for(int i = 0; i < strlen(str); i++){
		if (!is_num(str[i]) && str[i] != ' '&& str[i] != '('&&str[i] != ')'&&str[i] != '+'&&str[i] != '-'&&str[i] != '*'&&str[i] != '/') {
			cout << "非法符号" << endl;
			wrong = true; break;
		}
		if(str[i]!=' '){
			str1[j]=str[i];
			j++;
		}
		
		
	}	
	
}
  
void caculate(int kk= -1)
{	
	while(count_symbol >= kuohao_place[count_kuohao] && count_symbol!= 0 && count_symbol> kk){
		
		if(symbol[count_symbol-1]=='*'){
			num[count_num-2] = num[count_num-2]*num[count_num-1];
			
			symbol[count_symbol-1]='\n';
			count_num--;
			count_symbol--;	
			continue;
		}
		if(symbol[count_symbol-1]=='/'){
			if(num[count_num-1]==0){
				cout<<"除数为零";
				wrong = true; 
			} 
			num[count_num-2] = num[count_num-2]/num[count_num-1];
			
			symbol[count_symbol-1]='\n';
			count_num--;
			count_symbol--;	
			continue;
		}
		if(symbol[count_symbol-1]=='+'){
			
			num[count_num-2] = num[count_num-2]+num[count_num-1];
			
			symbol[count_symbol-1]='\n';
			count_num--;
			count_symbol--;	
			continue;
		}
		if(symbol[count_symbol-1]=='-'){
			num[count_num-2] = num[count_num-2]-num[count_num-1];
			symbol[count_symbol-1]='\n';		
			count_num--;
			count_symbol--;	
			continue;
		}
		if(symbol[count_symbol-1]=='('){	
			kuohao_place[count_kuohao]=0;
			symbol[count_symbol-1]='\n';
			count_kuohao --; 
			count_symbol --;	
			break;  //此时应该终止循环， 不然 程序会消除所有括号 
		}	
		if(symbol[count_symbol-1]==')'){
			symbol[count_symbol-1]='\n';
			count_symbol--;	
			continue;
		}	
	}	
}


void transform(char*str){
		
	int length = strlen(str);
	int i=0;	
	for(; i<length; i++){
		 
		if(is_num(str[i])){ //扫描到数字这种情况 	
			if (xsd)			
				{	math = math + (str[i]-48)*pow(10,count_xsd);			
					count_xsd--;	}
			else
				math = math*10 + (str[i]-48) ; 
								
			if(i == length-1) { 
				num[count_num]=math;
				math = 0;
				count_num++;
				xsd = false;
				count_xsd = 0;
				continue; 	}

			else if(str[i+1] > 57 || str[i+1] < 48 &&str[i+1]!='.') { 
				num[count_num]=math;
				math = 0;
				count_num++;
				xsd = false ;
				count_xsd = 0;
				continue; }
			else 
				continue;
		
		}

		else if(str[i]=='.' )  //扫描到点这种情况 
			{  if(xsd == true){
				cout<<"小数点误用";
				wrong = true;
		
		}
				xsd = true ;
				count_xsd--;
				continue;	}
		
		else if(str[i]=='(')  //扫描到左括号这种情况 
			{  
				count_kuohao++; //括号计数器+1 
				kuohao_place[count_kuohao] = count_symbol;
				symbol[count_symbol] = '(';
				count_symbol++; 
				continue;}
		
		
			
		else if(count_kuohao == 0)  //如果场没有括号这种情况 
			{
			
			if (str[i]=='+'||str[i]=='-')  //扫描到+ - 这种情况 
				{
					if(count_symbol == 0&&count_num !=0 ){
						
						symbol[count_symbol]=str[i];					
						count_symbol++; 
						continue;				
					}
					else if (symbol[0]=='*'||symbol[0]=='/'){
						i--;
						caculate();
						continue;
					}
					else if (symbol[0]=='+'||symbol[0]=='-'){
						i--;
						caculate();
						continue;
					}
					else if (count_num ==0){
						
						num[count_num] =0;
						count_num++;
					    symbol[count_symbol] = str[i];							
						count_symbol++; 
					    continue;
					}
								
			}
			
			else if (str[i]=='*' || str[i]=='/'){
				
					if( count_symbol == 0 ){		
						symbol[count_symbol] = str[i];					
						count_symbol++; 
						continue;				
					}
					else if (symbol[0]=='*'||symbol[0]=='/'){
						i--;
						caculate() ;
						continue;
					}
					else if (symbol[0]=='+'||symbol[0]=='-'){
						symbol[count_symbol] = str[i];
						count_symbol++; 
						continue;
					}					
			}
			
			}
		
		
		
		else if(count_kuohao != 0) //如果场上有括号那种情况 
			{
				if(str[i]==')')
				{	symbol[count_symbol] = str[i];
					count_symbol++; 
					caculate();	
					continue;
					}
				else if (symbol[count_symbol-1]=='('&& str[i-1]!= '('){
					symbol[count_symbol]=str[i];					
					count_symbol++; 
					continue;	
				}
				else if (str[i]=='+'||str[i]=='-')  //扫描到+ - 这种情况 
				{	
					if (str[i-1] == '('){
						num [count_num] = 0;
						count_num++;
					    symbol[count_symbol] = str[i];							
						count_symbol++; 
					    continue;
					}
					else if (symbol[kuohao_place[count_kuohao]+1]=='*'||symbol[kuohao_place[count_kuohao]+1]=='/'){
						i--;
						caculate(kuohao_place[count_kuohao]+1);
						continue;
					}
					else if (symbol[kuohao_place[count_kuohao]+1]=='+'||symbol[kuohao_place[count_kuohao]+1]=='-'){
						i--;
						caculate(kuohao_place[count_kuohao]+1);
						continue;
					}		
				
				}
				else if (str[i]=='*'||str[i]=='/')  //扫描到* / 这种情况 
				{
					if (symbol[kuohao_place[count_kuohao]+1]=='*'||symbol[kuohao_place[count_kuohao]+1]=='/'){
						i--;
						caculate(kuohao_place[count_kuohao]+1);
						continue;
					}
					else if (symbol[kuohao_place[count_kuohao]+1]=='+'||symbol[kuohao_place[count_kuohao]+1]=='-'){
						symbol[count_symbol]=str[i];					
						count_symbol++; 
						continue;	
					}			
				}		
		}
	}
	 
	caculate();
	
	if(!wrong)
		printf("%.1lf\n",num[0]);  //保留一位小数。 

}

//计算机 4.0版本


bool ca(){

	num[20] = { 0 };
	symbol[20] = { '\n' };
	wrong = false;
	math = 0;
	count_num = 0;
	count_symbol = 0;
	count_xsd = 0; //小数点位数； 
	xsd = false; //判断是否含有小数点； 

	kuohao_place[20] = { 0 };  //左括号在symbol存放的位置；增加数组可以包含多种括号的情况 

	count_kuohao = 0;  //遇到左括号的数量

	not_kuo = true;





	wrong = false;
	cout << "欢迎尝试计算器功能！！\n 注意数字之间的空格会默认是您按错了，比如1  2会默认为12\n";
	cout << "请输入你要计算的式子：" << endl;

	char str[100];

	getchar();
	cin.getline(str,100);

	char str1[100] ={'\n'};

	kuohao_off(str,str1);
	//cout<<str1<<endl;
	//report_wrong(str1);
	report_wrong(str1);
	if(!wrong)
		transform(str1);

	cout << endl;
	return true;
}



