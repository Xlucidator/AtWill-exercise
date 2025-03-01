#include <iostream>
#include <cstring>

using namespace std;

const int N = 3e4 + 2, M = 3e5 + 2;

typedef pair<int, int> pii;

int n, m;
// int h[N], e[M], ne[M], idx;
// bool flag[N];

bool g[N][N];
// int cnt[N];

int case_cnt[N][7]; // 1 ~ 6

void add(int a, int b) {
    g[a][b] = g[b][a] = 1;
    // e[idx] = b, ne[idx] = h[a], h[a] = e[idx++];
    // cnt[a]++; cnt[b]++;
}

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

// print x / y
inline void frac_print(int x, int y = 1) { 
    if (x == y) { x = y = 1; }
    else if (x == 0) { y = 1; }
    // else if (y % x == 0) { y = y / x; x = 1; }
    else {
        // if ((x % 2 == 0) && (y % 2 == 0)) {
        //     x >>= 1;
        //     y >>= 1;
        // }
        int gcd_num = gcd(x, y);
        x /= gcd_num;
        y /= gcd_num;
    }

    printf("%d/%d ", x, y);
}

void test_group(int a, int b, int c) {
    // case 1
    if (!g[a][b] && !g[b][c] && !g[a][c]) {
        case_cnt[a][1]++; case_cnt[b][1]++; case_cnt[c][1]++;
        return;
    } 

    // case 2/3 : one side
    if (g[a][b] && !g[b][c] && !g[a][c]) {
        case_cnt[c][2]++;
        case_cnt[a][3]++; case_cnt[b][3]++;
        return;
    }
    if (!g[a][b] && g[b][c] && !g[a][c]) {
        case_cnt[a][2]++;
        case_cnt[b][3]++; case_cnt[c][3]++;
        return;
    }
    if (!g[a][b] && !g[b][c] && g[a][c]) {
        case_cnt[b][2]++;
        case_cnt[a][3]++; case_cnt[c][3]++;
        return;
    }

    // case 4/5 tow side
    if (g[a][b] && g[b][c] && !g[a][c]) { // a - b - c
        case_cnt[b][4]++;
        case_cnt[a][5]++; case_cnt[c][5]++;
        return;
    }
    if (g[a][b] && !g[b][c] && g[a][c]) { // b - a - c
        case_cnt[a][4]++;
        case_cnt[b][5]++; case_cnt[c][5]++;
        return;
    }
    if (!g[a][b] && g[b][c] && g[a][c]) { // a - c - b
        case_cnt[c][4]++;
        case_cnt[a][5]++; case_cnt[b][5]++;
        return;
    }

    // case 6
    if (g[a][b] && g[b][c] && g[a][c]) {
        case_cnt[a][6]++; case_cnt[b][6]++; case_cnt[c][6]++;
        return;
    } 
}

void traverse() {
    for (int i = 1; i <= n-2; i++) {
        for (int j = i + 1; j <= n-1; ++j) {
            for (int k = j + 1; k <= n; ++k) {
                test_group(i, j, k);
            }
        }
    }
}

int main() {
    // memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);

    int x, y;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        add(x, y); // add(y, x);
    }

    int total_cnt = (n-1) * (n-2) / 2;
    traverse();
    for (int i = 1; i <= n; ++i) {
        frac_print(case_cnt[i][1], total_cnt);
        frac_print(case_cnt[i][2], total_cnt);
        frac_print(case_cnt[i][3], total_cnt);
        frac_print(case_cnt[i][4], total_cnt);
        frac_print(case_cnt[i][5], total_cnt);
        frac_print(case_cnt[i][6], total_cnt);
        puts("");
    }

    return 0;
}