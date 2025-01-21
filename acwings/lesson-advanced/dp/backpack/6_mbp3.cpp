#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002;
const int MAXV = 20002, MAXS = 20002;

int q[MAXV]; // mono queue
int N, V;
int dp[2][MAXV];

int main() {
    scanf("%d%d", &N, &V);
    int v, w, s;

    bool cur = 0, pre = 1;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &v, &w, &s);
        cur = !cur; pre = !cur;
        for (int j = 0; j < v; ++j) {
            int head = 0, tail = -1;
            for (int k = j; k <= V; k += v) {
                if (head <= tail && q[head] < k - s*v) head++;
                while (head <= tail && 
                    dp[pre][q[tail]] - (q[tail]-j)/v * w
                    <= 
                    dp[pre][k]       - (k-j)/v * w
                ) tail--;
                q[++tail] = k;

                dp[cur][k] = max(dp[cur][k], dp[pre][q[head]] + (k - q[head])/v * w);
            }
        }
    }

    printf("%d\n", dp[cur][V]);

    return 0;
}
