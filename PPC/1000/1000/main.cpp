//
//  main.cpp
//  1000
//
//  Created by moxiaoxi on 16/8/28.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
#include <string.h>
using namespace std;
int main(int argc, const char * argv[]) {
    int line;
    cin>>line;
    int **raw = new int*[line];
    for(int i=0;i<line;i++){
        raw[i]=new int [line];
        memset(raw[i], 0, sizeof(int)*line*line);
    }
    int **flag = new int*[line];
    for(int i=0;i<line;i++){
        flag[i]=new int [line];
        memset(flag[i], 0, sizeof(int)*line*line);
    }
    int **sum = new int*[line];
    for(int i=0;i<line;i++){
        sum[i]=new int [line];
        memset(sum[i], 0, sizeof(int)*line*line);
    }
//    int raw[100][100]={0};
//    int sum[100][100]={0};
//    int flag[100][100]={0};
    for(int i=0;i<line;i++)
        for(int j=0;j<i+1;j++)
        {
            cin>>raw[i][j];
        }
    //    cout<<"raw[][]"<<endl;
    //    for(int i =0;i<line;i++){
    //    for(int j=0;j<line;j++){
    //        cout<<raw[i][j]<<'\t';
    //    }
    //        cout<<endl;
    //    }
    for (int i=0; i<line; i++) {
        sum[line-1][i] = raw[line-1][i];
        flag[line-1][i]=i;//flag用来纪录路径，自底向上
        /*
         0 0 0 0 0
         0 1 1 1 1
         0 1 1 2 2
         0 1 2 3 3
         0 1 2 3 4
         一个竖行代表一条路
         */
    }
    for(int i=line-2;i>=0;i--){
        for(int j=0;j<=i;j++){
            if(raw[i][j]+sum[i+1][j]>raw[i][j]+sum[i+1][j+1]){
                sum[i][j]=raw[i][j]+sum[i+1][j];
                flag[i][j]=j;
            }else{
                sum[i][j]=raw[i][j]+sum[i+1][j+1];
                flag[i][j]=j+1;
            }
        }
    }
    //    cout<<"raw[][]"<<endl;
    //    for(int i= 0;i<line;i++){
    //        for(int j=0;j<line;j++){
    //            cout<<raw[i][j]<<'\t';
    //        }
    //        cout<<endl;
    //    }
    //    cout<<"flag[][]"<<endl;
    //    for(int i= 0;i<line;i++){
    //        for(int j=0;j<line;j++){
    //            cout<<flag[i][j]<<'\t';
    //        }
    //        cout<<endl;
    //    }
    //    cout<<"sum[][]"<<endl;
    //    for(int i= 0;i<line;i++){
    //        for(int j=0;j<line;j++){
    //            cout<<sum[i][j]<<'\t';
    //        }
    //        cout<<endl;
    //    }
    cout<<sum[0][0]<<endl;
    cout<<raw[0][0]<<' ';
    int temp = flag[0][0];
    for (int i =1; i<line; i++) {
        cout<<raw[i][temp]<<' ';
        temp=flag[i][temp];
    }
    for(int i=0;i<line;i++){
        delete [] raw[i];
        delete [] sum[i];
        delete [] flag[i];
    }
    delete [] raw;
    delete [] sum;
    delete [] flag;
    return 0;
}
