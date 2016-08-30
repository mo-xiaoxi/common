//
//  main.cpp
//  1008
//
//  Created by moxiaoxi on 16/8/30.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {

    int m,n;
    while (cin>>n>>m) {
        if (n==0&&m==0) {
            break;
        }
        int round[300]={0};
        for (int i=0; i<n; i++) {
            round[i]=1;
        }
        int count=n;
        int index=0;
        while (count>1) {
        for(int i =0; i <n;i++){
            if (round[i]==1) {
                index++;
                if (index%m==0) {
                    round[i]=0;
                    count--;
                }
            }
        }
        }
        for (int i =0; i<n; i++) {
            if (round[i]==1) {
                cout<<i+1<<endl;
            }
        }
    }
    return 0;
}
