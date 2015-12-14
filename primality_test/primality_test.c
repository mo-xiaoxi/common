
//
//  main.c
//  fast_exponentiation
//
//  Created by moxiaoxi on 15/12/7.
//  Copyright  2015年 moxiaoxi. All rights reserved.
//

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
//#include "Header.h"
//全局变量
static unsigned aPrimeList[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
};//素数表
const unsigned nPrimeListSize=sizeof(aPrimeList)/sizeof(unsigned);//求素数表元素个数
const unsigned nTestCnt = 8; // 表示进行测试的次数
/*************************************************************************/
//函数声明
unsigned  Montgomery(unsigned  n,unsigned  p,unsigned m);//蒙格马利算法快速求幂
//int IsPrime(unsigned n);//判断是否是素数
int RabbinMillerTest( unsigned n );//拉宾米勒测试
/************************************************************************/

//int IsPrime(unsigned n)//判断是否是素数
//{
//    if ( n < 2 )
//    {
//        // 小于2的数即不是合数也不是素数
//        return 0;
//    }
//    const int nListNum = sizeof(aPrimeList) / sizeof(unsigned);
//    for (int i=0;i<nListNum;++i)
//    {
//        // 按照素数表中的数对当前素数进行判断
//        if (1!=Montgomery(aPrimeList[i],n-1,n)&&n!=aPrimeList[i]) // 蒙格马利算法
//        {
//            return 0;
//        }
//    }
//    return 1;
//}

//蒙格马利算法快速求幂 快速计算(n^p)%m的值
unsigned Montgomery(unsigned n,unsigned p,unsigned m)
{ //快速计算(n^p)%m的值
    unsigned k=1;
    if(m!=0)
        n%=m;
    else
        return -1;//error  m为0的状态
    while(p!=1)
    {
        if(0!=(p&1))// 如果指数p是奇数，则说明计算后会剩一个多余的数，那么在这里把它乘到结果中
            k=(k*n)%m;//把“剩下的”乘起来
        n=(n*n)%m;//主体乘方
        p>>=1;//p /= 2; // 指数除以2
    }
    return (n*k)%m;
}

int RabbinMillerTest( unsigned n )
{
    if (n<2)
    {
        // 小于2的数即不是合数也不是素数
        return 0;
    }

    for(int i=0;i<nPrimeListSize;++i)
    {
        // 按照素数表中的数对当前素数进行判断
        if (n/2+1<=aPrimeList[i])
        {
            // 如果已经小于当前素数表的数，则一定是素数
            return 1;
        }
        if (0==n%aPrimeList[i])
        {
            // 余数为0则说明一定不是素数
            return 0;
        }
    }
    // 找到r和m，使得n = 2^r * m + 1;
    int r = 0, m = n - 1; // ( n - 1 ) 一定是合数
    while ( 0 == ( m & 1 ) )
    {
        m >>= 1; // 右移一位
        r++; // 统计右移的次数
    }
    //const unsigned nTestCnt = 8; // 表示进行测试的次数
    for ( unsigned i = 0; i < nTestCnt; ++i )
    {
        // 利用随机数进行测试，
        int a = aPrimeList[ rand() % nPrimeListSize ];
        if ( 1 != Montgomery( a, m, n ) )
        {
            int j = 0;
            int e = 1;
            for ( ; j < r; ++j )
            {
                if ( n - 1 == Montgomery( a, m * e, n ) )
                {
                    break;
                }
                e <<= 1;
            }
            if (j == r)
            {
                return 0;
            }
        }
    }
    return 1;
}


int main(int argc, const char * argv[]) {
    FILE *fp;
    int n,i,count;
    int *p;
    if(argc!=2){
                printf("have not enter file name strike any key exit");
                getchar();
                return -1;
            }
    
    if((fp=fopen(argv[1],"r"))==NULL){
        printf("\nCannot open file strike any key exit!");
        getchar();
        return -1;
    }
    //    if((fp=fopen("fast.txt","r"))==NULL){
    //        printf("\nCannot open file strike any key exit!");
    //        getchar();
    //        return -1;
    //    }
    fscanf(fp,"%d",&n);
    p = (int *)malloc(sizeof(int)*n);
    i=0;
    count=0;
    do{
        fscanf(fp,"%d",&p[i]);
//        //if(IsPrime(p[i])==1)
//        if(RabbinMillerTest(p[i])==1)
//        {
//            //printf("%d\n",p[i]);
//            count++;
//        }
        ++i;
    }while(i<n);
    for(i=0;i<n;i++)
        if(RabbinMillerTest(p[i])==1)
            {
               // printf("%d\n",p[i]);
                count++;
            }//先文件读取 再运算 要快一些 实测
    printf("count =%d\n",count);
    fclose(fp);
    return 0;
}
