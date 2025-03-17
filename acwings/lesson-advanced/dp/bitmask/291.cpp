#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 12, M = 1 << N;
typedef long long ll;

int n, m;
ll dp[N][M];
bool st[N];  // preprocess for continuous zero cnt

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m), n && m) {
        /* Preprocess */
        memset(dp, 0, sizeof dp);
        for (int i = 0; i < 1<<n; ++i) {
            st[i] = true; int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) {
                    if (cnt & 1) { st[i] = false; break; }
                    cnt = 0;
                } else cnt++;
            }
            if (cnt & 1) st[i] = false;
        }

        /* Calculation */
        dp[0][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < 1<<n; ++j) {
                for (int k = 0; k < 1<<n; ++k) {
                    if ((j & k) == 0 && st[j | k])
                        dp[i][j] += dp[i-1][k];
                }
            }
        }

        /* Out */
        printf("%lld\n", dp[m][0]);  // list m should all be zero
    }
}