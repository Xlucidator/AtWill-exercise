#include <iostream>
#include <algorithm>

using namespace std;

int N, V, M;
int dp[102][102];

int main() {
    cin >> N >> V >> M;
    int v, m, w;
    for (int i = 0; i < N; ++i) {
        cin >> v >> m >> w;
        for (int j = V; j >= v; --j) {
            for (int k = M; k >= m; --k) {
                dp[j][k] = max(dp[j][k], dp[j-v][k-m] + w);
            }
        }
    }
    cout << dp[V][M] << endl;
    
    return 0;
}

// written in challenge mode