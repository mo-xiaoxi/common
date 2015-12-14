//
//  Header.h
//  prime
//
//  Created by moxiaoxi on 15/12/10.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//

#ifndef Header_h
#define Header_h
/* Accuracy with which we test for prime numbers using Solovay-Strassen algorithm.
 * 20 Tests should be sufficient for most largish primes */
#define ACCURACY 20//检验素数时的测试次数 值越大 检测失误的可能性越低，但是随之速度也越慢

#define FACTOR_DIGITS 100
#define EXPONENT_MAX RAND_MAX
#define BUF_SIZE 512//buffer容量 如果一个数字，它10进制的最大容量是512个位  ！！！！注意 要依据测试值，修改这个值

/* bignum的容量之*/
#define BIGNUM_CAPACITY 20

/* 用于检验计算是否溢出*/
#define RADIX 4294967296UL //4字节的unsigned最大值
#define HALFRADIX 2147483648UL

#define MAX(a,b) ((a) > (b) ? (a) : (b))

/**
 基本单元
 */
typedef unsigned int word;

/**
bignum的结构体  length表示实际有多少个data capacity是这个结构体的容量（data的最大量） data是一个unsigned int类型
 这里采用多个unsigned int 拼接起来   
 eg 对于小于2^32的数  length＝1；capcacity＝20；只有一个data用于保存数值
 对于2^32~2^64  length=2;capacity=20;两个data来保存数值
 对于一个超过20个data来表示的数  扩大capacity的值即可
 */
typedef struct _bignum {
    int length;
    int capacity;
    word* data;
} bignum;

/**
 函数定义
 */
bignum* bignum_init();//初始化函数
void  bignum_reset(bignum* p);
void bignum_deinit(bignum* b);//回收函数 释放空间
void bignum_reset(bignum* p);//重置p为初始值
int bignum_iszero(bignum* b);//判断b是否0，为0则返回1
int bignum_isnonzero(bignum* b);//if not ,return 1
void bignum_copy(bignum* source, bignum* dest);//复制
void bignum_fromstring(bignum* b, char* string);//把字符串数值转化为bignum存储的大数  用字符串设置b
void bignum_fromint(bignum* b, unsigned int num);//用num来设置b
void bignum_print(bignum* b) ;//显示函数
int bignum_equal(bignum* b1, bignum* b2);//验证b1与b2是否相等
int bignum_greater(bignum* b1, bignum* b2);
int bignum_less(bignum* b1, bignum* b2);
void bignum_iadd(bignum* source, bignum* add) ;//source=source+add
void bignum_add(bignum* result, bignum* b1, bignum* b2); //result=b1+b2
void bignum_isubtract(bignum* source, bignum* sub);//source-=sub
void bignum_subtract(bignum* result, bignum* b1, bignum* b2);//result=b1-b2
void bignum_imultiply(bignum* source, bignum* mult);//source *= mult
void bignum_multiply(bignum* result, bignum* b1, bignum* b2);//result = b1 * b2
void bignum_idivide(bignum *source, bignum *div);//source = source/div
void bignum_idivider(bignum* source, bignum* div, bignum* remainder);//source = source/div and remainder = source - source/div.
void bignum_imodulate(bignum* source, bignum* modulus);//source = source % modulus
//商quotient = floor(b1/b2), 余数remainder = b1 - quotient * b2. If b1 < b2 ,quotient =0 and remainder = b2.
void bignum_divide(bignum* quotient, bignum* remainder, bignum* b1, bignum* b2) ;
//蒙哥马利法快速计算 result = base^exponent mod modulus
void bignum_modpow(bignum* base, bignum* exponent, bignum* modulus, bignum* result);
void bignum_gcd(bignum* b1, bignum* b2, bignum* result);//result = gcd(b1, b2)
int bignum_jacobi(bignum* ac, bignum* nc);//计算雅可比符号 J（ac，nc）
int solovayPrime(int a, bignum* n);//验证a是否是n的一个欧拉函数 如果是的，则满足a^(n - 1)/2 != Ja(a, n) mod n
int probablePrime(bignum* n, int k) ;//验证n是否是一个素数

/**
 定义0～10 因为转化的时候 需要使用这些常数
 */
word DATA0[1] = {0}; word DATA1[1] = {1}; word DATA2[1] = {2};
word DATA3[1] = {3}; word DATA4[1] = {4}; word DATA5[1] = {5};
word DATA6[1] = {6}; word DATA7[1] = {7}; word DATA8[1] = {8};
word DATA9[1] = {9}; word DATA10[1] = {10};
bignum NUMS[11] = {{1, 1, DATA0},{1, 1, DATA1},{1, 1, DATA2},
    {1, 1, DATA3},{1, 1, DATA4},{1, 1, DATA5},
    {1, 1, DATA6},{1, 1, DATA7},{1, 1, DATA8},
    {1, 1, DATA9},{1, 1, DATA10}};

#endif /* Header_h */

