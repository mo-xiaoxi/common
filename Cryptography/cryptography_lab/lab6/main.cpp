//
//  main.cpp
//  实验6
//
//  Created by moxiaoxi on 15/12/16.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string.h>
using namespace std;
void strupr(char str1[])//将字符串转化为大写
{
    int i;
    for(i=0;str1[i];i++)
        if(str1[i]>='a'&&str1[i]<='z')
            str1[i]-=32;
}

int main(int argc, const char * argv[]) {
    char plaintext[100],key[100],ciphertext[100],decodetext[100];
    int n,k;
    cout<<"请输入密钥：";
    cin>>key;
    k=strlen(key);			//得到密钥长度
    strupr(key);    //将密钥转化为大写
    cout<<"请输入要加密的明文：";
    cin>>plaintext;
    n=strlen(plaintext);		//得到明文长度
    strupr(plaintext);		//转化为大写
    
    int j=0;
    for(int i=0;i<n;i++)
    {
        j=j%k;
        if(plaintext[i]>=65 && plaintext[i]<=90)
        {
            ciphertext[i]=(plaintext[i]-65 + key[j]-65)%26 +65;		//加密
            j++;
        }
    }
    cout<<"密文为："<<ciphertext<<endl;
    
    j=0;
    for(int i=0;i<n;i++)
    {
        j=j%k;
        if(ciphertext[i]>=65 && ciphertext[i]<=90)
        {
            int temp=ciphertext[i]-65 - (key[j]-65);//解密
            if(temp>=0)
                decodetext[i]=temp%26+97;
            else
                decodetext[i]=(temp+26)%26+97;
            j++;
        }
    }
    cout<<"解密后数据："<<decodetext<<endl;
    return 0;
}
