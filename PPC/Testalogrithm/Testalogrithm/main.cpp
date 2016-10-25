//
//  main.cpp
//  Testalogrithm
//
//  Created by moxiaoxi on 16/9/2.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;
struct node {
    int x;
    int y;
};
bool compare(int a, int b){
    return a>b;
}
void  myfunction(int & a){
    ++a;
    return ;
}
int main(int argc, const char * argv[]) {
    int array[]={0,3,9,5,6,7,8,2,4,5};
    // min
    cout<<"min(1,2)"<<min(1, 2)<<endl;
    cout<<"min array"<<min(array[0],array[5],compare)<<endl;
    cout<<"max arrary"<<*max_element(array,array+9)<<endl;
    for (int i=0 ; i<10; i++) {
        cout<<i<<' '<<array[i]<<endl;
    }
    for_each(array,array+10,myfunction);
    for(int i =0 ;i<10;i++){
        cout<<i<<' '<<array[i]<<endl;
    }
    cout<<find(array, array+8, -1)<<endl;
    return 0;
}
