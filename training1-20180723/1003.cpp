#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

struct point {
    int x;
    int y;
    int id;
    point(){}
    point(int a, int b) : x(a), y(b){}
    bool operator < (const point &rhs) const {
        if(x == rhs.x) {
            return y < rhs.y;
        }
        return x < rhs.x;
    }
}p[5005];

int main(){
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < 3 * n; i++) {
            scanf("%d%d",  &p[i].x, &p[i].y);
            p[i].id = i + 1;
        }
        sort(p, p + 3*n);
        for(int i = 0; i < 3*n; i+=3) {
            printf("%d %d %d\n", p[i].id, p[i+1].id, p[i+2].id);
        }

    }
    return 0;
}
