//
//  main.c
//  hash
//
//  Created by moxiaoxi on 15/12/26.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//
#include <stdio.h>
#include "hash_aes.h"
#include <string.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
    FILE *fp1;
    if(argc!=2){
        printf("have not enter all the  name strike any key exit");
        getchar();
        return -1;
    }
    
    if((fp1=fopen(argv[1],"r"))==NULL){
        printf("\nCannot open input file strike any key exit!");
        getchar();
        return -1;
    }
    
//        if((fp1=fopen("11.pdf","r"))==NULL){
//            printf("\nCannot open read file strike any key exit!");
//            getchar();
//            return -1;
//        }
    unsigned char key[16];
    printf("please input the key:\n");//输入密钥
    scanf("%s",key);
    //printf("%s\n",key);
    readfile_aeshash(fp1,key);//读取文件并进行hash
    return 0;
    
}



// prints string as hex
static void phex(unsigned char* str,int n)
{
    unsigned char i;
    for(i = 0; i < n; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}

//异或运算
static void exclusive(unsigned char* output, unsigned char* input,int n)

{
    
    unsigned char i;
    
    for (i=0;i<n;++i)
        
    {
        
        output[i] ^= input[i];
        
    }
    
    
}
//从128位扩展到160位 16=>20
void hashExpansion(unsigned char *input)
{
    int i;
    for(i=0;i<4;i++)
    {
        input[16+i]=input[i]^input[i+4]^input[i+8]^input[i+12];
    }
}
//哈希函数

void hash(unsigned long len,unsigned char *input,unsigned char *key)
{
    unsigned long i,numb,numc,temp;
    numb=len/16;//一共可以分为多少块 加解密
    numc=len%16;//剩余多少
    unsigned char output[20];
    memset(output,0, 20*sizeof(unsigned char));
    //正好是16的整数倍 且大于16
    if (numc == 0){
        AES128_encrypt(input,key,output);
        exclusive(output,input,KEYLEN);//第一轮用输入密钥作为初始密钥
        for (i = 1; i < numb; ++i){
            AES128_encrypt(input+16*i,output,output);//其余轮，密钥为上一轮加密后数据
            exclusive(output,input+16*i,KEYLEN);
        }
    }//非16整数倍
    else
    {
        temp=16-numc;
        //补位
        for(i=16;i>numc;--i)
        {
            
            input[16*numb+i-1]=temp;
            
        }
        numb++;//补完以后，分组加1
        AES128_encrypt(input,key,output);
        exclusive(output,input,KEYLEN);//第一轮用输入密钥作为初始密钥
        for (i = 1; i < numb; ++i){
            AES128_encrypt(input+16*i,output,output);//其余轮，密钥为上一轮加密后数据
            exclusive(output,input+16*i,KEYLEN);
        }
        
    }
    hashExpansion(output);//扩展
    phex(output,20);
    return;
}


//读取文件并hash—aes加密
void readfile_aeshash(FILE * pFile,unsigned char *key)
{
    unsigned long len;
    unsigned char *pBuf;
    fseek(pFile,0,SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
    len=ftell(pFile); //获取文件长度
    //printf("%ld\n",len);
    pBuf=(unsigned char*)malloc(sizeof(unsigned char)*(len+1)); //定义数组长度
    rewind(pFile); //把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
    fread(pBuf,1,len,pFile); //读文件
    pBuf[len]=0; //把读到的文件最后一位 写为0 要不然系统会一直寻找到0后才结束
    //printf("%s\n",pBuf);  //显示读到的数据
    hash(len,pBuf,key);//hash运算
    fclose(pFile); // 关闭文件
    return ;
}






/*
 
 //得到通过S盒加密后的值
 
 static unsigned char getSBoxValue(unsigned char num)
 
 {
 
 return sbox[num];
 
 }
 
 
 
 //得到通过逆向S盒解密的值
 
 static unsigned char getSBoxInvert(unsigned char num)
 
 {
 
 return rsbox[num];
 
 }
 
 */

/*
 
 下面的为加密函数
 
 */

//生成轮密钥

static void KeyExpansion(void)

{
    
    int i, k;
    
    unsigned char tempa[4];
    
    
    
    // 第一轮
    
    for(i = 0; i < Nk; ++i)
        
    {/*
      
      RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
      
      RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
      
      RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
      
      RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];*/
        
        
        
        RoundKey[(i<<2) + 0] = Key[(i<<2) + 0];
        
        RoundKey[(i<<2) + 1] = Key[(i<<2) + 1];
        
        RoundKey[(i<<2) + 2] = Key[(i<<2) + 2];
        
        RoundKey[(i<<2) + 3] = Key[(i<<2) + 3];
        
    }
    
    
    
    //其余轮
    
    for(; (i < (Nc * (Nr + 1))); ++i)
        
    {
        
        /* for(j = 0; j < 4; ++j)
         
         {
         
         tempa[j]=RoundKey[(i-1) * 4 + j];
         
         }*/
        
        tempa[0]=RoundKey[(i-1) * 4 + 0];
        
        tempa[1]=RoundKey[(i-1) * 4 + 1];
        
        tempa[2]=RoundKey[(i-1) * 4 + 2];
        
        tempa[3]=RoundKey[(i-1) * 4 + 3];
        
        //W[0] W[4] W[8]...
        
        if (i % Nk == 0)
            
        {
            
            // 首先将4个输入字节翻转
            
            // [a0,a1,a2,a3]=》[a1,a2,a3,a0]
            
            
            
            {
                
                k = tempa[0];
                
                tempa[0] = tempa[1];
                
                tempa[1] = tempa[2];
                
                tempa[2] = tempa[3];
                
                tempa[3] = k;
                
            }
            
            
            
            //	执行S盒替换
            
            {
                
                tempa[0] = sbox[tempa[0]];
                
                tempa[1] = sbox[tempa[1]];
                
                tempa[2] = sbox[tempa[2]];
                
                tempa[3] = sbox[tempa[3]];
                
            }
            
            //与轮系数想加
            
            tempa[0] =  tempa[0] ^ Rcon[i/Nk];
            
        }//下面考虑其他位数的加解密
        
        /*else if (Nk > 6 && i % Nk == 4)
         
         {
         
         // Function Subword()
         
         {
         
         tempa[0] = sbox[tempa[0]];
         
         tempa[1] = sbox[tempa[1]];
         
         tempa[2] = sbox[tempa[2]];
         
         tempa[3] = sbox[tempa[3]];
         
         }
         
         }*/
        
        RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ tempa[0];
        
        RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ tempa[1];
        
        RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ tempa[2];
        
        RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ tempa[3];
        
    }
    
}



// 密钥加法函数

static void AddRoundKey(unsigned char round)

{
    
    unsigned char i;
    
    for(i=0;i<4;++i)
        
    {
        
        /* for(j = 0; j < 4; ++j)
         
         {
         
         (*matrix)[i][j] ^= RoundKey[round * Nc * 4 + i * Nc + j];
         
         }*/
        
        (*matrix)[i][0] ^= RoundKey[round * Nc * 4 + i * Nc + 0];
        
        (*matrix)[i][1] ^= RoundKey[round * Nc * 4 + i * Nc + 1];
        
        (*matrix)[i][2] ^= RoundKey[round * Nc * 4 + i * Nc + 2];
        
        (*matrix)[i][3] ^= RoundKey[round * Nc * 4 + i * Nc + 3];
        
    }
    
}



//正向S盒操作

static void SubBytes(void)

{
    
    unsigned char j;
    
    for(j = 0; j < 4; ++j)
        
    {
        
        /*for(j = 0; j < 4; ++j)
         
         {
         
         // (*matrix)[j][i] = getSBoxValue((*matrix)[j][i]);  不调用函数 直接运算 加快速度
         
         (*matrix)[j][i] = sbox[(*matrix)[j][i]];
         
         }*/
        
        (*matrix)[j][0] = sbox[(*matrix)[j][0]];
        
        (*matrix)[j][1] = sbox[(*matrix)[j][1]];
        
        (*matrix)[j][2] = sbox[(*matrix)[j][2]];
        
        (*matrix)[j][3] = sbox[(*matrix)[j][3]];
        
    }
    
}



//ShiftRows操作

static void ShiftRows(void)

{
    
    unsigned char temp;
    
    
    
    //向右移动三位 即向左移动一位
    
    temp           = (*matrix)[0][1];
    
    (*matrix)[0][1] = (*matrix)[1][1];
    
    (*matrix)[1][1] = (*matrix)[2][1];
    
    (*matrix)[2][1] = (*matrix)[3][1];
    
    (*matrix)[3][1] = temp;
    
    
    
    //向左移动两位
    
    temp           = (*matrix)[0][2];
    
    (*matrix)[0][2] = (*matrix)[2][2];
    
    (*matrix)[2][2] = temp;
    
    
    
    temp       = (*matrix)[1][2];
    
    (*matrix)[1][2] = (*matrix)[3][2];
    
    (*matrix)[3][2] = temp;
    
    
    
    // 向左移动3位
    
    temp       = (*matrix)[0][3];
    
    (*matrix)[0][3] = (*matrix)[3][3];
    
    (*matrix)[3][3] = (*matrix)[2][3];
    
    (*matrix)[2][3] = (*matrix)[1][3];
    
    (*matrix)[1][3] = temp;
    
}





static unsigned char xtime(unsigned char x)

{
    
    return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
    
}



//MixColumns操作

static void MixColumns(void)

{
    
    unsigned char i;
    
    unsigned char Temp1,Temp2,temp3;
    
    for(i = 0; i < 4; ++i)
        
    {
        
        temp3 = (*matrix)[i][0];
        
        Temp1 = (*matrix)[i][0] ^ (*matrix)[i][1] ^ (*matrix)[i][2] ^ (*matrix)[i][3] ;
        
        Temp2  = (*matrix)[i][0] ^ (*matrix)[i][1] ;
        
        Temp2 = xtime(Temp2);
        
        (*matrix)[i][0] ^= Temp2 ^ Temp1 ;
        
        Temp2  = (*matrix)[i][1] ^ (*matrix)[i][2] ;
        
        Temp2 = xtime(Temp2);
        
        (*matrix)[i][1] ^= Temp2 ^ Temp1 ;
        
        Temp2  = (*matrix)[i][2] ^ (*matrix)[i][3] ;
        
        Temp2 = xtime(Temp2);
        
        (*matrix)[i][2] ^= Temp2 ^ Temp1 ;
        
        Temp2  = (*matrix)[i][3] ^ temp3 ;
        
        Temp2 = xtime(Temp2);
        
        (*matrix)[i][3] ^= Temp2 ^ Temp1 ;
        
    }
    
}





// 加密主要操作

static void AES_encrypt(void)

{
    
    unsigned char round = 0;//轮数
    
    
    
    //第一次密钥加法层
    
    AddRoundKey(0);
    
    
    
    //\共有Nr轮加密 这里为10轮
    
    // 下面实现第一轮到Nr-1轮 即1-9轮
    
    //
    
    for(round = 1; round < Nr; ++round)
        
    {
        
        SubBytes();//字节替换 S盒
        
        ShiftRows();
        
        MixColumns();
        
        AddRoundKey(round);
        
    }
    
    
    
    //最后一轮加密 无MixColumn
    
    SubBytes();
    
    ShiftRows();
    
    AddRoundKey(Nr);
    
}



/*
 
 下面的为解密过程
 
 */







//
////逆向MixColumns混淆
//
//static void InvMixColumns(void)
//
//{
//
//    int i;
//
//    unsigned char a,b,c,d;
//
//    for(i=0;i<4;++i)
//
//    {
//
//        a = (*matrix)[i][0];
//
//        b = (*matrix)[i][1];
//
//        c = (*matrix)[i][2];
//
//        d = (*matrix)[i][3];
//
//
//
//        (*matrix)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
//
//        (*matrix)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
//
//        (*matrix)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
//
//        (*matrix)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
//
//    }
//
//}
//
//
//
////逆向S盒操作
//
//static void InvSubBytes(void)
//
//{
//
//    unsigned char j;
//
//    for(j=0;j<4;++j)
//
//    {
//
//        /* for(j=0;j<4;++j)
//
//         {
//
//         (*matrix)[j][i] = rsbox[(*matrix)[j][i]];
//
//         }*/
//
//
//
//        (*matrix)[j][0] = rsbox[(*matrix)[j][0]];
//
//        (*matrix)[j][1] = rsbox[(*matrix)[j][1]];
//
//        (*matrix)[j][2] = rsbox[(*matrix)[j][2]];
//
//        (*matrix)[j][3] = rsbox[(*matrix)[j][3]];
//
//
//
//    }
//
//}
//
//
//
////逆向ShiftRows操作
//
//static void InvShiftRows(void)
//
//{
//
//    unsigned char temp;
//
//
//
//    // 右移1位
//
//    temp=(*matrix)[3][1];
//
//    (*matrix)[3][1]=(*matrix)[2][1];
//
//    (*matrix)[2][1]=(*matrix)[1][1];
//
//    (*matrix)[1][1]=(*matrix)[0][1];
//
//    (*matrix)[0][1]=temp;
//
//
//
//    // 右移2位
//
//    temp=(*matrix)[0][2];
//
//    (*matrix)[0][2]=(*matrix)[2][2];
//
//    (*matrix)[2][2]=temp;
//
//
//
//    temp=(*matrix)[1][2];
//
//    (*matrix)[1][2]=(*matrix)[3][2];
//
//    (*matrix)[3][2]=temp;
//
//
//
//    // 右移动3位
//
//    temp=(*matrix)[0][3];
//
//    (*matrix)[0][3]=(*matrix)[1][3];
//
//    (*matrix)[1][3]=(*matrix)[2][3];
//
//    (*matrix)[2][3]=(*matrix)[3][3];
//
//    (*matrix)[3][3]=temp;
//
//}
//
//
//
//
//
////解密总过程
//
//static void AES_decrypt(void)
//
//{
//
//    unsigned char round;
//
//    AddRoundKey(Nr);
//
//
//
//    for(round=Nr-1;round>0;--round)
//
//    {
//
//        InvShiftRows();
//
//        InvSubBytes();
//
//        AddRoundKey(round);
//
//        InvMixColumns();
//
//    }
//
//    InvShiftRows();
//
//    InvSubBytes();
//
//    AddRoundKey(0);
//
//}
//












static void BlockCopy(unsigned char* output, unsigned char* input)

{
    
    unsigned char i;
    
    for (i=0;i<KEYLEN;++i)
        
    {
        
        output[i] = input[i];
        
    }
    
    
}




void AES128_encrypt(unsigned char* input, const unsigned char* key, unsigned char* output)

{
    
    
    
    BlockCopy(output, input);
    
    matrix = (matrix_t*)output;
    
    Key = key;
    
    KeyExpansion();
    
    AES_encrypt();
    
}

//
//void AES128_decrypt(unsigned char* input, const unsigned char* key, unsigned char *output)
//
//{
//
//
//    BlockCopy(output, input);
//
//    matrix = (matrix_t*)output;
//
//    Key = key;
//
//    AES_decrypt();
//
//}
