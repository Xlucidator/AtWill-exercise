#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
const int N = 2e5 + 2, M = 18;  // M = log2(N) = log2(2e5)

int n, m;
int w[N];
int f[N][M];

int len2k[N];

void init() {
    // init dp
    for (int j = 0; j < M && (1 << j) <= n; ++j) { // len = 1 << j
        // printf("[j = %d] len = %d\n", j, 1<<j);
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            if (!j) f[i][j] = w[i];
            else f[i][j] = max(f[i][j-1], f[i+(1<<j-1)][j-1]);
            // printf("\tset f[%d][%d] = %d\n", i, j, f[i][j]);
        }
    }

    // init len2k
    int k = 0, nxt = 2;
    for (int len = 1; len <= n; ++len) {
        if (len == nxt) { k++; nxt <<= 1; }
        len2k[len] = k;
    }
}

int query(int l, int r) {
    int len = r - l + 1;
    int k = len2k[len];
    // int k = log2(len);

    // printf("[test] max(f[%d][%d], f[%d][%d])\n", l, k, r-(1<<k)+1, k);
    return max(f[l][k], f[r-(1<<k)+1][k]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

    init();
    scanf("%d", &m);
    int l, r;
    while (m--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }

    return 0;
}


