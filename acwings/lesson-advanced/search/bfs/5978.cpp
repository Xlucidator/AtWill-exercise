#include <iostream>
#include <cstring>

using namespace std;

const int N = 42;

struct Coord { 
    uint8_t x, y;
    Coord() {}
    Coord(int x, int y):x(x), y(y) {}
};

char g[N][N];
int d[N][N];
int r, c;

Coord q[N * N];

int dir[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

inline bool inbound(int x, int y) { return 0 <= x && x < r && 0 <= y && y < c; }

int bfs() {
    int head = 0, tail = 0;
    q[0] = {0, 0};

    memset(d, -1, sizeof d);
    d[0][0] = 1;  // contain start point

    int x, y;
    while (head <= tail) {
        auto& coord = q[head++];
        for (int i = 0; i < 4; ++i) {
            x = coord.x + dir[i][0];
            y = coord.y + dir[i][1]; 
            if (inbound(x, y) && g[x][y] == '.' && d[x][y] == -1) {
                d[x][y] = d[coord.x][coord.y] + 1;
                q[++tail] = {x, y};
            }
        }
    }

    return d[r-1][c-1];
}

int main() {
    cin.tie(0);
    cin >> r >> c;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> g[i][j];
    cout << bfs() << endl;
    return 0;
}