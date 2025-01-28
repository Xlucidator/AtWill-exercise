// Backpack Concrete Method Display

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002, MAXV = 1002;

int v[MAXN], w[MAXN];
int dp[MAXN][MAXV]; // cannot compress 
bool select_q[MAXN][MAXV];
int N, V;

void printVec(int vec[][MAXV], int n, int m, const char* name) {
    printf("[%s]:\n", name);
    for (int i = 1; i <= n; ++i) {
        cout << "\ti=" << i << ": ";
        for (int j = 1; j <= m; ++j) {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> N >> V;

    for (int i = 1; i <= N; ++i) {
        cin >> v[i] >> w[i];
    }

    for (int i = N; i >= 1; i--) {
        for (int j = V; j >= 1; j--) {
            int not_use = dp[i+1][j];
            if (j >= v[i]) {
                int use = dp[i+1][j-v[i]]+w[i];
                if (use >= not_use) {
                    dp[i][j] = use;
                    select_q[i][j] = 1;
                    continue;
                }
            } 
            dp[i][j] = not_use;
            select_q[i][j] = 0;
        }
    }

    int j = V;
    for (int i = 1; i <= N; i++) {
        if (select_q[i][j]) {
            cout << i << " ";
            j -= v[i];
        }
    }
    cout << endl;

    return 0;
}