#include <iostream>
#include <algorithm>

using namespace std;
#define OPT

const int MAXN = 102, MAXV = 102;

int v[MAXN], w[MAXN], s[MAXN];
int N, V;
#ifdef OPT
    int dp[MAXV];
#else
    int dp[MAXN][MAXV];
#endif

int main() {
    scanf("%d%d", &N, &V);
    for (int i = 1; i <= N; ++i) scanf("%d%d%d", &v[i], &w[i], &s[i]); // can even be placed in the dp calculation

#ifdef OPT
    for (int i = 1; i < N; ++i) {
        for (int j = V; j >= v[i]; --j) {
            for (int k = 0; k <= s[i]; k++) {
                if (j - k*v[i] >= 0) dp[j] = max(dp[j], dp[j - k*v[i]] + k*w[i]);
            }
        }
    }
    for (int k = 0; k <= s[N]; k++) // i = N, j = V
        if (V - k*v[N] >= 0) dp[V] = max(dp[V], dp[V - k*v[N]] + k*w[N]);
    printf("%d\n", dp[V]);
#else
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= V; ++j) {
            for (int k = 0; k <= s[i]; k++) {
                if (j - k*v[i] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j - k*v[i]] + k*w[i]);
            }
        }
    }
    printf("%d\n", dp[N][V]);
#endif

    return 0;
}
