#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200 + 2, INF = 0x3f3f3f3f;

int d[N][N]; // dist from i to j <- from dp[k][i][j]
int n, m;

void floyd() {
    for (int k = 1; k <= n; ++k) { // attention: k out
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        } 
    }
}

int main() {
    cin.tie(0); int k;
    cin >> n >> m >> k;

    memset(d, 0x3f, sizeof d);
    for (int i = 1; i <= n; ++i) d[i][i] = 0;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        d[x][y] = min(d[x][y], z);
    }

    floyd();

    while (k--) {
        cin >> x >> y;
        if (d[x][y] < INF/2) cout << d[x][y] << endl;
        else cout << "impossible" << endl;   
    }
    
    return 0;
}
