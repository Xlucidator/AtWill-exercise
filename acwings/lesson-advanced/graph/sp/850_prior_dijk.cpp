#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1.5e5 + 2; // N = M

typedef pair<int, int> pii;

int h[N], e[N], ne[N], idx; // use matrix for graph
int w[N]; // edge weight: distance
int n, m;

int d[N];    // shortest path
int flag[N]; // vertex set of those shortest path is determinated

void add(int x, int y, int z) {
    e[idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx++;
}

int dijkstra(int target) {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> heap; // min heap
    heap.push({0, 1});

    while (!heap.empty()) {
        // find min distance to next vertex
        auto t = heap.top(); heap.pop();
        int& cur = t.second, & dist = t.first;

        // add vertex to determinate set
        if (flag[target]) break;
        if (flag[cur]) continue;
        flag[cur] = 1;
        
        // update distance
        for (int i = h[cur]; i != -1; i = ne[i]) {
            int nxt = e[i];
            if (d[nxt] > dist + w[i]) {
                d[nxt] = dist + w[i];
                heap.push({d[nxt], nxt});
            }
        }
    }

    return d[target] != 0x3f3f3f3f ? d[target] : -1;
}

int main() {
    memset(h, -1, sizeof h);

    cin >> n >> m;
    int a, b, d;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> d;
        add(a, b, d);
    }
    cout << dijkstra(n) << endl;

    return 0;
}