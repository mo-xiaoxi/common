//
//  main.cpp
//  1011
//
//  Created by moxiaoxi on 16/8/31.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node{
    int x;
    int y;
};
bool compare(node a, node b){
    return a.x>b.x;
}

int main(int argc, const char * argv[]) {
    vector<node> TestMap;
    node temp;
    int n,m,flag;
    while (cin>>n>>m) {
        if (n==0&&m==0) {
            break;
        }
        flag=-1;
        for (int i=0; i<TestMap.size(); i++) {
            if (TestMap[i].x==n) {
                flag=i;
            }
        }
        if (flag==-1) {
            temp.x=n;
            temp.y=m;
            TestMap.push_back(temp);
        }else{
            TestMap[flag].y+=m;
        }
    }
    while (cin>>n>>m) {
        if (n==0&&m==0) {
            break;
        }
        flag=-1;
        for (int i=0; i<TestMap.size(); i++) {
            if (TestMap[i].x==n) {
                flag=i;
            }
        }
        if (flag==-1) {
            temp.x=n;
            temp.y=m;
            TestMap.push_back(temp);
        }else{
            TestMap[flag].y+=m;
        }
    }
    sort(TestMap.begin(), TestMap.end(),compare);
    for (int i =0; i<TestMap.size(); i++) {
        cout<<TestMap[i].x<<' '<<TestMap[i].y<<endl;
    }
    return 0;
}
