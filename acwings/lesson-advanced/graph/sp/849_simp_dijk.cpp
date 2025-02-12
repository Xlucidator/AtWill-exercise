#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 500+2, M = 1e5 + 2;

int g[N][N]; // use matrix for graph
int n, m;

int d[N];    // shortest path
int flag[N]; // vertex set of those shortest path is determinated

void add(int x, int y, int z) {
    g[x][y] = min(g[x][y], z);
}

int dijkstra(int target) {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    int t;
    for (int i = 0; i < n; ++i) {
        // find min distance
        t = -1;
        for (int j = 1; j <= n; ++j) {
            if (!flag[j] && (t == -1 || d[j] < d[t]))
                t = j;
        }
        
        // add to set
        if (t == target) break;
        flag[t] = 1;
        // printf("%d\n", t);

        // update distance
        for (int j = 1; j <= n; ++j) {
            d[j] = min(d[j], d[t] + g[t][j]);
            // printf("[update] d[%d] -> %d\n", j, d[j]);
        }
    }

    return d[target] != 0x3f3f3f3f ? d[target] : -1;
}

int main() {
    memset(g, 0x3f, sizeof g);

    cin >> n >> m;
    int a, b, d;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> d;
        add(a, b, d);
    }
    cout << dijkstra(n) << endl;

    return 0;
}