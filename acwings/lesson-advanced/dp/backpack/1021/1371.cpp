#include <iostream>
#include <algorithm>

using namespace std;

const int MAXM = 10000+2;

long long dp[MAXM];
int n, m;

int main() {
    cin >> n >> m;
    dp[0] = 1;

    int v;
    for (int i = 1; i <= n; ++i) {
        cin >> v;
        for (int j = v; j <= m; ++j) {
            dp[j] += dp[j-v];
        }
    }
    cout << dp[m] << endl;

    return 0;
}