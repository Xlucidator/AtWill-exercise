#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 500+2, INF = 0x3f3f3f3f;

int n, m;
int g[N][N];
int d[N]; // distance to set
bool flag[N]; // is in set

int prim() {
    memset(d, 0x3f, sizeof d);

    int res = 0;
    for (int i = 0; i < n; ++i) {
        // find min weight edge that is out of set
        int t = -1;
        for (int j = 1; j <= n; ++j) {
            if (!flag[j] && (t == -1 || d[t] > d[j])) {
                t = j;
            }
        }

        // add it to set
        if (i/* remove init state i = 0 */ && d[t] == INF) return INF;
        if (i) res += d[t];
        flag[t] = 1;
        
        // update distance to set
        for (int j = 1; j <= n; ++j)
            d[j] = min(d[j], g[t][j]);
    }

    return res;
}

int main() {
    memset(g, 0x3f, sizeof g);
    cin >> n >> m;
    int a, b, c;
    
    while (m --) {
        cin >> a >> b >> c;
        if(a != b) g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int t = prim();
    if (t == INF) puts("impossible");  // there's INF edge in the graph <=> not connectable
    else printf("%d\n", t);

    return 0;
}