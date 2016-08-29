//
//  main.cpp
//  1001
//
//  Created by moxiaoxi on 16/8/28.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    int n,m;
    cin>>n>>m;
    int **p = new int *[n];
    for(int i=0;i<n;i++){
        p[i] = new int [m];
    }
    for(int i = 0;i<n;i++){
        for(int j =0;j<m;j++){
            cin>>p[i][j];
        }
}
    for(int i =m-1;i>=0;i--){
        for(int j =0 ;j<n;j++){
            if(j!=n-1){
                cout<<p[j][i]<<' ';}
            else{
                cout<<p[j][i];
            }
        }
        cout<<endl;
    }
    return 0;
}
