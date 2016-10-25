//
//  main.cpp
//  interestnumber
//
//  Created by moxiaoxi on 16/9/2.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//
/*
 这里是用动态规划来求解
 对于第n位，可由上一个状态(n-1位)求解
 每个位上有6个状态
 0 - use 2  need 0 1 3
 1 - use 2,0 need 1 3
 2 - use 2,3 need 0 1
 3 - use 0,1,2 need 3
 4 - use 0,2,3 need 1
 5 - use 0,1,2,3
 */
#include <iostream>
using namespace std;
#define mod 1000000007
int main(int argc, const char * argv[]) {
    long long int n;
    long long int state[1000][6]={0};
    cin>>n;
    for (long long int i =1; i<=n; i++) {
        state[i][0]=1;
        state[i][1]=(state[i-1][0]+state[i-1][1]*2)%mod;
        state[i][2]=(state[i-1][0]+state[i-1][2])%mod;
        state[i][3]=(state[i-1][1]+state[i-1][3]*2)%mod;
        state[i][4]=(state[i-1][1]+state[i-1][2]+state[i-1][4]*2)%mod;
        state[i][5]=(state[i-1][3]+state[i-1][4]+state[i-1][5]*2)%mod;
    }
    cout<<state[n][5];
    return 0;
}
