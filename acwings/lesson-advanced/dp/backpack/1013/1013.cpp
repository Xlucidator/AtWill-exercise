#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 12, MAXM = 17;

int N, M;
int profit[MAXN][MAXM];
int dp[MAXM];
int distrib[MAXN][MAXM];

int main() {
    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j)
            cin >> profit[i][j];
    }

    for (int i = N; i >= 1; --i) {
        for (int j = M; j >= 1; --j) {
            int cnt = 0;
            for (int k = 0; k <= M; ++k) {
                if (j >= k) {
                    int nvalue = dp[j-k] + profit[i][k];
                    if (nvalue > dp[j]) {
                        cnt = k;
                        dp[j] = nvalue;
                    }
                }
            }
            distrib[i][j] = cnt;
        }
    }
    cout << dp[M] << endl;
    
    int res[MAXM];
    int j = M;
    for (int i = 1; i <= N; ++i) {
        res[i] = distrib[i][j];
        cout << i << " " << res[i] << endl;
        j -= res[i];
    }

    return 0;
}