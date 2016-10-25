//
//  main.cpp
//  1015
//
//  Created by moxiaoxi on 16/9/2.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(int argc, const char * argv[]) {
    string change[]={"(Zero)","(One)","(Two)","(Three)","(Four)","(Five)","(Six)","(Seven)","(Eight)","(Nine)"};
    string input;
    int count[10]={0};
    getline(cin,input);
    for (int i =0; i<input.size(); i++) {
        if (input[i]>='0'&&input[i]<='9') {
            int index = input[i]-'0';
            cout<<change[index];
            count[index]++;
        }else{
            cout<<input[i];
        }
    }
    cout<<endl;
    for (int i =0; i<10; i++) {
        cout<<count[i]<<' ';
    }
    return 0;
}
