#include "banker.h"
#include<iostream>
using namespace std;

#define MAXPROCESS 100                        //最大进程数
#define MAXRESOURCE 100                       //最大资源数
int AVAILABLE[MAXRESOURCE];                   //可利用资源向量
int MAX[MAXPROCESS][MAXRESOURCE];            //最大需求矩阵
int ALLOCATION[MAXPROCESS][MAXRESOURCE];    //分配矩阵
int NEED[MAXPROCESS][MAXRESOURCE];            //需求矩阵
int REQUEST[MAXPROCESS][MAXRESOURCE];        //进程需要资源数
bool FINISH[MAXPROCESS];                        //表示系统是否有足够的资源分配给进程
int p[MAXPROCESS];                             //记录序列
int m, n;                                    //m个进程,n个资源
int i, j;									//遍历变量

int main()
{
	Init();
	Bank();
	return 0;
}


void Init()            //初始化算法 初始化银行家算法中所要模拟的各种资源
{
	cout << "请输入进程的数量:";
	cin >> m;
	cout << "请输入资源的类数:";
	cin >> n;
	cout << "请输入每个资源提供的最大数量：";
	for (i = 0; i < n; i++)
		cin >> AVAILABLE[i];
	cout << "请输入每个进程最大需求资源数：（即最大需求矩阵：格式为" << m << "x" << n <<")"<< endl;
	for (i = 0; i<m; i++)
	for (j = 0; j<n; j++)
		cin >> MAX[i][j];
	cout << "请输入每个进程已分配的资源数：（即分配矩阵：格式为" << m << "x" << n << ")" << endl;
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			cin >> ALLOCATION[i][j];
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j]<0)
			{
				cout << "对不起！您输入的第" << i + 1 << "个进程所拥有的第" << j + 1 << "个资源数值非法,请重新输入:" << endl;
				cout << "ALLOCATION[" << i + 1 << "][" << j + 1 << "]=";
				j--;
				continue;
			}
		}
	}
	//得到当前资源可利用值
	for (i = 0; i < n; i++)
	for (j = 0; j < m;j++)
	{
		AVAILABLE[j]-=ALLOCATION[i][j];
	}
	IsSafe();//判定初始值是否安全
	print();//输出当前状态
}

void print()   //显示函数
{
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "当前状态下，各进程已得到资源量:    " << endl;
	cout << "资源类别：";
	for (i = 0; i < n; i++)
		cout << i << "    ";
	cout << endl;
	for (i = 0; i<m; i++)
	{
		cout << "进程" << i << ":";
		for (j = 0; j<n; j++)
			cout << "    " << ALLOCATION[i][j];
		cout << endl;
	}

	cout << "当前状态下，系统剩余可利用资源量:    "<<endl;
	for (j = 0; j < n; j++)
		cout << "资源" << j << ": " << AVAILABLE[j] << endl;

	cout << "当前状态下，各进程还需要的资源量:" << endl;
	cout << "资源类别：";
	for (i = 0; i < n; i++)
		cout << i << "    ";
	cout << endl;
	for (i = 0; i<m; i++)
	{
		cout << "进程" << i << ":";

		for (j = 0; j<n; j++)
			cout << "    " << NEED[i][j];
		cout << endl;
	}

	cout << "-------------------------------------------------------------" << endl;
}

bool IsSafe() //安全性算法  判定当前状态，工作是否安全  安全则返回true 不安全返回flase
{
	int  l = 0;
	int Work[MAXRESOURCE];							//表示系统可提供给进程继续运行所需的各类资源数目
	for (i = 0; i < n; i++)//对work进行初始化
		Work[i] = AVAILABLE[i];
	for (i = 0; i < m; i++)//对finish进行初始化
	{
		FINISH[i] = false;//先初始化为不安全
	}
	while (l<m)//正常的话，共执行m次
	{
		int flag=0;//0为不安全，1为安全
		for (i = 0; i < m; i++)//对m个进程一次检查
		{
			if (FINISH[i] == true)
			{
				continue;
			}
			for (j = 0; j < n; j++)
			{
				if (NEED[i][j] > Work[j])
				{
					break;
				}
			}
			if (j == n)//表明进程i是安全的，进程i获得资源后，可顺利执行，直至完成，并释放出分配给它的资源
			{
				FINISH[i] = true;//进程i安全
				for (int k = 0; k < n; k++)
				{
					Work[k] += ALLOCATION[i][k];
				}
				p[l++] = i;//记录进程号
				flag = 1;//表示不安全
			}
			else//进程i是不安全的
			{
				continue;
			}
		}
		if (!flag)
		{
			cout << "系统是不安全的" << endl;
			return false;
		}
	}
	cout << "系统是安全的" << endl;
	cout << "安全序列:" << endl;
	for (i = 0; i < l; i++)//显示资源分配给进程的顺序
	{
		cout << p[i];
		if (i != l - 1)
		{
			cout << "-->";
		}
	}
	cout << "" << endl;
	return true;
}





void Bank()                //银行家算法
{
	int i, pid, number = 0;
	char flag;//标明是否继续分配

	while (1)
	{
		cout << endl;
	enterid:
		cout << "请输入要申请资源的进程ID(注:第1个进程号为0,依次类推)：";
		cin >> pid;
		if (pid > m||pid < 0)
		{
			cout << "进程ID输入错误，请重新输入！" << endl;
			goto enterid;
		}
	enternum:
		cout << "请输入进程"<<pid<<"要申请的各资源数量:" << endl;
		for (i = 0; i<n; i++)
		{
			cin >> REQUEST[pid][i];
		}
		for (i = 0; i<n; i++)//验证请求是否合理
		{
			if (REQUEST[pid][i]>NEED[pid][i])//进程ID申请的资源数量大于其所需要的进程数量
			{
				cout << "进程"<<pid<<"所申请的资源"<<i<<"的数量超出其进程实际需求量！请重新输入！" << endl;
				goto enternum;
			}
			if (REQUEST[pid][i]>AVAILABLE[i])//进程ID申请的资源数量大于系统剩余可用数量
			{
				cout << "进程"<<pid<<"所申请的资源"<<i<<"的数量超出系统剩余最大可用量！请重新输入！" << endl;
				goto enternum;
			}
		}
		for (i = 0; i<n; i++)//如果请求合理，分配资源，计算分配后资源数量
		{
			AVAILABLE[i] -= REQUEST[pid][i];//剩余可用数量
			ALLOCATION[pid][i] += REQUEST[pid][i];//已分配数量
			NEED[pid][i] -= REQUEST[pid][i];//还需要的数量
		}
		if (IsSafe())//判定若资源分配后，是否安全。若安全，则同意分配。
		{
			cout << "系统状态安全，可以分配！" << endl;
		}
		else
		{
			cout << "系统状态为不安全，不可分配！" << endl;
			for (i = 0; i<n; i++)//回到原数量
			{
				AVAILABLE[i] += REQUEST[pid][i];
				ALLOCATION[pid][i] -= REQUEST[pid][i];
				NEED[pid][i] += REQUEST[pid][i];
			}
		}
		for (i = 0; i<n; i++)
		{
			if (NEED[pid][i] == 0)//进程pid的资源i分配完毕
			{
				number++;
			}
		}
		if (number == n)//如果该进程各资源都已分配完毕，则释放资源
		{
			for (i = 0; i<n; i++)
			{
				AVAILABLE[i] += ALLOCATION[pid][i];
				ALLOCATION[pid][i] = 0;
				NEED[pid][i] = 0;
			}
			cout << "进程" << pid << "分配完毕，其占有的资源被释放！" << endl;
			print();//输出当前状态
			number = 0;
		}
		for (i = 0; i<m; i++)//分配好了以后将进程的标识FINISH改成false
		{
			FINISH[i] = false;
		}
		cout << "是否继续请求分配资源？（若是，请输入y/Y.否则输入其它）" << endl;
		cin >> flag;
		if (flag == 'y' || flag == 'Y')
		{
			continue;
		}
		break;
	}
}
