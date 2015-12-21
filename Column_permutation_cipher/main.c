//
//  main.cpp
//  实验5
//
//  Created by moxiaoxi on 15/12/16.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//
/*
 （1）       输入密钥
 （2）   排出密钥中字母的顺序
 （3）   输入明文
 （4）   按密钥中字母的顺序打乱明文顺序
 （5）   输出密文
 （6）   解密
 （7）   输出明文
 */
#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,l,k,m,num[30];
    char key[30],plantext[100],plantext2[100],cipher[100];
    printf("please input the key\n");
    scanf("%s",key);
    l=strlen(key);
    for(i=0;i<l;i++)
    {
        num[i]=0;
        for(j=0;j<l;j++)
        {
            
            if(key[j]<=key[i])//二重循环遍历 得到当前字母在整个密钥中的顺序
                //即d在密钥 a b d e c 中代表4 其中c代表3 e代表5 即12453 这里就是3换到5位置  5换到4 4—>3
            {
                
                num[i]++;
            }
            if(key[j]==key[i]&&j>i)//这里是处理密钥字母重复问题 通过后面的限制 可以令就算有重复的数 也不会存在重复的列 输入aa 返回12
                num[i]--;
            
        }
    }
    printf("please input the plantext\n");
    scanf("%s",plantext);
    k=strlen(plantext);
    
    i=0;											//末尾补x
    for(m=k%l;m<l;m++)
    {
        
        plantext[k+i]='x';
        i++;
    }
    int temp=i;//保存添加了多少多余字符
    if(k%l==0)										//计算有多少行
        m=k/l;
    else
        m=k/l+1;
    printf("加密:\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<l;j++)
        {
            
            cipher[i*l+j]=plantext[i*l+num[j]-1];//cipher从00-01-02.。。10-11遍历 即正常遍历 而plantext由密钥来决定 进行列变换
            
        }
    }
    for(i=0;i<l;i++)								//输出密文
    {
        for(j=0;j<m;j++)
            printf("%c",cipher[j*l+i]);//进行列遍历
    }
    printf("\n");
    
    printf("解密:\n");								//解密密文
    for(i=0;i<m;i++)
    {
        for(j=0;j<l;j++)
        {
            
            plantext2[i*l+num[j]-1]=cipher[i*l+j];
        }
    }
    plantext2[(i-1)*l+j-temp]='\0';//去除多余字符
    printf("%s\n",plantext2);
    return 0;
}
