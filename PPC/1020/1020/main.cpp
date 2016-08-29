//
//  main.cpp
//  1020
//
//  Created by moxiaoxi on 16/8/24.
//  Copyright © 2016年 moxiaoxi. All rights reserved.
//

#include <iostream>
using namespace std;
struct rectangle{
    int x;
    int y;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    int i,j;

    rectangle end1;

    rectangle end2;

    while(true){
        cin>>i>>j;
        if (i==0&&j==0) {
            break;
        }
        end1.x=i;
        end1.y=j;
        end2.x=i;
        end2.y=j;
        while(true){
            cin>>i>>j;
            if (i==0&&j==0) {
                cout<<end1.x<<' '<<end1.y<<' '<<end2.x<<' '<<end2.y<<endl;
                break;
            }
            if (i< end1.x) {
                end1.x = i;
            }
            if (i > end2.x) {
                end2.x = i;
            }
            if (j < end1.y) {
                end1.y = j;
            }
            if (j > end2.y) {
                end2.y = j;
            }
        }
        
    }
    return 0;
}
