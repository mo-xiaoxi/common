
//
//  main.c
//  primality_test
//
//  Created by moxiaoxi on 15/12/7.
//  Copyright  2015年 moxiaoxi. All rights reserved.
//

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
//#include "Header.h"
/**************************************************************/
unsigned  Montgomery(unsigned  n,unsigned  p,unsigned m);//蒙格马利算法快速求幂
/**************************************************************/


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

int main(int argc, const char * argv[]) {
    FILE *fp;
    int n,i;
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
    printf("%d\n",n);
    n*=3;
    p = (int *)malloc(sizeof(int)*n);
    i=0;
    for(i=0;i<n;)
    {
        fscanf(fp,"%d",&p[i++]);
        fgetc(fp);
        fscanf(fp,"%d",&p[i++]);
        fgetc(fp);
        fscanf(fp,"%d",&p[i++]);
        fgetc(fp);
        //printf("%d＝%d %d＝%d %d＝%d\n",i-3,p[i-3],i-2,p[i-2],i-1,p[i-1]);
        //printf("%d\n",Montgomery(p[i-3],p[i-2],p[i-1]));
    }
    for(i=0;i<n;i+=3)
    {   //printf("%d＝%d %d＝%d %d＝%d\n",i,p[i],i+1,p[i+1],i+2,p[i+2]);
       printf("%d\n",Montgomery(p[i],p[i+1],p[i+2]));
    }
    fclose(fp);
    return 1;

}
