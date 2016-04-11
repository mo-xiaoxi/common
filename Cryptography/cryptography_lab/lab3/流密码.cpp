#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;

int main()
{
	//产生密钥 
	int a[31]={1,1,0,0,1};   //a[5]=(a[0]+a[3])%2,逐位右移 
	for(int k=5;k<31;k++)
		a[k]=(a[k-2]+a[k-5])%2;
	cout<<"The key:"<<endl;
	for(int i=0;i<31;i++)
		cout<<a[i]<<' ';
	cout<<endl;
	
	int i=0,f;
	cout<<"Please choose one operation:1-encryption 2-decryption"<<endl;
	cin>>f;
	vector<int>s;
	if(f==1||f==2)
	{
		if(f==1)			//f=1时加密 
		{
			cout<<"Encrypt successfully.To see the ciphertext in out.txt."<<endl;
			ifstream in("in.txt");		//读入in.txt的ASC码 
			ofstream out("out.txt");	//输出 
			char c;
			while(in>>c)
			{
				int sum=0;
				for(int j=0;j<8;j++)
				{
					sum+=pow(2,7-j)*a[(i+j)%31];
					if(i+j>32)
						i=(i+j-1)%31+1;
					else
						i=i+8;
				}
				s.push_back((int (c))^sum);		//尾部插入 
			}
			for(int k=0;k<s.size();k++)
				out<<char(s[k]);
		}
		if(f==2)		//f=2时解密 
		{
			cout<<"Decrypt successfully.To see the plaintext in in.txt."<<endl;
			ifstream in("out.txt");
			ofstream out("in.txt");
			char c;
			while(in>>c)
			{
				int sum=0;
				for(int j=0;j<8;j++)
				{
					sum+=pow(2,7-j)*a[(i+j)%31];
					if(i+j>32)
						i=(i+j-1)%31+1;
					else
							i=i+8;
				}
				s.push_back((int (c))^sum);	
			}
			for(int k=0;k<s.size();k++)
				out<<char(s[k]);
		}
	}
	else
		cout<<"Invalid operation."<<endl;		//f不为1或者2时输入无效 
}

