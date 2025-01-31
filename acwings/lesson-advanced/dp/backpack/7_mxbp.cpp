#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002, MAXV = 1002;

int dp[MAXV];
int N, V;

int main() {
    cin >> N >> V;
    
    int v, w, s;
    for (int i = 1; i <= N; ++i) {
        cin >> v >> w >> s;
        if (s == -1) {
            for (int j = V; j >= v; --j)
                dp[j] = max(dp[j], dp[j-v] + w);
        } else if (s == 0) {
            for (int j = v; j <= V; ++j)
                dp[j] = max(dp[j], dp[j-v] + w);
        } else {
            // binary optimization
            int remain = s, k = 1;
            while (remain > 0) {
                int kv = k * v, kw = k * w;
                for (int j = V; j >= kv; --j) 
                    dp[j] = max(dp[j], dp[j-kv] + kw);
                remain -= k;
                k = min(remain, k << 1);
            }
        }
    }
    cout << dp[V] << endl;

    return 0;
}