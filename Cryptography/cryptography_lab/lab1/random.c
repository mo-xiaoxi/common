#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<stdio.h>
using namespace std;
#define N 256

void function1();
void function2();
void function3();

int main()
{
	cout<<"第一种方法："<<endl;
	function1();
	cout<<"第二种方法："<<endl;
	function2();
	cout<<"应用："<<endl;
	function3(); 
	return 0; 
} 

void function1()	//使用方法一进行随机排列，读取文件 
{
	int a[256],b[256];
	int i,j,n,temp;
	FILE *fp;
	cout<<"输入排序数组大小: "<<endl;
	cin>>n;		//输入排序数组大小 
	for(i=0;i<=n;i++)		//初始化待排序数组 
		a[i]=i;		 
	 
	fp=fopen("text.txt","r");	//从文件读取b[] 
	for(i=0;i<=n;i++)
		b[i]=fgetc(fp);
	fclose(fp);
	
	for(i=n;i>0;i--)		//计算并置换 
	{
		j=(b[i-1]+b[i])%i;
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
	
	for(i=0;i<n;i++)
		cout<<a[i]<<' ';
	cout<<a[n]<<endl;
}

void function2()
{
	int i,j,m,n;
	int a[256],b[256];
	
	memset(a,0,sizeof(a));		//将a[],b[]置为0 
	memset(b,0,sizeof(b));
	cout<<"输入m与n"<<endl; 
	cin>>m>>n;
	
	srand((unsigned int) time(0));	//以系统流逝时间作为随机数发生器种子 
	for(i=0;i<m;i++)
	{
		j=rand()%(n+1);	//产生随机数并对n+1取余 
		if(!a[j])
		{
			a[j]=j;
		}
	} 
	for(i=0;i<=n;i++)
	{
		if(b[a[i]]==0)			//如果这个数第一次出现则输出
			cout<<a[i]<<' ';	
		b[a[i]]=1;				//这个数已经出现过 
	}
	for(i=0;i<=n;i++)
	{
		if(b[i]==0)				//将未出现的数按顺序输出 
			cout<<i<<' ';
	}
	cout<<endl;
}

void swap(int* a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void function3() {
	srand((unsigned)time(NULL));
	int n, t;
	int a[N];
	int b[N];
	for (int i = 0;i < N;++i) {
		b[i] = i ;
	}
	printf("请输入演讲的人数\n");
	scanf("%d", &n);
	for (int i = 0;i < n;++i) {
		t = rand() % (n - i);//只从剩下的数据中随机抽取，之后的数据都不予考虑
		a[i] = b[t];//填入目标数组
		swap(&b[t], &b[n - i - 1]);//将选出的数据与最后一个数据进行交换
	}
	printf("演讲顺序如下：\n");
	for (int i = 0;i < n;++i) {
		printf(">>\t%d\t<<\n", a[i]);
	}
	system("pause");
}
