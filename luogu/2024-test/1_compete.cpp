#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, gp;

int seq[9];
bool flags[9];
int beat[9][9];

int test_round[9];
int ans;

inline bool test_win() {
    memcpy(test_round, seq, sizeof seq);
    int t, a, b;
    for (int g = gp; g >= 1; g >>= 1) {
        for (int i = 1; i <= g; ++i) {
            t = i << 1;
            a = test_round[t-1], b = test_round[t];
            test_round[i] = (beat[a][b] == 1) ? a : b;
        }
    }
    return test_round[1] == 1;
}

void dfs(int group) {
    if (group > gp) {
        // printf("[case] ");
        // for (int i = 1; i <= n; ++i) printf("%d ", seq[i]);
        // puts("");
        if (test_win()) ans++;
        return;
    }

    int pos = group << 1;
    for (int i = 1; i <= n; ++i) {
        if (flags[i]) continue;
        for (int j = i+1; j <= n; ++j) {
            if (flags[j]) continue;

            seq[pos-1] = i, seq[pos] = j;
            flags[i] = flags[j] = 1;
            dfs(group + 1);
            flags[i] = flags[j] = 0;
        }
    }
}

int main() {
    scanf("%d", &n); gp = n >> 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &beat[i][j]);
        }
    }
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         printf("%d ", beat[i][j]);
    //     }
    //     puts("");
    // }
    dfs(1);
    printf("%d\n", ans);

    return 0;
}