#include <iostream>
#include <algorithm>

using namespace std;
#define OPT

const int MAXN = 1002, MAXV = 1002;

int volume[MAXN], weight[MAXN];
int n, vlimit;

#ifdef OPT
    int dp[MAXV]; // compress to 1d: throw useless storage info of the intermediate status
#else
    int dp[MAXN][MAXV];  // dp[i][j]: use [0, i], limit to j, selection that has max weight sum ; { [i] not selected, [i] selected }
#endif

int main() {
    /* Read input */
    scanf("%d%d", &n, &vlimit);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &volume[i], &weight[i]);

    /* DP Calculate */
#ifdef OPT
    for (int i = 1; i < n; ++i) {
        for (int j = vlimit; j >= volume[i]; --j) {
            dp[j] = max(dp[j], dp[j-volume[i]] + weight[i]);
        }
    }
    // i = n, j = vlimit
    if (vlimit-volume[n] >= 0) dp[vlimit] = max(dp[vlimit], dp[vlimit-volume[n]] + weight[n]);
    printf("%d\n", dp[vlimit]);
#else
    int last_volume;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= vlimit; ++j) {
            dp[i][j] = dp[i-1][j];
            last_volume = j - volume[i];
            if (last_volume >= 0) 
                dp[i][j] = max(dp[i][j], dp[i-1][last_volume] + weight[i]);
        }
    }
    printf("%d\n", dp[n][vlimit]);
#endif
    

    return 0;
}

