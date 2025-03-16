// LCS + LIS

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 3002;

int A[MAXN], B[MAXN];
int dp[MAXN][MAXN];  // dp[i][j]: LCIS in A[0, i], B[0, j] with B[j] be the end
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
    for (int i = 1; i <= N; ++i) scanf("%d", &B[i]);
    
#ifdef RAW
    for (int i = 1; i <= N; ++i) {
        int numa = A[i];
        for (int j = 1; j <= N; ++j) {
            int numb = B[j];
            dp[i][j] = dp[i-1][j];
            if (numa == numb) {
                for (int k = 1; k <= j-1; k++) {
                    if (B[k] < numb) dp[i][j] = max(dp[i][j], dp[i-1][k] + 1);
                }
                dp[i][j] = max(dp[i][j], 1);  // for non
            }
        }
    }
#else
    for (int i = 1; i <= N; ++i) {
        int numa = A[i];
        int maxv = 1;
        for (int j = 1; j <= N; ++j) {
            int numb = B[j];
            dp[i][j] = dp[i-1][j];
            if (B[j-1] < numa) maxv = max(maxv, dp[i-1][j-1] + 1);
            if (numa == numb) dp[i][j] = max(dp[i][j], maxv);
        }
    }
#endif

    int res = 0;
    for (int i = 0; i <= N; i++) res = max(res, dp[N][i]);
    printf("%d\n", res);

    return 0;
}