#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;
const int INF = 0x3f3f3f3f;

// struct Edge {
//     int a, b, w;
// } e[N];
int n, m;
int h[N], e[N], w[N], ne[N], idx;
int d[N];

int q[N<<1];
bool flag[N]; // check whether vertex is in the queue

void add(int a, int b, int z) {
    e[idx] = b, w[idx] = z, ne[idx] = h[a], h[a] = idx++;
}

int spfa(int target) {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    int head = 0, tail = 0;
    q[0] = 1; flag[1] = 1;

    // assert no negative circle
    while (head <= tail) {
        int a = q[head++]; flag[a] = 0;
        for (int i = h[a]; i != -1; i = ne[i]) {
            int b = e[i];
            if (d[b] > d[a] + w[i]) {
                d[b] = d[a] + w[i];
                if (!flag[b]) { q[++tail] = b; flag[b] = 1; }
            }
        }
    }

    return d[target];
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }

    int t = spfa(n);
    
    if (t > INF/2) puts("impossible");
    else printf("%d\n", t);

    return 0;
}