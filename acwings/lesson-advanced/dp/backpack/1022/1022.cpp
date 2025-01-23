#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002, MAXM = 502, MAXK = 102;

int N, M, K;
int dp[MAXN][MAXM]; // dp[j][k]

int main() {
    scanf("%d%d%d", &N, &M, &K);

    int n, m;
    for (int i = 0; i < K; ++i) {
        scanf("%d%d", &n, &m);
        for (int j = N; j >= n; --j) {
            for (int k = M - 1; k >= m; --k) {
                dp[j][k] = max(dp[j][k], dp[j-n][k-m] + 1);
            }
        }
    }

    int max_num = dp[N][M-1];
    int min_dmg = M-1;
    auto& dp_N = dp[N];
    for (; min_dmg >= 0 && dp_N[min_dmg] == max_num; min_dmg--);

    printf("%d %d\n", max_num, M - min_dmg - 1);

    return 0;
}