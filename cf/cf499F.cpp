//
// Created by renqiuyu on 2018/7/27.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000005;

struct p{
    int op; // in = 0, and = 1, or = 2, xor = 3, not = 4
    int l, r;
    int v;
}node[maxn];

int init(int v) {
    if(node[v].op == 0) {
        return node[v].v;
    }
    if(node[v].op == 4) {
        return node[v].v = (!init(node[v].l));
    }
    if(node[v].op == 1) {
        return node[v].v = (init(node[v].l) & init(node[v].r));
    }
    if(node[v].op == 2) {
        return node[v].v = (init(node[v].l) | init(node[v].r));
    }
    if(node[v].op == 3) {
        return node[v].v = (init(node[v].l) ^ init(node[v].r));
    }
}

int ans[maxn];
void dfs(int v, int will) {
    if(node[v].op == 1) {
        if(will == 0) {
            ans[node[v].l] = ans[node[v].r] = 0;
            dfs(node[v].l, 0);
            dfs(node[v].r, 0);
        } else {
            if(node[v].v == 0) {
                if(node[node[v].l].v == 0 && node[node[v].r].v == 0) {
                    dfs(node[v].l, 0);
                    dfs(node[v].r, 0);
                } else if(node[node[v].l].v == 0) {
                    ans[node[v].l] = 1;
                    dfs(node[v].l, 1);
                } else {
                    ans[node[v].r] = 1;
                    dfs(node[v].r, 1);
                }
            } else {
                ans[node[v].l] = ans[node[v].r] = 1;
                dfs(node[v].l, 1);
                dfs(node[v].r, 1);
            }
        }
    }
    else if(node[v].op == 2) {
        if(will == 0) {
            ans[node[v].l] = ans[node[v].r] = 0;
            dfs(node[v].l, 0);
            dfs(node[v].r, 0);
        } else {
            if (node[v].v == 0) {
                ans[node[v].l] = ans[node[v].r] = 1;
                dfs(node[v].l, 1);
                dfs(node[v].r, 1);
            } else {
                int lc = node[v].l;
                int rc = node[v].r;
                if(node[lc].v == 1 && node[rc].v == 1) {
                    ans[lc] = ans[rc] = 0;
                    dfs(lc, 0);
                    dfs(rc, 0);
                } else if(node[lc].v == 1) {
                    dfs(lc, 1);
                    dfs(rc, 0);
                } else {
                    dfs(lc, 0);
                    dfs(rc, 1);
                }
            }
        }
    }
    else if(node[v].op == 3) {
        int lc = node[v].l;
        int rc = node[v].r;
        if(will == 0) {
            ans[lc] = ans[rc] = 0;
            dfs(lc, 0);
            dfs(rc, 0);
        }
        else {
            ans[lc] = ans[rc] = 1;
            dfs(lc, 1);
            dfs(rc, 1);
        }
    }
    else if(node[v].op == 4) {
        if(will == 0) {
            ans[node[v].l] = 0;
            dfs(node[v].l, 0);
        } else {
            ans[node[v].l] = 1;
            dfs(node[v].l, 1);
        }
    }
    else if(node[v].op == 0) {
        ans[v] = will;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        char op[100];
        scanf("%s", op);
        int x, y;
        if(op[0] == 'A') {
            // AND
            scanf("%d%d", &x, &y);
            node[i].op = 1;
            node[i].l = x;
            node[i].r = y;
        }
        if(op[0] == 'O') {
            scanf("%d%d", &x, &y);
            node[i].op = 2;
            node[i].l = x;
            node[i].r = y;
        }
        if(op[0] == 'X') {
            scanf("%d%d", &x, &y);
            node[i].op = 3;
            node[i].l = x;
            node[i].r = y;
        }
        if(op[0] == 'N') {
            scanf("%d", &x);
            node[i].op = 4;
            node[i].l = x;
        }
        if(op[0] == 'I') {
            scanf("%d", &x);
            node[i].op = 0;
            node[i].v = x;
        }
    }
    init(1);
    int orig = node[1].v;
    dfs(1, 1);
    for(int i = 1; i <= n; i++) {
        // cout <<i << " : " << node[i].op << " " << node[i].l << " "<<node[i].r << " " << node[i].v << " " << endl;
        // cout << ans[i] << " ";
        if(node[i].op == 0){
            if(ans[i]) {
                printf("%d", orig ^ 1);
            } else {
                printf("%d", orig);
            }
        }
    }
    printf("\n");
    return 0;
}