//
// Created by renqiuyu on 2018/7/27.
//
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

const int maxn = 300005;
int d[maxn];
int vis[maxn]; // v
int used[maxn]; // e
int cnt;
int n, m;

struct edge{
    int from, to, id;
    edge(){}
    edge(int f, int t, int id) : from(f), to(t), id(id){}
}edges[maxn];

int tot;
vector<int> G[100005];
vector<int> ans[100005];

void addedge(int f, int t, int id) {
    G[f].push_back(tot);
    edges[tot++] = edge(f, t, id);
    G[t].push_back(tot);
    edges[tot++] = edge(t, f, -id);
    d[f]++;
    d[t]++;
}

void eular(int x) {
    for(auto i : G[x]) {
        if(!used[i]) {
            used[i] = used[i ^ 1] = 1;
            eular(edges[i].to);
            if(i >= 2 * m) {
                cnt++;
            } else {
                ans[cnt].push_back(edges[i].id);
            }
        }
    }
}

vector<int> temp;
void D(int x) {
    vis[x] = 1;
    if(d[x] & 1) {
        temp.push_back(x);
    }
    for(auto i : G[x]) {
        if(!vis[edges[i].to]){
            D(edges[i].to);
        }
    }
}


int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        tot = 0;
        cnt = 0;
        memset(vis, 0, sizeof vis);
        memset(used, 0, sizeof used);
        memset(d, 0, sizeof d);
        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }
        for(int i = 1;i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v, i);
        }
        for(int i = 1; i <= n; i++){
            if(!vis[i]) {
                D(i);
            } else {
                continue;
            }
            if(!temp.empty() && temp.size() > 2) {
                for(int j = 2; j < temp.size(); j += 2) {
                    addedge(temp[j], temp[j + 1], 0);
                }
            }
            if(temp.empty()) {
                eular(i);
            } else {
                eular(temp[0]);
            }
            temp.clear();
            cnt++;
        }
        int res = 0;
        for(int i = 0; i < cnt; i++) {
            if(!ans[i].empty()) {
                res++;
            }
        }
        printf("%d\n", res);
        for(int i = 0; i < cnt; i++){
            if(ans[i].empty()) {
                continue;
            }
            printf("%d", ans[i].size());
            for(auto j : ans[i]) {
                printf(" %d", -j);
            }
            printf("\n");
            ans[i].clear();
        }
    }
    return 0;
}

/*

 4 5
 1 2
 2 3
 3 1
 4 1
 4 3

 4 6
 1 2
 2 3
 3 1
 4 1
 4 3
 4 2

 */