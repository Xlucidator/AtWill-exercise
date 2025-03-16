#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 500 + 2, INF = 0x3f3f3f3f;

int n;
int dp[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) dp[i][0] = dp[i][i+1] = -INF; // many bugs here

    int a;
    scanf("%d", &dp[1][1]);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &a);
            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + a;
            // printf("dp[%d][%d] = max(%d, %d) + %d = %d\n", i, j, dp[i-1][j-1], dp[i-1][j], a, dp[i][j]);
        }
    }
    int res = -INF;
    for (int i = 1; i <= n; ++i) res = max(res, dp[n][i]);
    printf("%d\n", res);
    return 0;
}