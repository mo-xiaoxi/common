//
//  main.cpp
//  1007
//
//  Created by moxiaoxi on 16/8/30.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
int main(){
    int p,e,i,d,n=0;
    while(cin>>p>>e>>i>>d){
        n=n+1;
        if(p==-1&&e==-1&&i==-1&&d==-1) break;
        p=p%23;
        e=e%28;
        i=i%33;
        while(i<=d){
            i=i+33;
        }
        while(true){
            if ( ( (i - p) % 23 == 0 ) && ( (i - e) % 28 == 0 ) ) break;
            else{
                i=i+33;
            }
        }
        cout << "Case " << n << ": the next triple peak occurs in " << i - d << " days." << endl;
    }
    return 0;
}

