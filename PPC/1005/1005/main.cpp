//
//  main.cpp
//  1005
//
//  Created by moxiaoxi on 16/8/29.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    string origin;
    int flag,n;
    vector<string> str1,str2;
    cin>>origin;
    cin>>flag>>n;
    string tmp;
    for(int i =0;i<n;i++) {
        cin>>tmp;
        str1.push_back(tmp);
        str2.push_back(tmp);
    }
    if (!flag) {
        transform(origin.begin(), origin.end(), origin.begin(), ::toupper);
        for(int i=0;i<str1.size();i++){
            transform(str1[i].begin(), str1[i].end(), str1[i].begin(), ::toupper);
        }
    }
    for (int i =0; i<str1.size(); i++) {
        if(str1[i].find(origin)!=string::npos){
            cout<<str2[i]<<endl;
        }
    }
    
    return 0;
}
