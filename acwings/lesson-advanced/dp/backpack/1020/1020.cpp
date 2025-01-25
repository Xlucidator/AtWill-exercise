#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// WRONG！ should be 21 * 1000, 79 * 1000
const int MAXO = 21 + 2, MAXN = 79 + 2;
const int NUL = 0x3f3f3f3f;

int M/* Oxygen */, N/* Nitrogen */, K;
int dp[MAXO][MAXN];

void printDPLegal(int round) {
    printf("[Round %d]\n", round);
    for (int j = 0; j < MAXO; ++j) {
        for (int k = 0; k < MAXN; ++k) {
            if (dp[j][k] != NUL) printf("f[%d][%d]: %d\n", j, k, dp[j][k]);
        }
    }
    puts("");
}

int main() {
    scanf("%d%d%d", &M, &N, &K);

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    int a, b, c;
    for (int i = 0; i < K; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        for (int j = M ; j >= 0; --j) {
            for (int k = N; k >= 0; --k) {
                dp[j][k] = min(dp[j][k], dp[max(0, j-a)][max(0, k-b)] + c);
            }
        }
        // printDPLegal(i+1);
    }

    printf("%d\n", dp[M][N]);

    return 0;
}
