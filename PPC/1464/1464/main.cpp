//
//  main.cpp
//  1464
//
//  Created by moxiaoxi on 16/8/18.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main() {
    string temp;
    while(cin>>temp)
    {
        int len = temp.length();
        int num1 = (len+2)/3;
        int num2 = len-2*num1;
        int i,j=len-1;
        for(i= 0;i<num1-1;i++)
        {
            cout<<temp[i];
            for(int k=0;k<num2;k++)
                cout<<" ";
            cout<<temp[j--]<<endl;
            
        }
        for(;i<=j;i++)
            cout<<temp[i];
        cout<<endl;
    }
    return 0;
}
