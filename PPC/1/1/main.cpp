//
//  main.cpp
//  1
//
//  Created by moxiaoxi on 16/9/19.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, const char * argv[]) {
    int array[10000];
    int n;
    while(cin>>n){

    for(int i =0;i<n;i++){
        cin>>array[i];
    }
    int max,min;
    max=*max_element(array,array+n);
    min = *min_element(array,array+n);
    cout<<max<<' '<<min<<endl;
    }
    return 0;
}
