//
// Created by renqiuyu on 2018/7/27.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 100005;
char str[maxn];

struct node{
    int m, a,b;
    bool operator < (const node &rhs) const {
        if(b >= a && rhs.b < rhs.a) return true;
        if(b < a && rhs.b >= rhs.a) return false;
        if(b < a && rhs.b < rhs.a) return b > rhs.b;
        return a < rhs.a;
    }
}nd[maxn];

int main() {
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%s", str);
            int tot = strlen(str);
            int top = 0;
            nd[i].m = nd[i].a = nd[i].b = 0;
            for(int j = 0; j < tot; j++) {
                if(str[j] == '(') {
                    top++;
                } else {
                    if(top == 0) {
                        nd[i].a++;
                    } else {
                        top--;
                        nd[i].m++;
                    }
                }
            }
            nd[i].b = top;
        }
        sort(nd, nd+n);
        int l = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            if(l > nd[i].a) {
                ans += nd[i].a;
                l -= nd[i].a;
            } else {
                ans += l;
                l = 0;
            }
            l += nd[i].b;
            ans += nd[i].m;
        }
        printf("%d\n", ans * 2);
    }
    return 0;
}