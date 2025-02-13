#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2000+2, M = 10000+2;
const int INF = 0x3f3f3f3f;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], cnt[N];
int flag[N];

int q[M*N]; // should be enough: M * 1000 is enough, for worst cases

void add(int x, int y, int z) {
    e[idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx++;
}

bool spfa(int target) {
    // no need to initialize: for only negative edge would trouble 
    // memset(dist, 0x3f, sizeof dist);
    // dist[1] = 0;
    int head = 0, tail = -1;
    for (int i = 1; i <= n; ++i) {
        q[++tail] = i;
        flag[i] = 1; 
    }
    
    while (head <= tail) {
        int a = q[head++]; flag[a] = 0;
        for (int i = h[a]; i != -1; i = ne[i]) {
            int b = e[i];
            if (dist[b] > dist[a] + w[i]) {
                dist[b] = dist[a] + w[i];
                cnt[b] = cnt[a] + 1;
                if (cnt[b] >= n) return true;
                if (!flag[b]) { q[++tail] = b, flag[b] = 1; }
            }
        }
    } 
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    puts(spfa(n) ? "Yes" : "No");

    return 0;
}