#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int x,y,z,k,konghang;//x�ַ��� ; y���� ��z���� ; k ע������ 

int m;      //���ǿ��ļ�ʱ  m=1
 
//�ַ��� 
void CountC(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)  //��Ҫ �������������� 
	{
		printf("�򲻿��ļ�\n"); 
		exit(0);
	}
	
	char ch;
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(ch>='!'&&ch<='~')  //ASCII  ��33��126 
		x++;
		ch=fgetc(fp);
		
	}
	if(x==0)m=0;      //m=0  ��Ϊ  ���ļ� 
	fclose(fp);
}

//����
void CountW(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("�򲻿��ļ�\n"); 
		exit(0);
	}
	
	char ch;
	int flag=0;       //�����ж��Ƿ�Ҫ +1 ,flagҪ����Ϊ0 
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')){  //����Ƿ���ĸ�ַ�����flagΪ0 ||ch=='.'||ch=='_'
            flag = 0;
        }
		else if((flag ==0)&&(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))      //�������ĸ�ַ���flagԭֵΪ0��flag��1����������һ
		{  
            flag = 1; 
            y++;
        }
        ch=fgetc(fp);
	}
//	y--;            //��������  ��ʱ��Ҫ����  ,��֪��ΪʲôҪ -1 
	if(m==0) y=0;
	fclose(fp);
} 

//���� 
int CountL(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("�򲻿��ļ�\n"); 
		exit(0);
	}
	
	char ch;
	ch=fgetc(fp);
	z++;            //  ��������   ��ʱ��Ҫȥ�� 
	while(ch!=EOF)
	{
		if(ch=='\n')
		z++;
		ch=fgetc(fp);
	}
	if(m==0) z=0;      //����z--   ���ļ����л���� 
	fclose(fp);
	return(z);
}


void CountA(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("�򲻿��ļ�\n"); 
		exit(0);
	}
	
//ע���� 	
	char ch; 
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(ch=='/')
		{
			ch=fgetc(fp);
			if(ch=='/')
			{
			    k++;   //ע����  +1 
			    ch=fgetc(fp);          //����µ��ַ��������¿�ʼѭ�� 
			    continue;
			}  
			else if(ch=='*')
			{	
				ch=fgetc(fp);
				
				while(ch!=EOF)
				{	
					if(ch=='\n')	k++;    //����ע�͵� ÿ���س���Ҫ +1
					if(ch=='*')
					ch=fgetc(fp);
					if(ch=='/') 
					{
					    k++;		//����ע������������+1���������ڶ���ѭ�� 
						break; 
					}    
					ch=fgetc(fp);
					
				}
				
			}
			
		}
		ch=fgetc(fp);
	}
	printf("ע���У�%d\n",k);
	rewind(fp);             //ָ���ļ���ͷ 


//���� 
	int flag=0;
	int num=0;      //�������з�֮����ַ��� 
	konghang=0;
	
	ch=fgetc(fp);
	while(ch!=EOF){
		if(ch=='\n'&&num==0)    //��һ�����з� 
		{
			flag=1;
			konghang++;
		}	
			
		else if(ch!='\n'&&flag==1)
			num++;                 

		else if(ch!='\n'&&flag==0&&num==0)  //��һ�� �Ǵ����� ����� 
			{
				num++;
				flag=1;
			}
		else if(ch=='\n'&&flag==1&&num>=0){  //�����е���󣬰��ۼӵ��ַ���  ��0 
			num=0;
			flag=0; 
		}	
		
		ch=fgetc(fp);	
	} 	
	printf("��������%d\n",konghang);
	rewind(fp);
	
//������	
	int num1=0,daimahang=0,flag1=1;;
	ch=fgetc(fp);
	while(ch!=EOF){
		 
		if((ch!=' '&&ch!='\n'&&ch!='\t'&&ch!='/'))
			{
				num1++;	
			}
		else if(ch=='\n'&&num1>=1&&flag1==1)
		{	
			daimahang++;
			num1=0;		
		}
		else if(ch=='/')
		{
			ch=fgetc(fp);
			if(ch=='/') 
			{
				ch=fgetc(fp);
				while(ch!=EOF){
					if(ch=='\n')	break;
					ch=fgetc(fp);
				}
			}		
			else if(ch=='*')
			{
				ch=fgetc(fp);
				while(ch!=EOF){
					if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')num1++;
					if(ch=='\n')num1=0;
					 if(ch=='*')
					{
						ch=fgetc(fp);
						if(ch=='/')	break;
					}
					ch=fgetc(fp);
				}
			}		
		}
			
		ch=fgetc(fp);
	} 
	daimahang++;      //���һ��û��'\n',�Զ�  +1 
	if(m==0) daimahang=0;
	printf("����������%d\n",daimahang);
	fclose(fp);
	 
} 


int main(){
  
  char fu[5];
  char fname[50];
  while(1){
  	m=1; //���ǿ��ļ���  m=1
  	
  	x=y=z=k=konghang=0;
  	printf("�����ļ�����");
    scanf("%s",fname);
  
     CountC(fname) ;
	printf("�ַ���Ϊ��%d\n",x);
       
    CountW(fname);
   	printf("������Ϊ��%d\n",y);  
		 
	CountL(fname);
 	printf("������%d\n",z);
 	
 	CountA(fname);
 	
  }
  
	 	   
/* printf("-c:ͳ���ַ���\n -w:ͳ�Ƶ�����\n -l:ͳ������\n -9:�˳�\n");
  
  while(1)
  { x=0;y=1;z=1;k=0;     //����������Ϊ  1 
    printf("��������Ĳ���c/w/l/a/9:");
    scanf("%s",fu);
    
  	if(fu[0]=='c')
     {
	   CountC(fname) ;
       printf("�ַ���Ϊ��%d\n",x); 
     }
     
     if(fu[0]=='w')
	 {
	 	CountW(fname);
     	printf("������Ϊ��%d\n",y);	
	 }
	 
	 if(fu[0]=='l')
	 {
	 	CountL(fname);
	 	printf("������%d\n",z);
	 }
	 
	 if(fu[0]=='a')
	 {
	 	CountA(fname);	
	 }
	 
	 if(fu[0]=='9')
	 break;
  }
*/
 
 return 0;

}
