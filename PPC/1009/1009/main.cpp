//
//  main.cpp
//  1009
//
//  Created by moxiaoxi on 16/8/30.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#define NUM 5

using namespace std;

void Caesar( string &str){
    char test=char('A'+NUM);
    for (int i =0 ; i<str.size(); i++) {
        if(str[i]<test&&str[i]>='A'){
            str[i]=str[i]-NUM+26;
        }
        else if(str[i]>=test&&str[i]<='Z'){
            str[i]=str[i]-NUM;
        }
    }
    return ;
}
int main(int argc, const char * argv[]) {
    string str,start,end;
    while (getline(cin,start)) {
        if (start=="ENDOFINPUT") {
            break;
        }
        else if (start =="START") {
            getline(cin,str);
            getline(cin,end);
            Caesar(str);
            cout<<str<<endl;
        }
    }
    Caesar(str);
    return 0;
}
