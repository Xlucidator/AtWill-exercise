#include <iostream>

using namespace std;

const int N = 12; // maxn

int n;
char bd[N][N];
bool row[N], col[N], dig[N<<1], adig[N<<1];

void dfs(int x, int y, int cnt) {
    if (y == n) y = 0, x++;
    if (x == n) {
        if (cnt == n) { // has result
            for (int i = 0; i < n; ++i)
                puts(bd[i]);
            puts("");
        }
        return;
    }

    // do not place queen
    dfs(x, y+1, cnt);

    // place queen
    if (!row[x] && !col[y] && !dig[y-x+n] && !adig[y+x]) {  // x-y+n is also ok, at will
        row[x] = col[y] = dig[y-x+n] = adig[y+x] = 1;
        bd[x][y] = 'Q';
        dfs(x, y+1, cnt+1);
        bd[x][y] = '.';
        row[x] = col[y] = dig[y-x+n] = adig[y+x] = 0;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            bd[i][j] = '.';
    dfs(0, 0, 0);
    return 0;
}