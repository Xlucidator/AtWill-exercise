#include <iostream>
#include <algorithm>
using namespace std;

const int N = 600 + 2;
typedef long long ll;

int n, m;
int a[N];
int e[N];
// int dp[N];
ll sum;

ll ans = 0x3f3f3f3f3f3f3f3f;

void dfs(int e_idx) {
    // printf("[debug] e = %d\n", e_idx);
    if (e_idx == m) {
        ans = min(ans, sum);
        // printf("%lld\n", sum);
        return ;
    }

    int dist, tmp;
    for (int i = 0; i < n; ++i) {
        tmp = a[i];
        dist = abs(a[i] - e[e_idx]);

        a[i] = e[e_idx];
        sum += dist;
        dfs(e_idx+1);
        sum -= dist;
        a[i] = tmp;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &e[i]);

    dfs(0);
    printf("%lld\n", ans);

    return 0;
}