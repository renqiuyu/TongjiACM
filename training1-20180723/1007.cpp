//
// Created by renqiuyu on 2018/7/23.
//
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <numeric>

using namespace std;


int a[1005];
int getsum(int n) {
    return accumulate(a + 1, a + n + 1, 0);

}
int main(){
    a[1] = 1;
    a[2] = 1;
    for(int i = 3; i < 1005; i++) {
        a[i] = a[i-a[i-1]] + a[i-1-a[i-2]];
    }
    for(int i = 2; i <= 1000; i++) {
        cout << a[i] - a[i-1] << endl;
    }
    return 0;
}

