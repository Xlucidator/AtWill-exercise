#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 2, M = 2e5 + 2;
const int INF = 0x3f3f3f3f;

struct Edge {
    int a, b, w;
    bool operator< (const Edge& other) const {
        return w < other.w;
    }
};

Edge e[M];
int n, m;
int p[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    int res = 0, cnt = 0; // cnt: mst edges cnt
    for (int i = 0; i < m; ++i) {
        Edge& edge = e[i];
        int pa = find(edge.a), pb = find(edge.b);
        if (pa != pb) {
            res += edge.w;
            cnt++;
            p[pb] = pa; 
        }
    }
    return (cnt < n - 1) ? INF : res;
}

int main() {
    scanf("%d%d", &n, &m);
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        e[i] = {x, y, z};
    }
    sort(e, e+m);
    for (int i = 1; i <= n; ++i) p[i] = i;

    int t = kruskal();
    if (t == INF) puts("impossible");
    else printf("%d\n", t);

    return 0;
}