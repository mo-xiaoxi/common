//
//  main.cpp
//  1013
//
//  Created by moxiaoxi on 16/8/31.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
bool compare(char a, char b){
    return a<b;
}
int main(int argc, const char * argv[]) {
    string origin;
    vector<char> output;
    getline(cin, origin);
    vector<char> input;
    for (int i =0 ; i< origin.length(); i++) {
        if (origin[i]>='A'&&origin[i]<='Z') {
            input.push_back(origin[i]);
        }
    }
//    for (int i = 0; i < input.size(); i++) {
//        cout<<input[i];
//    }
//    cout<<endl;
    sort(input.begin(),input.end() , compare);
//    for (int i = 0; i < input.size(); i++) {
//        cout<<input[i];
//    }
//    cout<<origin.length()<<endl;
    int j=0;
    for (int i =0 ; i< origin.length(); i++) {
        if (origin[i]>='A'&&origin[i]<='Z') {
            output.push_back(input[j++]);
        }
        else{
            output.push_back(origin[i]);
        }
    }
//    cout<<endl;
    for (int i =0 ; i< output.size(); i++) {
        cout<<output[i];
    }
    cout<<endl;
    return 0;
}
