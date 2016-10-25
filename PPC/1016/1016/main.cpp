//
//  main.cpp
//  1016
//
//  Created by moxiaoxi on 16/9/2.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main(int argc, const char * argv[]) {
    string change[]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu","shi"};
    string input ;
    cin>>input;
    int  count =0;
    for (int i =0 ; i< input.size(); i++) {
        count+=input[i]-'0';
    }
    char output[30];
    int i,n,index;
    n=sprintf(output, "%d",count);
    for (i =0 ; i<n-1; i++) {
        index=output[i]-'0';
        cout<<change[index]<<' ';
    }
    index = output[i]-'0';
    cout<<change[index];
    return 0;
}
