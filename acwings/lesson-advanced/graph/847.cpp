#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 2;

int n, m; // vertex & edge
int h[N], e[N], ne[N], idx;
int q[N]; // for bfs
int d[N]; // distance

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int bfs() {
    int head = 0, tail = 0;
    q[0] = 1;

    memset(d, -1, sizeof d);
    d[1] = 0;
    while (head <= tail) {
        int t = q[head++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (d[j] == -1) { // not detect yet
                d[j] = d[t] + 1;
                q[++tail] = j;
            }
        }
    }
    return d[n];
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        add(a, b);
    }
    cout << bfs() << endl;
    return 0;
}