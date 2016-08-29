//
//  main.cpp
//  1002
//
//  Created by moxiaoxi on 16/8/29.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node{
    int num;
    int count;
};

bool large_count(const node &m1 ,const node &m2){
    if (m1.count == m2.count)
        return m1.num<m2.num;
    else
        return m1.count > m2.count;
}
int main(int argc, const char * argv[]) {
    int n;
    vector<node> test;
    cin>>n;
    node tmp;
    int temp;
    for(int i = 0; i < n;i++){
        cin>>temp;
        int j=0;
        for (; j< test.size(); j++) {
            if (temp==test[j].num) {
                test[j].count++;
                break;
            }
        }
        if(j==test.size()){
            tmp.num=temp;
            tmp.count=1;
            test.push_back(tmp);
        }
    }
//    cout<<"before:"<<endl;
//    for (int i =0; i<test.size(); i++) {
//        cout<<test[i].num<<'\t'<<test[i].count<<endl;
//    }
    sort(test.begin(), test.end(),large_count);
//    cout<<"after:"<<endl;
//    for (int i =0; i<test.size(); i++) {
//        cout<<test[i].num<<'\t'<<test[i].count<<endl;
//    }
    for (int i = 0; i<test.size();i++) {
        cout<<test[i].num<<' '<<test[i].count<<endl;
    }
    
    return 0;
}
