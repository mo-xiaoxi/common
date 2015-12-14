//
//  main.c
//  prime
//
//  Created by moxiaoxi on 15/12/10.
//  Copyright © 2015年 moxiaoxi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "Header.h"

int main(int argc, const char * argv[]) {
    unsigned long num,len,j,count;
    FILE *fp;
    bignum *p = bignum_init();
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
    fscanf(fp,"%ld",&num);
//    printf("num=%ld\n",num);
    fgetc(fp);
    count=0;
    for(j=0;j<num;j++)
    {
        char *buffer=(char*)malloc(BUF_SIZE*sizeof(char));
        if (fgets(buffer,BUF_SIZE,fp) ==NULL)  break; //这里没有考虑一行数字超过buf_size的情况！ 若需要，则修正
        len=strlen(buffer);//buffer中保存了回车
        if(buffer[len-1]=='\n') --len;//回车去除
        buffer[len]='\0';
//        printf("len=%ld\n",len);
//        printf("%ld=%s\n",j,buffer);/*输出获取到的数据 */
        bignum_fromstring(p, buffer);
//        bignum_print(p);
//        printf("\n");
        if(probablePrime(p, ACCURACY))//如果概率上p是素数，则显示出来  这里运用Solovay-Strassen素数检验法
        {
            bignum_print(p);
            printf("\n");
            ++count;
        }
        bignum_reset(p);
        free(buffer);
    }
    printf("count=%ld",count);
    bignum_deinit(p);
    return 0;

}

//初始化函数
bignum* bignum_init() {
    bignum* b = malloc(sizeof(bignum));
    b->length = 0;
    b->capacity = BIGNUM_CAPACITY;
    b->data = calloc(BIGNUM_CAPACITY, sizeof(word));//在内存的动态分配BIGNUM_CAPACITY个word空间
    return b;
}

//回收函数 释放空间
void bignum_deinit(bignum* b){
    free(b);
    free(b->data);
    return;
}
//重置p为初始值
void  bignum_reset(bignum* p) {
    p->length=0;
    p->capacity = BIGNUM_CAPACITY;
    memset(p->data, 0, BIGNUM_CAPACITY*sizeof(word));
    return;
}
//print函数
void bignum_print(bignum* b) {
    int cap = 100, len = 0, i;
    char* buffer = malloc(cap * sizeof(char));
    bignum *copy = bignum_init(), *remainder = bignum_init();
    if(b->length == 0 || bignum_iszero(b)) printf("0");
    else {
        bignum_copy(b, copy);
        while(bignum_isnonzero(copy)) {
            bignum_idivider(copy, &NUMS[10], remainder);
            buffer[len++] = remainder->data[0];
            if(len >= cap) {//如果长度不够
                cap *= 2;
                buffer = realloc(buffer, cap * sizeof(char));
            }
        }
            for(i = len - 1; i >= 0; i--) printf("%d", buffer[i]);
    }
    bignum_deinit(copy);
    bignum_deinit(remainder);
    free(buffer);
    return;
}

//用num来设置b
void bignum_fromint(bignum* b, unsigned int num) {
    b->length = 1;
    if(b->capacity < b->length) {
        b->capacity = b->length;
        b->data = realloc(b->data, b->capacity * sizeof(word));
    }
    b->data[0] = num;
}



//通过string来设置大数
void bignum_fromstring(bignum* b, char* string) {
    int i, len = 0;
    while(string[len] != '\0') len++;/* 找到string的长度 */
    for(i = 0; i < len; i++) {
        if(i != 0)
            bignum_imultiply(b, &NUMS[10]); /* 10进制转化 */
        bignum_iadd(b, &NUMS[string[i] - '0']); /* 相加 */
    }
    return;
}

//复制
void bignum_copy(bignum* source, bignum* dest){
    dest->length = source->length;
    if(source->capacity > dest->capacity) {
        dest->capacity = source->capacity;
        dest->data = realloc(dest->data, dest->capacity * sizeof(word));
    }
    memcpy(dest->data, source->data, dest->length * sizeof(word));
}
/******************************************************************
 定义各类比较函数
 ******************************************************************/
//判断b是否0，为0则返回1
int bignum_iszero(bignum* b) {
    return b->length == 0 || (b->length == 1 && b->data[0] == 0);
}

//if not ,return 1
int bignum_isnonzero(bignum* b) {
    return !bignum_iszero(b);
    
}

//检查b1是否小于b2
int bignum_less(bignum* b1, bignum* b2) {
    int i;
    if(bignum_iszero(b1) && bignum_iszero(b2)) return 0;
    else if(bignum_iszero(b1)) return 1;
    else if(bignum_iszero(b2)) return 0;
    else if(b1->length != b2->length) return b1->length < b2->length;
    for(i = b1->length - 1; i >= 0; i--) {
        if(b1->data[i] != b2->data[i]) return b1->data[i] < b2->data[i];
    }
    return 0;
}

/**
 *验证b1是否大于b2
 */
int bignum_greater(bignum* b1, bignum* b2) {
    int i;
    if(bignum_iszero(b1) && bignum_iszero(b2)) return 0;
    else if(bignum_iszero(b1)) return 0;
    else if(bignum_iszero(b2)) return 1;
    else if(b1->length != b2->length) return b1->length > b2->length;
    for(i = b1->length - 1; i >= 0; i--) {
        if(b1->data[i] != b2->data[i]) return b1->data[i] > b2->data[i];
    }
    return 0;
}

//验证b1<=b2
int bignum_leq(bignum* b1, bignum* b2) {
    return !bignum_greater(b1, b2);
}

//验证b1与b2是否相等
int bignum_equal(bignum* b1, bignum* b2) {
    int i;
    if(bignum_iszero(b1) && bignum_iszero(b2)) return 1;
    else if(bignum_iszero(b1)) return 0;
    else if(bignum_iszero(b2)) return 0;
    else if(b1->length != b2->length) return 0;
    for(i = b1->length - 1; i >= 0; i--) {
        if(b1->data[i] != b2->data[i]) return 0;
    }
    return 1;
}

/******************************************************************
 定义各类加减乘除函数
 ******************************************************************/

//source += add

void bignum_iadd(bignum* source, bignum* add) {
    bignum* temp = bignum_init();
    bignum_add(temp, source, add);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

/**
 * result = b1 + b2
 */
void bignum_add(bignum* result, bignum* b1, bignum* b2) {
    word sum, carry = 0;
    int i, n = MAX(b1->length, b2->length);
    if(n + 1 > result->capacity) {//如果和大于bignum当下能容忍的最大数，那么扩大capacity
        result->capacity = n + 1;
        result->data = realloc(result->data, result->capacity * sizeof(word));
    }
    for(i = 0; i < n; i++) {
        sum = carry;
        if(i < b1->length) sum += b1->data[i];
        if(i < b2->length) sum += b2->data[i];
        result->data[i] = sum; /* Already taken mod 2^32 by unsigned wrap around */
        //结果如果大于2^32,则溢出＝》进位
        if(i < b1->length) {
            if(sum < b1->data[i]) carry = 1; /* Result must have wrapped 2^32 so carry bit is 1 */
            else carry = 0;
        }
        else {
            if(sum < b2->data[i]) carry = 1; /* Result must have wrapped 2^32 so carry bit is 1 */
            else carry = 0;
        }
    }
    if(carry == 1) {
        result->length = n + 1;
        result->data[n] = 1;
    }
    else {
        result->length = n;
    }
}

//source-=sub
void bignum_isubtract(bignum* source, bignum* sub) {
    bignum* temp = bignum_init();
    bignum_subtract(temp, source, sub);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

//result=b1-b2
void bignum_subtract(bignum* result, bignum* b1, bignum* b2) {
    int length = 0, i;
    word carry = 0, diff, temp;
    if(b1->length > result->capacity) {
        result->capacity = b1->length;
        result->data = realloc(result->data, result->capacity * sizeof(word));
    }
    for(i = 0; i < b1->length; i++) {
        temp = carry;
        if(i < b2->length) temp = temp + b2->data[i]; /* Auto wrapped mod RADIX */
        diff = b1->data[i] - temp;
        if(temp > b1->data[i]) carry = 1;
        else carry = 0;
        result->data[i] = diff;
        if(result->data[i] != 0) length = i + 1;
    }
    result->length = length;
}


//自乘source *= mult
void bignum_imultiply(bignum* source, bignum* mult) {
    bignum* temp = bignum_init();
    bignum_multiply(temp, source, mult);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

//result = b1 * b2
void bignum_multiply(bignum* result, bignum* b1, bignum* b2) {
    int i, j, k;
    word carry, temp;
    unsigned long long int prod; /* Long for intermediate product... this is not portable and should probably be changed */
    if(b1->length + b2->length > result->capacity) {//如果结果超过，结果所能表达的最大数，则扩大结果范围
        result->capacity = b1->length + b2->length;
        result->data = realloc(result->data, result->capacity * sizeof(word));
    }
    for(i = 0; i < b1->length + b2->length; i++) result->data[i] = 0;
    
    for(i = 0; i < b1->length; i++) {
        for(j = 0; j < b2->length; j++) {
            prod = (b1->data[i] * (unsigned long long int)b2->data[j]) + (unsigned long long int)(result->data[i+j]); /*因为转化成long long来运算，所以该运算不会溢出 This should not overflow... */
            carry = (word)(prod / RADIX);
            
            /* Add carry to the next word over, but this may cause further overflow.. propogate 将溢出值加到下一个数中，但是 这可能造成再次溢出 比如在10进制中99+01 个位溢出进1到十位 然后10位也会溢出 */
            k = 1;
            while(carry > 0) {
                temp = result->data[i+j+k] + carry;
                if(temp < result->data[i+j+k]) carry = 1;
                else carry = 0;
                result->data[i+j+k] = temp; /* Already wrapped in unsigned arithmetic */
                k++;
            }
            
            prod = (result->data[i+j] + b1->data[i] * (unsigned long long int)b2->data[j]) % RADIX; /* Again, should not overflow... */
            result->data[i+j] = prod; /* Add */
        }
    }
    if(b1->length + b2->length > 0 && result->data[b1->length + b2->length - 1] == 0) result->length = b1->length + b2->length - 1;//结果最高位为0的状态
    else result->length = b1->length + b2->length;//最高位不为0
}

//source = source/div
void bignum_idivide(bignum *source, bignum *div) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, div);
    bignum_copy(q, source);
    bignum_deinit(q);
    bignum_deinit(r);
}

//source = source/div and remainder = source - source/div.
void bignum_idivider(bignum* source, bignum* div, bignum* remainder) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, div);
    bignum_copy(q, source);
    bignum_copy(r, remainder);
    bignum_deinit(q);
    bignum_deinit(r);
}

//商quotient = floor(b1/b2), 余数remainder = b1 - quotient * b2. If b1 < b2 ,quotient =0 and remainder = b2.
void bignum_divide(bignum* quotient, bignum* remainder, bignum* b1, bignum* b2) {
    bignum *b2copy = bignum_init(), *b1copy = bignum_init();
    bignum *temp = bignum_init(), *temp2 = bignum_init(), *temp3 = bignum_init();
    bignum* quottemp = bignum_init();
    word carry = 0;
    int n, m, i, j, length = 0;
    unsigned long long factor = 1;
    unsigned long long gquot, gtemp, grem;
    if(bignum_less(b1, b2)) { /* Trivial case, b1/b2 = 0 iff b1 < b2. */
        quotient->length = 0;
        bignum_copy(b1, remainder);
    }
    else if(bignum_iszero(b1)) { /* 0/x = 0.. assuming b2 is nonzero */
        quotient->length = 0;
        bignum_fromint(remainder, 0);
    }
    else if(b2->length == 1) { /* Division by a single limb means we can do simple division */
        if(quotient->capacity < b1->length) {
            quotient->capacity = b1->length;
            quotient->data = realloc(quotient->data, quotient->capacity * sizeof(word));
        }
        for(i = b1->length - 1; i >= 0; i--) {
            gtemp = carry * RADIX + b1->data[i];
            gquot = gtemp / b2->data[0];
            quotient->data[i] = gquot;
            if(quotient->data[i] != 0 && length == 0) length = i + 1;
            carry = gtemp % b2->data[0];
        }
        bignum_fromint(remainder, carry);
        quotient->length = length;
    }
    else { /* Long division is neccessary */
        n = b1->length + 1;
        m = b2->length;
        if(quotient->capacity < n - m) {
            quotient->capacity = n - m;
            quotient->data = realloc(quotient->data, (n - m) * sizeof(word));
        }
        bignum_copy(b1, b1copy);
        bignum_copy(b2, b2copy);
        /* Normalize.. multiply by the divisor by 2 until MSB >= HALFRADIX. This ensures fast
         * convergence when guessing the quotient below. We also multiply the dividend by the
         * same amount to ensure the result does not change. */
        while(b2copy->data[b2copy->length - 1] < HALFRADIX) {
            factor *= 2;
            bignum_imultiply(b2copy, &NUMS[2]);
        }
        if(factor > 1) {
            bignum_fromint(temp, factor);
            bignum_imultiply(b1copy, temp);
        }
        /* Ensure the dividend is longer than the original (pre-normalized) divisor. If it is not
         * we introduce a dummy zero word to artificially inflate it. */
        if(b1copy->length != n) {
            b1copy->length++;
            if(b1copy->length > b1copy->capacity) {
                b1copy->capacity = b1copy->length;
                b1copy->data = realloc(b1copy->data, b1copy->capacity * sizeof(word));
            }
            b1copy->data[n - 1] = 0;
        }
        
        /* Process quotient by long division */
        for(i = n - m - 1; i >= 0; i--) {
            gtemp = RADIX * b1copy->data[i + m] + b1copy->data[i + m - 1];
            gquot = gtemp / b2copy->data[m - 1];
            if(gquot >= RADIX) gquot = UINT_MAX;
            grem = gtemp % b2copy->data[m - 1];
            while(grem < RADIX && gquot * b2copy->data[m - 2] > RADIX * grem + b1copy->data[i + m - 2]) { /* Should not overflow... ? */
                gquot--;
                grem += b2copy->data[m - 1];
            }
            quottemp->data[0] = gquot % RADIX;
            quottemp->data[1] = (gquot / RADIX);
            if(quottemp->data[1] != 0) quottemp->length = 2;
            else quottemp->length = 1;
            bignum_multiply(temp2, b2copy, quottemp);
            if(m + 1 > temp3->capacity) {
                temp3->capacity = m + 1;
                temp3->data = realloc(temp3->data, temp3->capacity * sizeof(word));
            }
            temp3->length = 0;
            for(j = 0; j <= m; j++) {
                temp3->data[j] = b1copy->data[i + j];
                if(temp3->data[j] != 0) temp3->length = j + 1;
            }
            if(bignum_less(temp3, temp2)) {
                bignum_iadd(temp3, b2copy);
                gquot--;
            }
            bignum_isubtract(temp3, temp2);
            for(j = 0; j < temp3->length; j++) b1copy->data[i + j] = temp3->data[j];
            for(j = temp3->length; j <= m; j++) b1copy->data[i + j] = 0;
            quotient->data[i] = gquot;
            if(quotient->data[i] != 0) quotient->length = i;
        }
        
        if(quotient->data[b1->length - b2->length] == 0) quotient->length = b1->length - b2->length;
        else quotient->length = b1->length - b2->length + 1;
        
        /* Divide by factor now to find final remainder */
        carry = 0;
        for(i = b1copy->length - 1; i >= 0; i--) {
            gtemp = carry * RADIX + b1copy->data[i];
            b1copy->data[i] = gtemp/factor;
            if(b1copy->data[i] != 0 && length == 0) length = i + 1;
            carry = gtemp % factor;
        }
        b1copy->length = length;
        bignum_copy(b1copy, remainder);
    }
    bignum_deinit(temp);
    bignum_deinit(temp2);
    bignum_deinit(temp3);
    bignum_deinit(b1copy);
    bignum_deinit(b2copy);
    bignum_deinit(quottemp);
}
/**
 * 计算余数 remainder
 */
void bignum_remainder(bignum* source, bignum *div, bignum* remainder) {
    bignum *q = bignum_init();
    bignum_divide(q, remainder, source, div);
    bignum_deinit(q);
}


/**
 * 模运算 source = source % modulus
 */
void bignum_imodulate(bignum* source, bignum* modulus) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, modulus);
    bignum_copy(r, source);
    bignum_deinit(q);
    bignum_deinit(r);
}

/**
 * result = base^exponent mod modulus
 */
void bignum_modpow(bignum* base, bignum* exponent, bignum* modulus, bignum* result) {
    bignum *a = bignum_init(), *b = bignum_init(), *c = bignum_init();
    bignum *discard = bignum_init(), *remainder = bignum_init();
    bignum_copy(base, a);
    bignum_copy(exponent, b);
    bignum_copy(modulus, c);
    bignum_fromint(result, 1);
    while(bignum_greater(b, &NUMS[0])) {
        if(b->data[0] & 1) {
            bignum_imultiply(result, a);
            bignum_imodulate(result, c);
        }
        bignum_idivide(b, &NUMS[2]);
        bignum_copy(a, discard);
        bignum_imultiply(a, discard);
        bignum_imodulate(a, c);
    }
    bignum_deinit(a);
    bignum_deinit(b);
    bignum_deinit(c);
    bignum_deinit(discard);
    bignum_deinit(remainder);
}

/******************************************************************
 判定素数具体函数
 ******************************************************************/
/*从概率上验证n是否是一个素数
 Solovay-Strassen素数检验法
 1.随机生成1<=a<=N的整数a
 2.若（a，n）＝1且（a／n）＝a^(n-1)/2(mod n) 则输出n为素数，否则为合数
 */
int probablePrime(bignum* n, int k) {
    if(bignum_equal(n, &NUMS[2])) return 1;//为2 为素数
    else if(n->data[0] % 2 == 0 || bignum_equal(n, &NUMS[1])) return 0;//偶数和1 不为素数
    while(k-- > 0) {
        if(n->length <= 1) { /* Prevent a > n */
            if(!solovayPrime(rand() % (n->data[0] - 2) + 2, n)) return 0;
        }
        else {
            int wit = rand() % (RAND_MAX - 2) + 2;
            if(!solovayPrime(wit, n)) return 0;
        }
    }
    return 1;
}

/**
 *
 确认a是不是与n互质 如果互质，则a^(n - 1)/2 != Ja(a, n) mod n
 */
int solovayPrime(int a, bignum* n) {
    bignum *ab = bignum_init(), *res = bignum_init(), *pow = bignum_init();
    bignum *modpow = bignum_init();
    int x, result;
    
    bignum_fromint(ab, a);
    x = bignum_jacobi(ab, n);
    if(x == -1) bignum_subtract(res, n, &NUMS[1]);
    else bignum_fromint(res, x);
    bignum_copy(n, pow);
    bignum_isubtract(pow, &NUMS[1]);
    bignum_idivide(pow, &NUMS[2]);
    bignum_modpow(ab, pow, n, modpow);
    
    result = !bignum_equal(res, &NUMS[0]) && bignum_equal(modpow, res);
    bignum_deinit(ab);
    bignum_deinit(res);
    bignum_deinit(pow);
    bignum_deinit(modpow);
    return result;
}

/**
 *计算雅可比符号 J（ac，nc
 */
int bignum_jacobi(bignum* ac, bignum* nc) {
    bignum *remainder = bignum_init(), *twos = bignum_init();
    bignum *temp = bignum_init(), *a = bignum_init(), *n = bignum_init();
    int mult = 1, result = 0;
    bignum_copy(ac, a);
    bignum_copy(nc, n);
    while(bignum_greater(a, &NUMS[1]) && !bignum_equal(a, n)) {
        bignum_imodulate(a, n);
        if(bignum_leq(a, &NUMS[1]) || bignum_equal(a, n)) break;
        bignum_fromint(twos, 0);
        /* Factor out multiples of two */
        while(a->data[0] % 2 == 0) {
            bignum_iadd(twos, &NUMS[1]);
            bignum_idivide(a, &NUMS[2]);
        }
        /* Coefficient for flipping */
        if(bignum_greater(twos, &NUMS[0]) && twos->data[0] % 2 == 1) {
            bignum_remainder(n, &NUMS[8], remainder);
            if(!bignum_equal(remainder, &NUMS[1]) && !bignum_equal(remainder, &NUMS[7])) {
                mult *= -1;
            }
        }
        if(bignum_leq(a, &NUMS[1]) || bignum_equal(a, n)) break;
        bignum_remainder(n, &NUMS[4], remainder);
        bignum_remainder(a, &NUMS[4], temp);
        if(!bignum_equal(remainder, &NUMS[1]) && !bignum_equal(temp, &NUMS[1])) mult *= -1;
        bignum_copy(a, temp);
        bignum_copy(n, a);
        bignum_copy(temp, n);
    }
    if(bignum_equal(a, &NUMS[1])) result = mult;
    else result = 0;
    bignum_deinit(remainder);
    bignum_deinit(twos);
    bignum_deinit(temp);
    bignum_deinit(a);
    bignum_deinit(n);
    return result;
}
