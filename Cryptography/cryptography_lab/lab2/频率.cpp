#include<iostream>
#include<cstring>
using namespace std;

void transform(char str[]);	//将大写字母统一转换成小写 
void sort(char str[]);
void count(char str[]);
float n;
 
void transform(char str[])	//将大写字母统一转换成小写 
{
	for(int i=0;i<n;i++)
	{
		if(str[i]>=65&&str[i]<=90)
			str[i]=str[i]+32;
	}
}

void sort(char str[])	//将出现的字母从a到z排序 
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

void count(char str[])	//统计每个字母出现的次数及频率 
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
	cout<<"请输入字符串（500字以内，不区分大小写）："<<endl;
	cin>>str;
	n=strlen(str);
	cout<<"字符总数为："<<n<<endl; 
	transform(str);
	sort(str);
	count(str);
	return 0;
}



