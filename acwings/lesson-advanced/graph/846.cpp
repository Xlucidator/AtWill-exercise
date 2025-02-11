#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 2; // N for vertex (M for edges)

int n;
int h[N], e[N<<1], ne[N<<1], idx;
bool flags[N];

int ans = N; // for barycenter

inline void init() {
    memset(h, -1, sizeof h);
}

inline void add(int a, int b) { // add b to a's adjcent table: means a --> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int dfs(int u) {
    flags[u] = true;

    int sum = 1, res = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];   // for each subtree
        if (!flags[j]) {
            int s = dfs(j);
            res = max(res, s);
            sum += s;
        }
    }
    res = max(res, n - sum);
    ans = min(ans, res);
    return sum;
}

int main() {
    init();

    cin >> n;
    int a, b;
    for (int i = 0; i < n-1; ++i) {
        cin >> a >> b;
        add(a, b); add(b, a);
    }

    dfs(1);
    cout << ans << endl;

    return 0;
}