#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 500 + 2, M = 1e5 + 2;
const int INF = 0x3f3f3f3f;

struct Edge {
    int a, b, w;
};

int n, m, k;
Edge e[M];
int d[2][N];
int dist[N], backup[N];

void printdist(int turn) {
    printf("[round %d] ", turn);
    for (int i = 1; i <= n; ++i) printf("%d ", d[1][i]);
    puts("");
}

#ifdef SIMPLE

int bellman_ford(int target) { // target = n 
    memset(d, 0x3f, sizeof d);
    dist[1] = 0;

    for (int i = 0; i < k; ++i) {
        memcpy(backup, dist, sizeof(dist));
        for (int j = 0; j < m; ++j) {
            int a = e[j].a, b = e[j].b, w = e[j].w;
            dist[b] = min(dist[b], backup[a] + w);
        }
    }

    return dist[n] > INF / 2 ? -1 : dist[n];
}

#else

int bellman_ford(int target) {
    memset(d, 0x3f, sizeof d);
    auto& pre = d[0], &cur = d[1];
    cur[1] = 0; 

    bool is_update;
    for (int i = 0; i < k; ++i) {
        // printdist(i);
        is_update = false;
        memcpy(pre + 1, cur + 1, sizeof(int) * n);
        for (int j = 0; j < m; ++j) {
            auto& edge = e[j];
            int d_nxt = pre[edge.a] + edge.w;
            if (d_nxt < cur[edge.b]) {
                cur[edge.b] = d_nxt;
                is_update = true; 
                // printf("\tupdate d[%d] %d -> %d\n", edge.b, pre[edge.b], cur[edge.b]);
            }
        }
        if (!is_update) break;
    }
    // int res = cur[target];
                            // ! -1 can be a legal answer
    // return (res > INF / 2) ? INF : res; // ! INF can be update by negative edges
    return cur[target];
}

#endif 

int main() {
    cin >> n >> m >> k;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        e[i] = {x, y, z};
    }

    int t = bellman_ford(n);
    if (t > INF/2) puts("impossible");
    else cout << t << endl;

    return 0;
}