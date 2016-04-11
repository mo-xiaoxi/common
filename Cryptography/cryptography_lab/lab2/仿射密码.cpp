#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int gcd(int m,int n);//判断m与N是否互质 
void transform(char str[]);//将大写字母统一转换成小写 
void encrypt(char str[]);
void decrypt(char str[]); 
int n;		//输入字符数 
int a,b;		//密钥 
int x[500],y[500];		//将字母转变成数字后的数字数组 
char str[500],strout[500];		//输入和输出的字符串 
	
int main()
{
	int f;
	cout<<"请输入秘钥（a，b）:"<<endl;
	cin>>a>>b;
	if(gcd(a,26)!=1)
		cout<<"输入的密钥不合法，请重新输入"<<endl;
	else
	{
		cout<<"选择加密（0）或者解密（1）："<<endl;
		cin>>f;
		if(f==0)
		{
			cout<<"请输入明文："<<endl;
			cin>>str;
			n=strlen(str);
			transform(str);
			cout<<"密文为："<<endl; 
			encrypt(str);
		}
		else
		{
			cout<<"请输入密文："<<endl;
			cin>>str;
			n=strlen(str);
			transform(str);
			cout<<"明文为："<<endl; 		
			decrypt(str);
		}	
	}
	return 0; 
} 

int gcd(int m,int n)	//判断a与26是否互素 
{
	if(n<m)				//确保n>m 
	{
		int temp=n;
		n=m;
		m=temp;
	}
	while(m!=0)			//返回n=1时两者互素 
	{
		int y=n%m;
		n=m;
		m=y;
	}
	return n;
}

void transform(char str[])	//将大写字母统一转换成小写 
{
	for(int i=0;i<n;i++)
	{
		if(str[i]>=65&&str[i]<=90)
			str[i]=str[i]+32;
	}
}

void encrypt(char str[])		//加密 
{

	for(int i=0;i<n;i++)
	{
		str[i]=str[i]-'a';
		y[i]=(a*str[i]+b)%26;
		strout[i]=y[i]+'a';
		cout<<strout[i];
	}	
} 

void decrypt(char str[])		//解密 
{
	int c;		//a的逆元 
	for(int i=1;i<26;i++)		//计算a的逆元 
	{
		if((i*a)%26==1)
		{
			c=i;
			break;
		}
	}
	for(int i=0;i<n;i++)
	{
		str[i]=str[i]-'a';
		if(str[i]>b)			//y-b小于0时要加26 
			x[i]=(c*(str[i]-b))%26;
		else
			x[i]=(c*(str[i]-b+26))%26;
		strout[i]=x[i]+'a';
		cout<<strout[i];
	} 
} 


