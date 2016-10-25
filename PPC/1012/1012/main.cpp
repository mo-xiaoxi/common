//
//  main.cpp
//  1012
//
//  Created by moxiaoxi on 16/8/31.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//


#include <iostream>
using namespace std;
bool contain(int m,int n){
    int i,j,s=0;
    string str[10] = {"123456","23","12457","12347","2367","13467","134567","123","1234567","123467"};
    int mlen = str[m].length();
    int nlen = str[n].length();
    int min = mlen<nlen?mlen:nlen;
    for(i=0;i<mlen;i++){
        for(j=0;j<nlen;j++){
            if(str[m][i]==str[n][j]) s++;
        }
    }
    if(s==min) return true;
    else return false;
}
int main(){
    
    int b[10],f,i;
    while(1){
        cin>>b[0];
        if(b[0]==-1) break;
        for(i=1;i<10;i++){
            cin>>b[i];
        }
        f=1;
        for(i=0;i<9;i++){
            if((contain(b[i],b[i+1]))==0){
                f=0;
                break;
            }
            
        }
        if(f==0) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    
    return 0;
}
