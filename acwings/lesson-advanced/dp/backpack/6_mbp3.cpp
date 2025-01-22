#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002;
const int MAXV = 20002, MAXS = 20002;

int q[MAXV]; // mono queue
int N, V;
int dp[MAXV];

void printQueue(int head, int tail) {
    printf("[queue] ");
    for (int i = head; i <= tail; ++i) printf("%d ",q[i]);
    puts("");
}

#define offset_value(idx, base) (dp[idx] + ((base)-idx)/v * w)

int main() {
    scanf("%d%d", &N, &V);
    int v, w, s;

    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &v, &w, &s);
        for (int j = V; j > V-v; --j) {
            int head = 0, tail = -1;

            // Preload
            int k, cnt;
            for (k = j, cnt = 0; k >= 0 && cnt <= s; k -= v, cnt++) {
                while (head <= tail && offset_value(q[tail], j) <= offset_value(k, j)) tail--;
                q[++tail] = k;
                // printQueue(head, tail); // debug
            }
            k -= (s + 1 - cnt) * v;
            
            // Begin to Calculate dp[j], dp[j-v], ..., dp[j%v]
            for (int tar = j; tar > 0; tar -= v, k -= v) {
                dp[tar] = max(dp[tar], offset_value(q[head], tar));
                // (dp[tar] != 0) ? printf("Update dp[%d][%d] to %d\n", i, tar, dp[tar]) : true; // debug

                if (head <= tail && q[head] > k + s*v) head++;
                if (k >= 0) {
                    while (head <= tail && offset_value(q[tail], j) <= offset_value(k, j)) tail--;
                    q[++tail] = k;
                }
                // printQueue(head, tail); // debug
            }
        }
    }

    printf("%d\n", dp[V]);

    return 0;
}
