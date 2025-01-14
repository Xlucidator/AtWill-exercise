#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_M = 101; // sum
const int MAX_N = 21;  // stamp size
const int INF = 0x7ffffff0;

int M, N;
int dp[MAX_N][MAX_M]; // dp[i][j]: minimal size of stamps ( locate in [0, i] ) to sum up with j
int stamps[MAX_N];

void init_dp() {
    fill(&dp[0][0], &dp[0][0] + MAX_N * MAX_M, INF);
}

void printVec(int (*arr)[MAX_M], int n, int m, const char* name) {
    printf("[vector %s]\n", name);
    for (int i = 0; i < n; ++i) {
        printf("\t[%d] ", i);
        for (int j = 0; j < m; ++j) {
            printf("%3d", arr[i][j] == INF ? 0 : arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    init_dp();
    cin >> M >> N;
    for (int i = 0; i < N; ++i) {
        cin >> stamps[i];
        dp[i][stamps[i]] = 1;
    }

    for (int i = 1; i < N/* stamps size */; ++i) {
        int new_stamp = stamps[i];
        for (int sum = stamps[0]; sum <= M/* target sum */; ++sum) {
            dp[i][sum] = min(dp[i][sum], dp[i-1][sum]);
            int last_sum = sum - new_stamp;
            if (last_sum > 0) 
                dp[i][sum] = min(dp[i][sum], dp[i-1][last_sum] + 1);
        }            
    }

    // printVec(dp, N, M, "dp");
    int res = dp[N-1][M];
    printf("%d\n", res == INF ? 0 : res);

    return 0;
}