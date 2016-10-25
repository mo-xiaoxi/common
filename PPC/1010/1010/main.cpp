//
//  main.cpp
//  1010
//
//  Created by moxiaoxi on 16/8/31.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    int code[18];
    int w[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    int crc[]={1,0,10/*X*/,9,8,7,6,5,4,3,2};
    int S,Y;
    char temp;
    while (true) {
    int i=0;
    while (cin>>temp) {
        if (temp=='-') {
            break;
        }
        if (temp=='X') {
            temp=10;
        }else{
            temp=temp-'0';
        }
        code[i]=(int)temp;
        i++;
        if (i==18) {
            break;
        }
    }
        if (temp=='-') {
            break;
        }
        S=0;
        for(int i =0;i<17;i++){
            S+=w[i]*code[i];
        }
        Y=S%11;
        if (crc[Y]==code[17]) {
            cout<<1<<endl;
        }else{
            cout<<0<<endl;
        }
    }
    return 0;
}
