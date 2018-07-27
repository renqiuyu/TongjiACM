#include <iostream>
#include <cstdio>

using namespace std;
int n, q;
const int maxn = 1e5 + 10;
int Min[maxn << 2], sum[maxn << 2], B[maxn], cnt[maxn << 2];
inline int ls(int x)
{
    return x << 1;
}
inline int rs(int x)
{
    return x << 1 | 1;
}
void pushup(int x)
{
    sum[x] = sum[ls(x)] + sum[rs(x)];
    Min[x] = min(Min[ls(x)], Min[rs(x)]);
}
void build(int x, int l, int r)
{
    if(l == r)
    {
        scanf("%d", &B[l]);
        Min[x] = B[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
    pushup(x);
}
void lazy(int x, int val)//打lazy标记的时候自身直接计算 
{
    cnt[x] += val;
    Min[x] += val;
}
void pushdown(int x)
{
    if(cnt[x])
    {
        lazy(ls(x), cnt[x]);
        lazy(rs(x), cnt[x]);
        cnt[x] = 0;
    }
}
void change(int x, int l, int r, int a, int b)
{
    if(a <= l && r <= b && Min[x] - 1 > 0)
    {
        lazy(x, -1);
        return;
    }
    if(l == r)
    {
        Min[x] += -1;
        while(Min[x] <= 0)
        {
            Min[x] += B[l];
            ++sum[x];
        }
        return;
    }
    int mid = l + r >> 1;
    pushdown(x);
    if(a <= mid)
        change(ls(x), l, mid, a, b);
    if(b > mid)
        change(rs(x), mid + 1, r, a, b);
    pushup(x);
}
int query(int x, int l, int r, int a, int b)
{
    if(a <= l && r <= b)
        return sum[x];
    pushdown(x);
    int mid = l + r >> 1;
    int ans = 0;
    if(a <= mid)
        ans = query(ls(x), l, mid, a, b);
    if(b > mid)
        ans = ans + query(rs(x), mid + 1, r, a, b);
    return ans;
}
char s[100];
int main()
{
    int l, r;
    while(~scanf("%d%d", &n, &q))
    {
        memset(Min, 0, sizeof(Min));
        memset(sum, 0, sizeof(sum));
        memset(cnt, 0, sizeof(cnt));
        build(1, 1, n);
        for(int i = 1; i <= q; ++i)
        {
            scanf("%s%d%d", s, &l, &r);
            if(s[0] == 'q')
                printf("%d\n", query(1, 1, n, l, r));
            else
                change(1, 1, n, l, r);
        }
    }
    return 0;
}
/*
5 100
1 5 2 4 3
add 1 4
query 1 4
add 2 5
query 2 5
add 3 5
query 1 5
add 2 4
query 1 4
add 2 5
query 2 5
add 2 2
query 1 5
*/