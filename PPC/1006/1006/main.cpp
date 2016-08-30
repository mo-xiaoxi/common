//
//  main.cpp
//  1006
//
//  Created by moxiaoxi on 16/8/29.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
bool Isrun(int year){
    if (year%4==0) {
        if(year%100==0&&year%400!=0){
            return false;
        }
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    string week[7]={"Saturday","Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    int year[2]={365,366};
    int month[2][12]={31, 28, 31, 30, 31, 30, 31, 31, 30,31, 30, 31,
                      31, 29, 31, 30, 31, 30, 31, 31, 30,31, 30, 31};
    int num;
    int dayofweek;
    int i,j;
    while (cin>>num&&num!=-1) {
        dayofweek=num%7;
        num++;
        for (i=2000; num>year[Isrun(i)]; i++) {
            num-=year[Isrun(i)];
        }
        for (j=0; num>month[Isrun(i)][j]; j++) {
            num-=month[Isrun(i)][j];
        }
        cout<<i<<'-';
        cout<<setw(2)<<setfill('0')<<j+1<<'-'<<setw(2)<<setfill('0')<<num<<' ';
        cout<<week[dayofweek]<<endl;
    }
    return 0;
}
