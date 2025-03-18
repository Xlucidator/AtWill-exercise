#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100 + 2, V = N;

int n, m;
int v[N], w[N];
int dp[N][V];

int h[N], e[N], ne[N], idx;
int root;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        dfs(son);

        // like group bp
        for (int j = m - v[u]; j > 0; --j) { // volume: u volume
            for (int k = 0; k <= j; ++k) {   // select: give son volume k 
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[son][k]);
            }
        }
    }

    for (int i = m; i >= v[u]; --i) dp[u][i] = dp[u][i-v[u]] + w[u];
    for (int i = 0; i < v[u]; ++i) dp[u][i] = 0;
}

int main() {
    memset(h, -1, sizeof h);

    scanf("%d%d", &n, &m);
    int p;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &v[i], &w[i], &p);
        if (p == -1) root = i;
        else add(p, i);
    }

    dfs(root);

    printf("%d\n", dp[root][m]);

    return 0;
}