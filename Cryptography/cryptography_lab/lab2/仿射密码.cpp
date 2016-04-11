#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int gcd(int m,int n);//�ж�m��N�Ƿ��� 
void transform(char str[]);//����д��ĸͳһת����Сд 
void encrypt(char str[]);
void decrypt(char str[]); 
int n;		//�����ַ��� 
int a,b;		//��Կ 
int x[500],y[500];		//����ĸת������ֺ���������� 
char str[500],strout[500];		//�����������ַ��� 
	
int main()
{
	int f;
	cout<<"��������Կ��a��b��:"<<endl;
	cin>>a>>b;
	if(gcd(a,26)!=1)
		cout<<"�������Կ���Ϸ�������������"<<endl;
	else
	{
		cout<<"ѡ����ܣ�0�����߽��ܣ�1����"<<endl;
		cin>>f;
		if(f==0)
		{
			cout<<"���������ģ�"<<endl;
			cin>>str;
			n=strlen(str);
			transform(str);
			cout<<"����Ϊ��"<<endl; 
			encrypt(str);
		}
		else
		{
			cout<<"���������ģ�"<<endl;
			cin>>str;
			n=strlen(str);
			transform(str);
			cout<<"����Ϊ��"<<endl; 		
			decrypt(str);
		}	
	}
	return 0; 
} 

int gcd(int m,int n)	//�ж�a��26�Ƿ��� 
{
	if(n<m)				//ȷ��n>m 
	{
		int temp=n;
		n=m;
		m=temp;
	}
	while(m!=0)			//����n=1ʱ���߻��� 
	{
		int y=n%m;
		n=m;
		m=y;
	}
	return n;
}

void transform(char str[])	//����д��ĸͳһת����Сд 
{
	for(int i=0;i<n;i++)
	{
		if(str[i]>=65&&str[i]<=90)
			str[i]=str[i]+32;
	}
}

void encrypt(char str[])		//���� 
{

	for(int i=0;i<n;i++)
	{
		str[i]=str[i]-'a';
		y[i]=(a*str[i]+b)%26;
		strout[i]=y[i]+'a';
		cout<<strout[i];
	}	
} 

void decrypt(char str[])		//���� 
{
	int c;		//a����Ԫ 
	for(int i=1;i<26;i++)		//����a����Ԫ 
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
		if(str[i]>b)			//y-bС��0ʱҪ��26 
			x[i]=(c*(str[i]-b))%26;
		else
			x[i]=(c*(str[i]-b+26))%26;
		strout[i]=x[i]+'a';
		cout<<strout[i];
	} 
} 


