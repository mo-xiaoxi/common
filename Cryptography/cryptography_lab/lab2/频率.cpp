#include<iostream>
#include<cstring>
using namespace std;

void transform(char str[]);	//����д��ĸͳһת����Сд 
void sort(char str[]);
void count(char str[]);
float n;
 
void transform(char str[])	//����д��ĸͳһת����Сд 
{
	for(int i=0;i<n;i++)
	{
		if(str[i]>=65&&str[i]<=90)
			str[i]=str[i]+32;
	}
}

void sort(char str[])	//�����ֵ���ĸ��a��z���� 
{
	char temp;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			if(str[i]>str[j])
			{
				temp=str[i];
				str[i]=str[j];
				str[j]=temp;
			}
		}
}

void count(char str[])	//ͳ��ÿ����ĸ���ֵĴ�����Ƶ�� 
{
	int i,m=1;
	for(i=0;i<n;i++)
	{
		if(str[i]==str[i+1])
			m++;
		else
		{
			float p=m/n;
			cout<<str[i]<<' '<<m<<' '<<p<<endl;
			m=1;
		}
	}
}

int main()
{
	char str[200]; 
	cout<<"�������ַ�����500�����ڣ������ִ�Сд����"<<endl;
	cin>>str;
	n=strlen(str);
	cout<<"�ַ�����Ϊ��"<<n<<endl; 
	transform(str);
	sort(str);
	count(str);
	return 0;
}



