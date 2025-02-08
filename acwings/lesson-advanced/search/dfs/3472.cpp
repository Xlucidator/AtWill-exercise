#include <iostream>

using namespace std;

int r;
int res[93], idx;
bool col[10], dig[20], adig[20];

void dfs(int x) {
    if (x == 9) {
        res[++idx] = r;
        return;
    }
    for (int y = 1; y <= 8; ++y) {
        if (col[y] || dig[x - y + 8] || adig[x + y]) continue;
        col[y] = dig[x - y + 8] = adig[x + y] = 1;
        r = r * 10 + y;
        dfs(x+1);
        r /= 10;
        col[y] = dig[x - y + 8] = adig[x + y] = 0;
    }
}

int main() {
    dfs(1);
    int n; scanf("%d", &n);
    int s;
    while (n--) {
        scanf("%d", &s);
        printf("%d\n", res[s]);
    }
    return 0;
}