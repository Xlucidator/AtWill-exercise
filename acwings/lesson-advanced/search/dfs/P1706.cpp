#include <iostream>

using namespace std;

const int N = 11;

bool numset[N];
int seq[N];
int n;

void dfs(int pos) {
    if (pos > n) {
        for (int i = 1; i <= n; ++i) printf("%5d", seq[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (numset[i]) continue;
        seq[pos] = i;
        numset[i] = true;
        dfs(pos + 1);
        numset[i] = false;
    }
}

int main() {
    cin >> n;
    dfs(1);
    
    return 0;
}