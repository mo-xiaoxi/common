//
//  main.cpp
//  1004
//
//  Created by moxiaoxi on 16/8/29.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
//涂色问题
struct rec{
    int x1;
    int y1;
    int x2;
    int y2;
};
int main(int argc, const char * argv[]) {
    rec test;
    int n;
    int flag[100][100]={0};
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>test.x1>>test.y1>>test.x2>>test.y2;
        for(int j=test.x1;j<test.x2;j++)
            for(int k=test.y1;k<test.y2;k++){
                flag[j][k]=1;
            }
    }
    int count=0;
    for (int i=0; i<100; i++)
        for (int j=0;j<100;j++){
            if (flag[i][j]==1) {
                count++;
            }
    }
    cout<<count;
    return 0;
}
