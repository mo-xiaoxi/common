//
//  main.cpp
//  maxnum
//
//  Created by moxiaoxi on 16/9/2.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, const char * argv[]) {
    int n;
    int *array = new int [n];
    memset(array, 0, n);
    int *p=NULL;
    int count;
    int maxcount=0;
    cin>>n;
    for(int i =0;i<n;i++){
        cin>>array[i];
    }
    for (int i =0; i<n; i++) {
        count=0;
        for (int j=0; j<n; j++) {
            if (array[i]==array[j]) {
                count++;
            }
        }
        if (count>maxcount) {
            maxcount=count;
            p=array+i;
        }else if (count==maxcount){
            if(array[i]<*p){
                p=array+i;
            }
        }
    }

    cout<<*p<<endl;
    delete [] array;
    return 0;
}
