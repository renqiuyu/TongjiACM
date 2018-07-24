//
// Created by renqiuyu on 2018/7/24.
//

#include <iostream>
#include <cstdio>
#include <algorithm>


using namespace std;
typedef long long ll;

const int maxn = 1000005;
const int mod = 1e9+7;
ll a[maxn];
ll p, q;

ll power(ll x, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) {
            ans *= x;
            ans %= mod;
        }
        x *= x;
        x %= mod;
        k >>= 1;
    }
    return ans;
}

struct T{
    struct node{
        int l, r, p;
        ll v;
    }tree[maxn];
    int stack[maxn];
    int root;
    int n;
    void init(int n) {
        this->n = n;
        for(int i = 0; i <= n; i++) {
            tree[i].l = tree[i].r = tree[i].p = -1;
        }
        p = 1;
        q = 1;
    }
    void build(){
        int top = -1;
        for(int i = 0; i < n; i++) {
            int k = top;
            while(k >= 0 && a[stack[k]] < a[i]) {
                k--;
            }
            if(k != -1) {
                tree[i].p = stack[k];
                tree[i].v = a[stack[k]];
                tree[stack[k]].r = i;
            }
            if(k < top) {
                tree[stack[k+1]].p = i;
                tree[i].l = stack[k+1];
            }
            stack[++k] = i;
            top = k;
        }
        tree[stack[0]].p = -1;
        root = stack[0];
    }
    int dfs(int x){
        if(tree[x].l == -1 && tree[x].r == -1) {
            return 1;
        }
        int sum = 0;
        if(tree[x].l != -1) {
            sum += dfs(tree[x].l);
        }
        if(tree[x].r != -1) {
            sum += dfs(tree[x].r);
        }
        p *= sum + 1;
        p %= mod;
        return sum+1;
    }
    ll solve(){
        dfs(root);
        return q * n % mod * power(p * 2, mod-2) % mod;
    }
}t;
int main() {
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
        ::t.init(n);
        ::t.build();
        printf("%lld\n", ::t.solve());
    }
    return 0;
}

/*
3
3
1 2 2
3
1 2 1
5
1 2 3 2 1

*/

