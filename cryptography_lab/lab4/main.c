//
//  main.cpp
//  
//
//  Created by moxiaoxi on 15/12/16.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//

#include<iostream>
#include "string"
#include<cmath>
#include<fstream>
using namespace std;
int Geffe(int k1[],int k2[],int k3[],int b[])
{
    
     cout<<"Geffe:";
    for(int i=0; i< 31; i++)
    {
        b[i]=(k1[i]&k2[i])|(k3[i]&k2[i])|k3[i];
        
    }
    for(int i=0;i<31;i++)
        cout<<b[i]<<" ";
    return 0;
}
int JK(int k1[],int k2[],int c[])
{
    cout<<"JK:";
    for(int i=0; i< 31; i++)
    {
        c[i]=(k1[i]|k2[i]+1)&c[i-1]|k1[i];
        
    }
    for(int i=0;i<31;i++)
        cout<<c[i]<<" ";
    return 0;
}

void cypt(int b[])
{
    int j;
    int i;
    int k;
    int sum=0;
    char cypher[100],cyph[100];
    int sum0[100];
    cout<<"input the cyphertext:";
    //	for(j=0;j<100;j++){
    //		scanf("%c",cypher[i]);
    //	}
    cin>>cypher;
    //j=sizeof(cypher);
    for(int l=0;l<100;l++)//将密钥转化为10进制
    {
        i=0;
        for( k=0;k<8;++k)
            sum+=pow(2,7-k)*b[(i+k)%31];
        //cout<<sum;
        sum0[l]=sum;
        if(i+k>32)
            i=(i+k-1)%31+1;
        else
            i=i+8;
        
    }
    cout<<"密文:";
    for( j=0;cypher[j]!='\0';j++)
    {
        
        cyph[j]=cypher[j]^sum0[j];//加密
        cout<<cyph[j];
    }
    cout<<endl;
    cout<<"明文:";
    for(int k=0;k<j;k++)
    {
        cypher[k]=cyph[k]^sum0[k];//解密
        cout<<cypher[k];
    }
    cout<<endl;
}

int main()
{
    int k1[31]={1,1,0,0,1};
    int k2[31]={0,0,1,0,1};
    int k3[31]={0,1,0,1,0};
    int i=0;
    for(i=5;i<31;i++)
        k1[i]=(k1[i-5]+k1[i-2])%2;
    
    for(i=5;i<31;i++)
        k2[i]=(k2[i-5]+k2[i-2])%2;
    
    for(i=5;i<31;i++)
        k3[i]=(k3[i-5]+k3[i-2])%2;
    
    cout<<"LSFR1：";
    	for(i=0;i<31;i++)
            cout<<k1[i]<<" ";
    cout<<endl;
    cout<<"LSFR2：";
    	for(i=0;i<31;i++)
            cout<<k2[i]<<" ";
    cout<<endl;
    cout<<"LSFR3：";
    	for(i=0;i<31;i++)
    	cout<<k3[i]<<" ";
    cout<<endl;
    
    int b[31];
    Geffe(k1,k2,k3,b);//生成2进制密钥
    cout<<endl;
    int c[31];
    c[0]=0;
    JK(k3,k2,c);//生成2进制密钥
    cout<<endl;
    cout<<"Geffe operate:"<<endl;
    cypt(b);
    cout<<endl;
    cout<<"J-K operate:"<<endl;
    cypt(c);
    
    return 0;
}


