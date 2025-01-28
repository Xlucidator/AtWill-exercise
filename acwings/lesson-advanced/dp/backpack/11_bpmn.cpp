// Backpack Method Number

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002, MAXV = 1002;
const int MOD = 1e9 + 7;

int dp[MAXV];
int cnt[MAXV];
int N, V;

void printVec(int arr[], int n, const char* name) {
    printf("%s\t", name);
    for (int i = 1; i <= n; ++i) printf("%d ", arr[i]); 
    puts("");
}

int main() {
    cin >> N >> V;
    for (int j = 0; j <= V; ++j) cnt[j] = 1;
    int v, w;
    for (int i = 1; i <= N; ++i) {
        cin >> v >> w;
        // printf("[round %d]\n", i);
        for (int j = V; j >= v; --j) {
            int use = dp[j-v] + w;
            if (dp[j] < use) {
                dp[j] = use;
                cnt[j] = cnt[j-v];
            } else if (dp[j] == use) {
                cnt[j] = (cnt[j] + cnt[j-v]) % MOD;
            }  
        }
        // printVec(dp, V, "dp");
        // printVec(cnt, V, "cnt");
    }
    cout << cnt[V] << endl;

    return 0;
}
