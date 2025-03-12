#include <iostream>
#include <cstring>

using namespace std;
const int N = 6;

char g[N][N], bg[N][N];
// use bit in int to store is better

/* Sequence:
 *     1
 *   4 5 2
 *     3
 */
const int dx[5] = {-1, 0, 1, 0, 0}, dy[5] = {0, 1, 0, -1, 0};  // store offset
void turn(int x, int y) {
    int a, b;
    for (int i = 0; i < 5; ++i) {
        a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= 5 || b < 0 || b >= 5) continue;
        g[a][b] ^= 1;   // '0' = 48, '1' = 49, only differs in last bit
    }
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        for (int i = 0; i < 5; ++i) scanf("%s", bg[i]);

        int res = 10;
        // first line cases: 00000 ~ 11111
        for (int op = 0; op < 32; op++) { 
            int cnt = 0;
            memcpy(g, bg, sizeof g);
            // operate first line
            for (int i = 0; i < 5; ++i) {
                if (op >> i & 1) {
                    turn(0, i);
                    cnt++;
                }
            }
            // other lines: iteration
            for (int i = 1; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (g[i-1][j] == '0') {
                        turn(i, j);
                        cnt++;
                    }
                }
            }
            // check
            bool success = true;
            for (int i = 0; i < 5; ++i) {
                if (g[4][i] == '0') {
                    success = false;
                    break;
                }
            }
            if (success && res > cnt) res = cnt;
        }
        if (res > 6) res = -1;
        printf("%d\n", res);
    } 
}