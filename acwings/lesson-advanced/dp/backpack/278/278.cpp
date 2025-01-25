#include <iostream>
#include <algorithm>

using namespace std;

const int MAXM = 10000 + 2;

int dp[MAXM];
int N, M;

int main() {
    cin >> N >> M;
    dp[0] = 1;

    int a;
    for (int i = 0; i < N; ++i) {
        cin >> a;
        for (int j = M; j >= a; --j) {
            dp[j] += dp[j-a];
        }
    }
    cout << dp[M] << endl;

    return 0;
}