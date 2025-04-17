#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 110, S = 110 * N;

int n;
int dp[S];
struct Stone {
    int s, e, l;
    // float val() { return (float)s / (float)l; }
    bool operator<(const Stone& other) { return s * other.l < other.s * l; }
} stone[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T;
    cin >> T;
    for (int x = 1; x <= T; ++x) {
        cin >> n;
        int max_time = 0;
        for (int i = 0; i < n; ++i) {
            cin >> stone[i].s >> stone[i].e >> stone[i].l;
            max_time += stone[i].s;
        }
        sort(stone, stone + n);

        memset(dp, -1, sizeof dp);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            auto& st = stone[i];
            for (int j = max_time; j >= st.s; j--) {
                int t = j - st.s;
                dp[j] = max(dp[j], dp[t] + st.e - st.l*t);
            }
        }

        int res = 0;
        for (int i = 0; i <= max_time; ++i) res = max(res, dp[i]);
        printf("Case #%d: %d\n", x, res);
    }
    return 0;
}