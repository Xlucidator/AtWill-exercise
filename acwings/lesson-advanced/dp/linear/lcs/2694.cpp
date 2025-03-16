#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 5000 + 2;
const int MOD = 1e8;

string a, b;
int asize, bsize;
int dp[2][MAXN], cnt[2][MAXN];
// full: dp[i][j]

int main() {
    cin >> a >> b;
    asize = a.length() - 1;
    bsize = b.length() - 1;
    cnt[1][0] = 1;
    for (int j = 0; j <= bsize; ++j) cnt[0][j] = 1;

    bool cur, pre;
    for (int i = 1; i <= asize; ++i) {
        cur = i & 1; pre = !cur;
        char ch_a = a[i-1];
        for (int j = 1; j <= bsize; ++j) {
            char ch_b = b[j-1];
            // init
            cnt[cur][j] = 0;
            // update
            if (ch_a == ch_b) {
                dp[cur][j] = dp[pre][j-1] + 1;
                cnt[cur][j] += cnt[pre][j-1];
            } else {
                dp[cur][j] = max(dp[cur][j-1], dp[pre][j]);
                if (dp[cur][j] == dp[pre][j-1]) cnt[cur][j] -= cnt[pre][j-1]; // clear duplicated cnt in advance
            }
            if (dp[cur][j] == dp[cur][j-1]) cnt[cur][j] = (cnt[cur][j] + cnt[cur][j-1]) % MOD;
            if (dp[cur][j] == dp[pre][ j ]) cnt[cur][j] = (cnt[cur][j] + cnt[pre][ j ]) % MOD;

            // printf("%d ", dp[cur][j]);
        }
        // putchar('\n');
    }

    printf("%d\n%d\n", dp[cur][bsize], cnt[cur][bsize]);
    return 0;
}