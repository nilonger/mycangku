#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int x,y,z,k,konghang;//x字符数 ; y词数 ；z行数 ; k 注释行数 

int m;      //不是空文件时  m=1
 
//字符数 
void CountC(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)  //不要 放在主函数里面 
	{
		printf("打不开文件\n"); 
		exit(0);
	}
	
	char ch;
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(ch>='!'&&ch<='~')  //ASCII  从33到126 
		x++;
		ch=fgetc(fp);
		
	}
	if(x==0)m=0;      //m=0  则为  空文件 
	fclose(fp);
}

//词数
void CountW(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("打不开文件\n"); 
		exit(0);
	}
	
	char ch;
	int flag=0;       //用于判断是否要 +1 ,flag要先置为0 
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')){  //如果是非字母字符，让flag为0 ||ch=='.'||ch=='_'
            flag = 0;
        }
		else if((flag ==0)&&(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))      //如果是字母字符且flag原值为0，flag置1，单词数加一
		{  
            flag = 1; 
            y++;
        }
        ch=fgetc(fp);
	}
//	y--;            //单独测试  的时候要加上  ,不知道为什么要 -1 
	if(m==0) y=0;
	fclose(fp);
} 

//行数 
int CountL(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("打不开文件\n"); 
		exit(0);
	}
	
	char ch;
	ch=fgetc(fp);
	z++;            //  单独测试   的时候要去掉 
	while(ch!=EOF)
	{
		if(ch=='\n')
		z++;
		ch=fgetc(fp);
	}
	if(m==0) z=0;      //不能z--   空文件运行会出错 
	fclose(fp);
	return(z);
}


void CountA(char fname[]){
	FILE* fp=NULL;
	 if((fp=fopen(fname,"r"))==NULL)
	{
		printf("打不开文件\n"); 
		exit(0);
	}
	
//注释行 	
	char ch; 
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(ch=='/')
		{
			ch=fgetc(fp);
			if(ch=='/')
			{
			    k++;   //注释行  +1 
			    ch=fgetc(fp);          //获得新的字符，并重新开始循环 
			    continue;
			}  
			else if(ch=='*')
			{	
				ch=fgetc(fp);
				
				while(ch!=EOF)
				{	
					if(ch=='\n')	k++;    //多行注释的 每个回车都要 +1
					if(ch=='*')
					ch=fgetc(fp);
					if(ch=='/') 
					{
					    k++;		//多行注释完整，行数+1，并跳出第二层循环 
						break; 
					}    
					ch=fgetc(fp);
					
				}
				
			}
			
		}
		ch=fgetc(fp);
	}
	printf("注释行：%d\n",k);
	rewind(fp);             //指回文件开头 


//空行 
	int flag=0;
	int num=0;      //两个换行符之间的字符数 
	konghang=0;
	
	ch=fgetc(fp);
	while(ch!=EOF){
		if(ch=='\n'&&num==0)    //第一个换行符 
		{
			flag=1;
			konghang++;
		}	
			
		else if(ch!='\n'&&flag==1)
			num++;                 

		else if(ch!='\n'&&flag==0&&num==0)  //第一行 是代码行 的情况 
			{
				num++;
				flag=1;
			}
		else if(ch=='\n'&&flag==1&&num>=0){  //代码行到最后，把累加的字符数  归0 
			num=0;
			flag=0; 
		}	
		
		ch=fgetc(fp);	
	} 	
	printf("空行数：%d\n",konghang);
	rewind(fp);
	
//代码行	
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
	daimahang++;      //最后一行没有'\n',自动  +1 
	if(m==0) daimahang=0;
	printf("代码行数：%d\n",daimahang);
	fclose(fp);
	 
} 


int main(){
  
  char fu[5];
  char fname[50];
  while(1){
  	m=1; //不是空文件是  m=1
  	
  	x=y=z=k=konghang=0;
  	printf("输入文件名：");
    scanf("%s",fname);
  
     CountC(fname) ;
	printf("字符数为：%d\n",x);
       
    CountW(fname);
   	printf("单词数为：%d\n",y);  
		 
	CountL(fname);
 	printf("行数：%d\n",z);
 	
 	CountA(fname);
 	
  }
  
	 	   
/* printf("-c:统计字符数\n -w:统计单词数\n -l:统计行数\n -9:退出\n");
  
  while(1)
  { x=0;y=1;z=1;k=0;     //行数先设置为  1 
    printf("请输入你的操作c/w/l/a/9:");
    scanf("%s",fu);
    
  	if(fu[0]=='c')
     {
	   CountC(fname) ;
       printf("字符数为：%d\n",x); 
     }
     
     if(fu[0]=='w')
	 {
	 	CountW(fname);
     	printf("单词数为：%d\n",y);	
	 }
	 
	 if(fu[0]=='l')
	 {
	 	CountL(fname);
	 	printf("行数：%d\n",z);
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
