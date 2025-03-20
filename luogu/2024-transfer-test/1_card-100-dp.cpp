#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 5000 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
ll dp[N][N]; // [i][k]
pll cards[N];

int main() {
    scanf("%d%d", &n, &k);
    int a, b;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
        cards[i] = {b, a};
    }
    sort(cards + 1, cards + n + 1);

    dp[0][1] = -INF;
    for (int i = 1; i <= n; ++i) dp[i][1] = max(dp[i-1][1], cards[i].first + cards[i].second);
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + cards[i].second);
        }
    }

    ll res = -INF;
    for (int i = k; i <= n; ++i) res = max(res, dp[i][k] - cards[i].first);
    printf("%lld\n", res);

    return 0;
}