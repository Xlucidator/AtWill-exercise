#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 1e6+2;

int a[MAXN];
int n, k;
int q[MAXN]; // monotonic queue : store **number's index** in a[]

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    /* Get Min in the Window */
    int head = 0, tail = -1; // [head->, tail->] should be monotone increasing, the min idx is in q[head]
    for (int i = 0; i < n; ++i) { // window [i-k+1, i]
        if (head <= tail/* for queue validity */ && q[head] < i-k+1) head++;
        // Every time before add a[i] in: get rid of all the numbers that are GEQ than a[i] from tail
        while (head <= tail/* for queue validity */ && a[q[tail]] >= a[i]) tail--;
        q[++tail] = i;

        if (i >= k - 1) printf("%d ", a[q[head]]);
    }
    puts("");

    head = 0, tail = -1;    // [head->, tail->] should be monotone decreasing
    for (int i = 0; i < n; ++i) {
        if (head <= tail && q[head] < i-k+1) head++;
        while (head <= tail && a[q[tail]] <= a[i]) tail--;
        q[++tail] = i;

        if (i >= k - 1) printf("%d ", a[q[head]]);
    }
    puts("");

    return 0;
}
