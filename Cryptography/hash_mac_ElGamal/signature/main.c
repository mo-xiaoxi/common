//
//  main.c
//  prime
//
//  Created by lkz on 15/12/27.
//  Copyright © 2015年 lkz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "Header.h"

int main(int argc, const char * argv[]) {
    
    char *p=(char*)malloc(BUF_SIZE*sizeof(char));
    printf("\n请输入选择的大素数p：\n");
    scanf("%s",p);
    bignum *p1 = bignum_init();
    bignum_fromstring(p1, p);
    free(p);
    if(probablePrime(p1, ACCURACY))
    {
        printf("p合理");
        bignum *yz = bignum_init();
        bignum_fromint(yz, 3);
        if (bignum_equal(yz,p1)) {
            printf("但p太小不适用！\n");
            return 1;
        }
    }else{
        printf("p不是素数！\n");
        return 1;
    }
    bignum *p2 = bignum_init();
    bignum *temp = bignum_init();
    bignum_fromint(temp, 1);
    bignum_subtract(p2, p1, temp);
    printf("\n请输入选择的本原元α：\n");
    char *a=(char*)malloc(BUF_SIZE*sizeof(char));
    scanf("%s",a);
    bignum *a1 = bignum_init();
    bignum_fromstring(a1, a);
    free(a);
    printf("\n请输入选择的随机整数d：(2<=d<=p-2)\n");
    char *d=(char*)malloc(BUF_SIZE*sizeof(char));
    scanf("%s",d);
    bignum *d1 = bignum_init();
    bignum_fromstring(d1, d);
    free(d);
    bignum *yz0 = bignum_init();
    bignum_fromint(yz0, 2);
    bignum *yz1 = bignum_init();
    bignum_subtract(yz1, p1, yz0);
    if( (bignum_greater(d1, yz0)||bignum_equal(d1, yz0))&&(bignum_greater(yz1,d1)||bignum_equal(yz1,d1)) )
    {
        printf("d合理");
    }else{
        printf("d不合要求！\n");
        return 1;
    }
    printf("\n请输入您的消息x：\n");
    char *x=(char*)malloc(BUF_SIZE*sizeof(char));
    scanf("%s",x);
    bignum *x1 = bignum_init();
    bignum_fromstring(x1, x);
    free(x);
    printf("\n请输入您选择的k：（2<=k<=p-2且k应与p-1互质）\n");
    char *k=(char*)malloc(BUF_SIZE*sizeof(char));
    scanf("%s",k);
    bignum *k1 = bignum_init();
    bignum_fromstring(k1, k);
    free(k);
    if( (bignum_greater(k1, yz0)||bignum_equal(k1, yz0))&&(bignum_greater(yz1,k1)||bignum_equal(yz1,k1)) )
    {
        bignum *yz2 = bignum_init();
        bignum_gcd(k1, p2, yz2);
        if (!bignum_equal(yz2,temp)) {
            printf("k不合要求！\n");
            return 1;
        }
        printf("k合理");
    }else{
        printf("k不合要求！\n");
        return 1;
    }
    
    
    
    bignum *b1 = bignum_init();
    bignum_modpow(a1,d1,p1,b1);
    printf("\n\n所以\n您生成的公钥（p,α,β）为：\t(");
    bignum_print(p1);
    printf(",");
    bignum_print(a1);
    printf(",");
    bignum_print(b1);
    printf(")\n");
    
    printf("您的私钥为：");
    bignum_print(d1);
    printf("\n");
    printf("您发出的消息(x(r,s))为：\t(");
    bignum_print(x1);
    printf(",(");
    bignum *r1 = bignum_init();
    bignum_modpow(a1,k1,p1,r1);
    bignum_print(r1);
    printf(",");
    bignum *s1=bignum_init();
    bignum_multiply(temp, d1, r1);
    
    bignum *temp2 = bignum_init();
    bignum *x2 = bignum_init();
    bignum_copy(x1, x2);
    while (bignum_less(x2, temp)) {
        bignum *add = bignum_init();
        bignum_copy(p2, add);
        bignum_iadd(x2, add) ;
    }
    bignum_subtract(temp2, x2, temp);
//    printf("\ntemp2:");
//    bignum_print(temp2);
//    printf("\t");
//    bignum_print(x2);
//    printf("\t");
//    bignum_print(temp);
//    printf("\n");
    bignum_inverse(k1, p2, temp);//计算a的逆元result = a^-1 mod m
    bignum_multiply(s1, temp, temp2);
    bignum_imodulate(s1, p2);//source = source % modulus
    bignum_print(s1);
    printf("))\n");
    
    bignum *t0 = bignum_init();
    bignum_modpow(a1,x1,p1,t0);
    bignum *t1 = bignum_init();
    bignum_modpow(b1,r1,p1,t1);
    bignum *t2 = bignum_init();
    bignum_modpow(r1,s1,p1,t2);
    bignum *t3 = bignum_init();
    bignum_multiply(t3, t1, t2);
    bignum_imodulate(t3, p1);
    printf("按t=(α^x)mod p，结果为：");
    bignum_print(t0);
    printf("\n按t=(β^r*r^s)mod p，结果为：");
    bignum_print(t3);
    printf("\n");
    if (bignum_equal(t0, t3)) {
        printf("此签名正确有效～\n\n");
    }else{
        printf("此签名错误无效！\n\n");
    }
}




//重置p为初始值
void  bignum_reset(bignum* p) {
    p->length=0;
    p->capacity = BIGNUM_CAPACITY;
    memset(p->data, 0, BIGNUM_CAPACITY*sizeof(word));
    return;
}

/**
 * Initialize a bignum structure. This is the only way to safely create a bignum
 * and should be called where-ever one is declared. (We realloc the memory in all
 * other cases which is technically safe but may cause problems when we go to free
 * it.) 初始化
 */
bignum* bignum_init() {
    bignum* b = malloc(sizeof(bignum));
    // bignum* b = calloc(1,sizeof(bignum));
    b->length = 0;
    b->capacity = BIGNUM_CAPACITY;
    b->data = calloc(BIGNUM_CAPACITY, sizeof(word));//在内存的动态分配BIGNUM_CAPACITY个word空间
    return b;
}

/**
 * Free resources used by a bignum. Use judiciously to avoid memory leaks.
 释放空间
 */
void bignum_deinit(bignum* b) {
    free(b->data);
    free(b);
}

/**
 * Check if the given bignum is zero
 */
int bignum_iszero(bignum* b) {
    return b->length == 0 || (b->length == 1 && b->data[0] == 0);
}

/**
 * Check if the given bignum is nonzero.
 */
int bignum_isnonzero(bignum* b) {
    return !bignum_iszero(b);
}

/**
 * Copy from source bignum into destination bignum.
 */
void bignum_copy(bignum* source, bignum* dest) {
    dest->length = source->length;
    if(source->capacity > dest->capacity) {
        dest->capacity = source->capacity;
        dest->data = realloc(dest->data, dest->capacity * sizeof(word));
    }
    memcpy(dest->data, source->data, dest->length * sizeof(word));
}

/**
 * Load a bignum from a base 10 string. Only pure numeric strings will work.
 */
void bignum_fromstring(bignum* b, char* string) {
    int i, len = 0;
    while(string[len] != '\0') len++; /* Find string length */
    for(i = 0; i < len; i++) {
        if(i != 0) bignum_imultiply(b, &NUMS[10]); /* Base 10 multiply */
        bignum_iadd(b, &NUMS[string[i] - '0']); /* Add */
    }
}

/**
 * Load a bignum from an unsigned integer.
 */
void bignum_fromint(bignum* b, unsigned int num) {
    b->length = 1;
    if(b->capacity < b->length) {
        b->capacity = b->length;
        b->data = realloc(b->data, b->capacity * sizeof(word));
    }
    b->data[0] = num;
}

/**
 * Print a bignum to stdout as base 10 integer. This is done by
 * repeated division by 10. We can make it more efficient by dividing by
 * 10^9 for example, then doing single precision arithmetic to retrieve the
 * 9 remainders
 */
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
            if(len >= cap) {
                cap *= 2;
                buffer = realloc(buffer, cap * sizeof(char));
            }
        }
        for(i = len - 1; i >= 0; i--) printf("%d", buffer[i]);
    }
    bignum_deinit(copy);
    bignum_deinit(remainder);
    free(buffer);
}

/**
 * Check if two bignums are equal.
 */
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

/**
 * Check if bignum b1 is greater than b2
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

/**
 * Check if bignum b1 is less than b2
 */
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
 * Check if bignum b1 is greater than or equal to b2
 */
int bignum_geq(bignum* b1, bignum* b2) {
    return !bignum_less(b1, b2);
}

/**
 * Check if bignum b1 is less than or equal to b2
 */
int bignum_leq(bignum* b1, bignum* b2) {
    return !bignum_greater(b1, b2);
}

/**
 * Perform an in place add into the source bignum. That is source += add
 */
void bignum_iadd(bignum* source, bignum* add) {
    bignum* temp = bignum_init();
    bignum_add(temp, source, add);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

/**
 * Add two bignums by the add with carry method. result = b1 + b2
 */
void bignum_add(bignum* result, bignum* b1, bignum* b2) {
    word sum, carry = 0;
    int i, n = MAX(b1->length, b2->length);
    if(n + 1 > result->capacity) {
        result->capacity = n + 1;
        result->data = realloc(result->data, result->capacity * sizeof(word));
    }
    for(i = 0; i < n; i++) {
        sum = carry;
        if(i < b1->length) sum += b1->data[i];
        if(i < b2->length) sum += b2->data[i];
        result->data[i] = sum; /* Already taken mod 2^32 by unsigned wrap around */
        
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

/**
 * Perform an in place subtract from the source bignum. That is, source -= sub
 */
void bignum_isubtract(bignum* source, bignum* sub) {
    bignum* temp = bignum_init();
    bignum_subtract(temp, source, sub);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

/**
 * Subtract bignum b2 from b1. result = b1 - b2. The result is undefined if b2 > b1.
 * This uses the basic subtract with carry method
 */
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

/**
 * Perform an in place multiplication into the source bignum. That is source *= mult
 */
void bignum_imultiply(bignum* source, bignum* mult) {
    bignum* temp = bignum_init();
    bignum_multiply(temp, source, mult);
    bignum_copy(temp, source);
    bignum_deinit(temp);
}

/**
 * Multiply two bignums by the naive school method. result = b1 * b2. I have experimented
 * with FFT mult and Karatsuba but neither was looking to be  more efficient than the school
 * method for reasonable number of digits. There are some improvments to be made here,
 * especially for squaring which can cut out half of the operations.
 */
void bignum_multiply(bignum* result, bignum* b1, bignum* b2) {
    int i, j, k;
    word carry, temp;
    unsigned long long int prod; /* Long for intermediate product... this is not portable and should probably be changed */
    if(b1->length + b2->length > result->capacity) {
        result->capacity = b1->length + b2->length;
        result->data = realloc(result->data, result->capacity * sizeof(word));
    }
    for(i = 0; i < b1->length + b2->length; i++) result->data[i] = 0;
    
    for(i = 0; i < b1->length; i++) {
        for(j = 0; j < b2->length; j++) {
            prod = (b1->data[i] * (unsigned long long int)b2->data[j]) + (unsigned long long int)(result->data[i+j]); /* This should not overflow... */
            carry = (word)(prod / RADIX);
            
            /* Add carry to the next word over, but this may cause further overflow.. propogate */
            k = 1;
            while(carry > 0) {
                temp = result->data[i+j+k] + carry;
                if(temp < result->data[i+j+k]) carry = 1;
                else carry = 0;
                result->data[i+j+k] = temp; /* Already wrapped in unsigned arithmetic */
                k++;
            }
            
            prod = (result->data[i+j] + b1->data[i] * (unsigned long long int)b2->data[j]) % RADIX; /* Again, should not overflow... */
            result->data[i+j] = (unsigned)prod; /* Add */
        }
    }
    if(b1->length + b2->length > 0 && result->data[b1->length + b2->length - 1] == 0) result->length = b1->length + b2->length - 1;
    else result->length = b1->length + b2->length;
}

/**
 * Perform an in place divide of source. source = source/div.
 */
void bignum_idivide(bignum *source, bignum *div) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, div);
    bignum_copy(q, source);
    bignum_deinit(q);
    bignum_deinit(r);
}

/**
 * Perform an in place divide of source, also producing a remainder.
 * source = source/div and remainder = source - source/div.
 */
void bignum_idivider(bignum* source, bignum* div, bignum* remainder) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, div);
    bignum_copy(q, source);
    bignum_copy(r, remainder);
    bignum_deinit(q);
    bignum_deinit(r);
}

/**
 * Calculate the remainder when source is divided by div.
 */
void bignum_remainder(bignum* source, bignum *div, bignum* remainder) {
    bignum *q = bignum_init();
    bignum_divide(q, remainder, source, div);
    bignum_deinit(q);
}

/**
 * Modulate the source by the modulus. source = source % modulus
 */
void bignum_imodulate(bignum* source, bignum* modulus) {
    bignum *q = bignum_init(), *r = bignum_init();
    bignum_divide(q, r, source, modulus);
    bignum_copy(r, source);
    bignum_deinit(q);
    bignum_deinit(r);
}

/**
 * Divide two bignums by naive long division, producing both a quotient and remainder.
 * quotient = floor(b1/b2), remainder = b1 - quotient * b2. If b1 < b2 the quotient is
 * trivially 0 and remainder is b2.
 */
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
            quotient->data[i] = (unsigned)gquot;
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
            bignum_fromint(temp, (unsigned)factor);
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
            quottemp->data[0] = (unsigned)gquot % RADIX;
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
            quotient->data[i] = (unsigned)gquot;
            if(quotient->data[i] != 0) quotient->length = i;
        }
        
        if(quotient->data[b1->length - b2->length] == 0) quotient->length = b1->length - b2->length;
        else quotient->length = b1->length - b2->length + 1;
        
        /* Divide by factor now to find final remainder */
        carry = 0;
        for(i = b1copy->length - 1; i >= 0; i--) {
            gtemp = carry * RADIX + b1copy->data[i];
            b1copy->data[i] = (unsigned)gtemp/factor;
            if(b1copy->data[i] != 0 && length == 0) length = i + 1;
            carry = (unsigned)gtemp % factor;
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
 * Perform modular exponentiation by repeated squaring. This will compute
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

/**
 * Compute the gcd of two bignums. result = gcd(b1, b2)
 */
void bignum_gcd(bignum* b1, bignum* b2, bignum* result) {
    bignum *a = bignum_init(), *b = bignum_init(), *remainder = bignum_init();
    bignum *temp = bignum_init(), *discard = bignum_init();
    bignum_copy(b1, a);
    bignum_copy(b2, b);
    while(!bignum_equal(b, &NUMS[0])) {
        bignum_copy(b, temp);
        bignum_imodulate(a, b);
        bignum_copy(a, b);
        bignum_copy(temp, a);
    }
    bignum_copy(a, result);
    bignum_deinit(a);
    bignum_deinit(b);
    bignum_deinit(remainder);
    bignum_deinit(temp);
    bignum_deinit(discard);
}

/**
 * Compute the inverse of a mod m. Or, result = a^-1 mod m.
 */
void bignum_inverse(bignum* a, bignum* m, bignum* result) {
    bignum *remprev = bignum_init(), *rem = bignum_init();
    bignum *auxprev = bignum_init(), *aux = bignum_init();
    bignum *rcur = bignum_init(), *qcur = bignum_init(), *acur = bignum_init();
    
    bignum_copy(m, remprev);
    bignum_copy(a, rem);
    bignum_fromint(auxprev, 0);
    bignum_fromint(aux, 1);
    while(bignum_greater(rem, &NUMS[1])) {
        bignum_divide(qcur, rcur, remprev, rem);
        /* Observe we are finding the inverse in a finite field so we can use
         * a modified algorithm that avoids negative numbers here */
        bignum_subtract(acur, m, qcur);
        bignum_imultiply(acur, aux);
        bignum_iadd(acur, auxprev);
        bignum_imodulate(acur, m);
        
        bignum_copy(rem, remprev);
        bignum_copy(aux, auxprev);
        bignum_copy(rcur, rem);
        bignum_copy(acur, aux);
    }
    
    bignum_copy(acur, result);
    
    bignum_deinit(remprev);
    bignum_deinit(rem);
    bignum_deinit(auxprev);
    bignum_deinit(aux);
    bignum_deinit(rcur);
    bignum_deinit(qcur);
    bignum_deinit(acur);
}

/**
 * Compute the jacobi symbol, J(ac, nc).
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

/**
 * Check whether a is a Euler witness for n. That is, if a^(n - 1)/2 != Ja(a, n) mod n
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
 * Test if n is probably prime, by repeatedly using the Solovay-Strassen primality test.
 */
int probablePrime(bignum* n, int k) {
    if(bignum_equal(n, &NUMS[2])) return 1;
    else if(n->data[0] % 2 == 0 || bignum_equal(n, &NUMS[1])) return 0;
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
 * Generate a random prime number, with a specified number of digits.
 * This will generate a base 10 digit string of given length, convert it
 * to a bignum and then do an increasing search for the first probable prime.
 */
void randPrime(int numDigits, bignum* result) {
    char *string = malloc((numDigits + 1) * sizeof(char));
    int i;
    string[0] = (rand() % 9) + '1'; /* No leading zeros */
    string[numDigits - 1] = (rand() % 5) * 2 + '1'; /* Last digit is odd */
    for(i = 1; i < numDigits - 1; i++) string[i] = (rand() % 10) + '0';
    string[numDigits] = '\0';
    bignum_fromstring(result, string);
    while(1) {
        if(probablePrime(result, ACCURACY)) {
            free(string);
            return;
        }
        bignum_iadd(result, &NUMS[2]); /* result += 2 */
    }
}

/**
 * Choose a random public key exponent for the RSA algorithm. The exponent will
 * be less than the modulus, n, and coprime to phi.
 */
void randExponent(bignum* phi, int n, bignum* result) {
    bignum* gcd = bignum_init();
    int e = rand() % n;
    while(1) {
        bignum_fromint(result, e);
        bignum_gcd(result, phi, gcd);
        if(bignum_equal(gcd, &NUMS[1])) {
            bignum_deinit(gcd);
            return;
        }
        e = (e + 1) % n;
        if(e <= 2) e = 3;
    }
}

/**
 * Read the file fd into an array of bytes ready for encryption.
 * The array will be padded with zeros until it divides the number of
 * bytes encrypted per block. Returns the number of bytes read.
 */
int readFile(FILE* fd, char** buffer, int bytes) {
    int len = 0, cap = BUF_SIZE, r;
    char buf[BUF_SIZE];
    *buffer = malloc(BUF_SIZE * sizeof(char));
    while((r = (int)fread(buf, sizeof(char), BUF_SIZE, fd)) > 0) {
        if(len + r >= cap) {
            cap *= 2;
            *buffer = realloc(*buffer, cap);
        }
        memcpy(&(*buffer)[len], buf, r);
        len += r;
    }
    /* Pad the last block with zeros to signal end of cryptogram. An additional block is added if there is no room */
    if(len + bytes - len % bytes > cap) *buffer = realloc(*buffer, len + bytes - len % bytes);
    do {
        (*buffer)[len] = '\0';
        len++;
    }
    while(len % bytes != 0);
    return len;
}

/**
 * Encode the message m using public exponent and modulus, result = m^e mod n
 */
void encode(bignum* m, bignum* e, bignum* n, bignum* result) {
    bignum_modpow(m, e, n, result);
}

/**
 * Decode cryptogram c using private exponent and public modulus, result = c^d mod n
 */
void decode(bignum* c, bignum* d, bignum* n, bignum* result) {
    bignum_modpow(c, d, n, result);
}

/**
 * Encode the message of given length, using the public key (exponent, modulus)
 * The resulting array will be of size len/bytes, each index being the encryption
 * of "bytes" consecutive characters, given by m = (m1 + m2*128 + m3*128^2 + ..),
 * encoded = m^exponent mod modulus
 */
bignum *encodeMessage(int len, int bytes, char *message, bignum *exponent, bignum *modulus) {
    /* Calloc works here because capacity = 0 forces a realloc by callees but we should really
     * bignum_init() all of these */
    int i, j;
    bignum *encoded = calloc(len/bytes, sizeof(bignum));
    bignum *num128 = bignum_init(), *num128pow = bignum_init();
    bignum *x = bignum_init(), *current = bignum_init();
    bignum_fromint(num128, 128);
    bignum_fromint(num128pow, 1);
    for(i = 0; i < len; i += bytes) {
        bignum_fromint(x, 0);
        bignum_fromint(num128pow, 1);
        /* Compute buffer[0] + buffer[1]*128 + buffer[2]*128^2 etc (base 128 representation for characters->int encoding)*/
        for(j = 0; j < bytes; j++) {
            bignum_fromint(current, message[i + j]);
            bignum_imultiply(current, num128pow);
            bignum_iadd(x, current); /*x += buffer[i + j] * (1 << (7 * j)) */
            bignum_imultiply(num128pow, num128);
        }
        encode(x, exponent, modulus, &encoded[i/bytes]);
#ifndef NOPRINT
        bignum_print(&encoded[i/bytes]);
        printf(" ");
#endif
    }
    return encoded;
}

/**
 * Decode the cryptogram of given length, using the private key (exponent, modulus)
 * Each encrypted packet should represent "bytes" characters as per encodeMessage.
 * The returned message will be of size len * bytes.
 */
int *decodeMessage(int len, int bytes, bignum *cryptogram, bignum *exponent, bignum *modulus) {
    int *decoded = malloc(len * bytes * sizeof(int));
    int i, j;
    bignum *x = bignum_init(), *remainder = bignum_init();
    bignum *num128 = bignum_init();
    bignum_fromint(num128, 128);
    for(i = 0; i < len; i++) {
        decode(&cryptogram[i], exponent, modulus, x);
        for(j = 0; j < bytes; j++) {
            bignum_idivider(x, num128, remainder);
            if(remainder->length == 0) decoded[i*bytes + j] = (char)0;
            else decoded[i*bytes + j] = (char)(remainder->data[0]);
#ifndef NOPRINT
            printf("%c", (char)(decoded[i*bytes + j]));
#endif
        }
    }
    return decoded;
}


