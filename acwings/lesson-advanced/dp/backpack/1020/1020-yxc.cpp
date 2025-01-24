// wrong answer

#include <cstring>
#include <iostream>

using namespace std;

const int N = 50, M = 160;

int n, m, K;
int f[N][M];

int main()
{
    cin >> n >> m >> K;

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;

    while (K--)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        for (int i = N - 1; i >= v1; i--)
            for (int j = M - 1; j >= v2; j--)
                f[i][j] = min(f[i][j], f[i - v1][j - v2] + w);
    }

    int res = 1e9;
    for (int i = n; i < N; i++)
        for (int j = m; j < M; j++)
            res = min(res, f[i][j]);

    cout << res << endl;

    return 0;
}