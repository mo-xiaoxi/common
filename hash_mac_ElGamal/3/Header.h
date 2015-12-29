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
#define ACCURACY 20

#define FACTOR_DIGITS 100
#define EXPONENT_MAX RAND_MAX
#define BUF_SIZE 1025

/* Initial capacity for a bignum structure. They will flexibly expand but this
 * should be reasonably high to avoid frequent early reallocs */
#define BIGNUM_CAPACITY 20

/* Radix and halfradix. These should be changed if the limb/word type changes */
#define RADIX 4294967296UL
#define HALFRADIX 2147483648UL

#define MAX(a,b) ((a) > (b) ? (a) : (b))

/**
 * Basic limb type. Note that some calculations rely on unsigned overflow wrap-around of this type.
 * As a result, only unsigned types should be used here, and the RADIX, HALFRADIX above should be
 * changed as necessary. Unsigned integer should probably be the most efficient word type, and this
 * is used by GMP for example.
 */
typedef unsigned int word;

/**
 * Structure for representing multiple precision integers. This is a base "word" LSB
 * representation. In this case the base, word, is 2^32. Length is the number of words
 * in the current representation. Length should not allow for trailing zeros (Things like
 * 000124). The capacity is the number of words allocated for the limb data.
 */
typedef struct _bignum {
    int length;
    int capacity;
    word* data;
} bignum;

/**
 * Some forward delcarations as this was requested to be a single file.
 * See specific functions for explanations.
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
void bignum_inverse(bignum* a, bignum* m, bignum* result);//计算a的逆元result = a^-1 mod m
int bignum_jacobi(bignum* ac, bignum* nc);//计算雅可比符号 J（ac，nc）
int solovayPrime(int a, bignum* n);//验证a是否是n的一个欧拉函数 如果是的，则满足a^(n - 1)/2 != Ja(a, n) mod n
int probablePrime(bignum* n, int k) ;//验证n是否是一个素数
void randPrime(int numDigits, bignum* result) ;//随机生成一个素数
void randExponent(bignum* phi, int n, bignum* result);
int readFile(FILE* fd, char** buffer, int bytes);
void encode(bignum* m, bignum* e, bignum* n, bignum* result);
void decode(bignum* c, bignum* d, bignum* n, bignum* result);
bignum *encodeMessage(int len, int bytes, char *message, bignum *exponent, bignum *modulus);
int *decodeMessage(int len, int bytes, bignum *cryptogram, bignum *exponent, bignum *modulus);

/**
 * Save some frequently used bigintegers (0 - 10) so they do not need to be repeatedly
 * created. Used as, NUMS[5] = bignum("5"), etc..
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

