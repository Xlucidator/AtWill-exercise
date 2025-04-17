/*
怎么装物品，使得剩余空间最小
 => 将箱子的容量看作价值，目标使价值最大 
dp[j]: 体积为j时，最大的价值（最大的体积）
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXV = 20000 + 2;

int dp[MAXV];
int n , V;

int main() {
    cin >> V >> n;
    int v;
    for (int i = 0; i < n; ++i) {
        cin >> v;
        for (int j = V; j >= v; --j) {
            dp[j] = max(dp[j], dp[j-v] + v);
        }
    }
    cout << V - dp[V] << endl;
    return 0;
}