//
//  main.cpp
//  1014
//
//  Created by moxiaoxi on 16/8/31.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;

void findrank(int *sort,int n){
    for (int i =0; i<n; i++)
        for (int j =i+1;j<n;j++){
            if (sort[i]==sort[j]&&sort[i]!=-1&&sort[j]!=-1) {
                sort[j]=-1;
            }
    }
    for (int i =0 ; i<n; i++) {
        for (int j=i; j<n; j++) {
            if (sort[i]<sort[j]) {
                int temp = sort[j];
                sort[j]=sort[i];
                sort[i]=temp;
            }
        }
    }
    return ;
}

int main(int argc, const char * argv[]) {
    int num[100]={0};
    int sort[100]={0};
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        cin>>num[i];
    }
    for (int j=0; j<n; j++) {
        sort[j]=num[j];
    }
    findrank(sort, n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (num[i]==sort[j]) {
                cout<<j+1<<' ';
            }
        }
    }
    return 0;
}
