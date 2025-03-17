#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 6002;

int n;
int happy[N];
int h[N], e[N], ne[N], idx;  // graph: sll storage
bool has_father[N]; // special: to tell the root

int dp[N][2];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    dp[u][1] = happy[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs(j);
        dp[u][0] += max(dp[j][0], dp[j][1]);
        dp[u][1] += dp[j][0];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    /* Read in & Preprocess */
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> happy[i];
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b; // a <-- b
        has_father[a] = true;
        add(b, a);
    }
    int root = 1; // Find root
    while (has_father[root]) root++;

    /* Calculate dp */
    dfs(root);

    /* Output */
    cout << max(dp[root][0], dp[root][1]) << endl;

    return 0;
}