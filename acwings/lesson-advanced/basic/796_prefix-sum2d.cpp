#include <iostream>

using namespace std;
const int N = 1000 + 2;

int n, m, q;
int s[N][N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m >> q;
    int a;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a;
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a;
        }
    }

    int x1, y1, x2, y2;
    while (q--) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1] << endl;
    }

    return 0;
}