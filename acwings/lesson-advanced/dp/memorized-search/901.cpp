#include <iostream>
#include <algorithm>
// #include <cstring>

using namespace std;
const int N = 310;

int n, m;
int h[N][N];
int dp[N][N];

// up right down left
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
inline bool inbound(int x, int y) { 
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

int dpRecursive(int x, int y) {
    int& v = dp[x][y];
    if (v != 0) return v;

    int a, b;
    for (int i = 0; i < 4; ++i) {
        a = x + dx[i], b = y + dy[i];
        if (inbound(a, b) && h[a][b] < h[x][y])
            v = max(v, dpRecursive(a, b) + 1);
    }
    return v = max(v, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j) 
            scanf("%d", &h[i][j]);
            
    int res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            res = max(res, dpRecursive(i, j));
    printf("%d\n", res);

    return 0;
}