#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// WRONG！ should be 21 * 1000, 79 * 1000
const int MAXO = 21 + 21 + 2, MAXN = 79 + 79 + 2;
const int NUL = 0x3f3f3f3f;

int M/* Oxygen */, N/* Nitrogen */, K;
int dp[21000][MAXN];

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
        for (int j = MAXO - 1; j >= a; --j) {
            for (int k = MAXN - 1; k >= b; --k) {
                dp[j][k] = min(dp[j][k], dp[j-a][k-b] + c);
            }
        }
        printDPLegal(i+1);
    }

    int res = NUL;
    for (int j = M; j < MAXO; ++j) {
        for (int k = N; k < MAXN; ++k) {
            res = min(res, dp[j][k]);
        }
    }

    printf("%d\n", res);

    return 0;
}
