#include <iostream>

using namespace std;

const int N = 1e5 + 2;

int f[N];
int n, m;

void init(int n) {
    for (int i = 1; i <= n; ++i) f[i] = i;
}

int find(int a) {
    int fa = f[a];
    for (fa = f[a]; fa != f[fa]; fa = f[a]) f[a] = f[fa];
    return fa;
}

void uunion(int a, int b) {
    int fa = find(a), fb = find(b);
    f[b] = f[fb] = fa;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    init(n);
    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'M') {
            uunion(a, b);
        } else if (op == 'Q') {
            printf(find(a) == find(b) ? "Yes\n" : "No\n");
        }
    }

    return 0;
}