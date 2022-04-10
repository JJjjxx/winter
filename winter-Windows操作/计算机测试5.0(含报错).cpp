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
int count_xsd = 0; //С����λ���� 
bool xsd = false ; //�ж��Ƿ���С���㣻 

int kuohao_place[20]={0};  //��������symbol��ŵ�λ�ã�����������԰����������ŵ���� 

int count_kuohao = 0;  //���������ŵ�����
 
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
			{cout<<"��������"; 
		wrong = true; break;
		
		}
		else if(is_operator(str[i])&&is_operator(str[i+1]))
			{cout<<"����������";
		wrong = true; break;
		}
		if (is_operator(str[i]) && (!is_num(str[i+1])) &&str[i+1] !='('      )
			{cout<<"����������";
		wrong = true; break;
		}
		if(is_operator(str[i])&&(str[i+1] == '\n'||str[i+1]==')')){
			cout<<"����������";
			wrong = true; break;
		}
		if(str[i]=='(')
			zuo++;
		if(str[i]==')')
			you++;
		if(str[i]=='('&&str[i+1]==')'){
			cout<<"������������";
			wrong = true; break;
		}
		
	}
	if (zuo!= you)
		{cout<<"Բ���Ų�ƥ��";
	wrong = true;
	}
	return true;
}  
  
void kuohao_off(char* str,char* str1){
	int j = 0;
	for(int i = 0; i < strlen(str); i++){
		if (!is_num(str[i]) && str[i] != ' '&& str[i] != '('&&str[i] != ')'&&str[i] != '+'&&str[i] != '-'&&str[i] != '*'&&str[i] != '/') {
			cout << "�Ƿ�����" << endl;
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
				cout<<"����Ϊ��";
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
			break;  //��ʱӦ����ֹѭ���� ��Ȼ ����������������� 
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
		 
		if(is_num(str[i])){ //ɨ�赽����������� 	
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

		else if(str[i]=='.' )  //ɨ�赽��������� 
			{  if(xsd == true){
				cout<<"С��������";
				wrong = true;
		
		}
				xsd = true ;
				count_xsd--;
				continue;	}
		
		else if(str[i]=='(')  //ɨ�赽������������� 
			{  
				count_kuohao++; //���ż�����+1 
				kuohao_place[count_kuohao] = count_symbol;
				symbol[count_symbol] = '(';
				count_symbol++; 
				continue;}
		
		
			
		else if(count_kuohao == 0)  //�����û������������� 
			{
			
			if (str[i]=='+'||str[i]=='-')  //ɨ�赽+ - ������� 
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
		
		
		
		else if(count_kuohao != 0) //�������������������� 
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
				else if (str[i]=='+'||str[i]=='-')  //ɨ�赽+ - ������� 
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
				else if (str[i]=='*'||str[i]=='/')  //ɨ�赽* / ������� 
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
		printf("%.1lf\n",num[0]);  //����һλС���� 

}

//����� 4.0�汾


bool ca(){

	num[20] = { 0 };
	symbol[20] = { '\n' };
	wrong = false;
	math = 0;
	count_num = 0;
	count_symbol = 0;
	count_xsd = 0; //С����λ���� 
	xsd = false; //�ж��Ƿ���С���㣻 

	kuohao_place[20] = { 0 };  //��������symbol��ŵ�λ�ã�����������԰����������ŵ���� 

	count_kuohao = 0;  //���������ŵ�����

	not_kuo = true;





	wrong = false;
	cout << "��ӭ���Լ��������ܣ���\n ע������֮��Ŀո��Ĭ�����������ˣ�����1  2��Ĭ��Ϊ12\n";
	cout << "��������Ҫ�����ʽ�ӣ�" << endl;

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



