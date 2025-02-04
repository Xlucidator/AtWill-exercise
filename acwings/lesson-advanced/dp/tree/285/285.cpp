#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 6002;

int dp[MAXN][2];
int n;
int happy[MAXN];
int h[MAXN], e[MAXN], ne[MAXN], idx;  // Graph ds model : use link list
// list head, node value, next pointer, current using idx
bool has_father[MAXN];

         /* curr   next */
inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    // 'a': h[a] -> idx: content e[idx], nextlink ne[idx] -> last h[a] ==
}

void dfs(int i) {

}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> happy[i];

    memset(h, -1, sizeof h);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b; // a <-- b
        has_father[a] = true;
        add(b, a);
    }

    /* Find root */
    int root = 1;
    while (has_father[root]) root++;

    dfs(root);

    cout << max(dp[root][0], dp[root][1]);

    return 0;
}