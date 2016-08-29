//
//  main.cpp
//  1055
//
//  Created by moxiaoxi on 16/8/24.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    string  temp;
    cin>>temp;
    string test;
    int len=temp.length();
    for(int i = 0;i <len/2 ;i++)
    {
        test[0] = temp[i];
        temp[i]=temp[len-1-i];
        temp[len-1-i] = test[0];
    }
    cout<<temp<<endl;

    
    return 0;
}
