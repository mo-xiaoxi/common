//
//  main.cpp
//  1003
//
//  Created by moxiaoxi on 16/8/29.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int, const char * argv[]) {
    int n;
    cin>>n;
    int array[1000]={0};
    int count=0;
    for (int i=0; i<n; i++) {
        cin>>array[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if ((array[i]-array[j])==1||(array[i]-array[j])==-1) {
                count++;
            }
        }
    }
    cout<<count;
    return 0;
}
