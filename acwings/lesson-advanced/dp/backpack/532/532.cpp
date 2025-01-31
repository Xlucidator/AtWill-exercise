#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXAI = 25000 + 2, MAXN = 100 + 2;

int dp[MAXAI];
int a[MAXN];

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        int cnt = 0, maxa = 0;
        cin >> n;

        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a, a + n);
        maxa = a[n-1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = a[i]; j <= maxa; ++j) {
                dp[j] += dp[j-a[i]];
            }
            if (dp[a[i]] == 1) cnt++;
        }

        cout << cnt << endl;
    }

    return 0;
}