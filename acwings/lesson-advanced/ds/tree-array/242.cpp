#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e5 + 2;

int n, m;
int a[N];
ll tr[N]; // for b[N] : delta_a array

inline int lowbit(int x) { return x & -x; }

void add(int x, int c) { // (index, +c)
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

// no need: cannot overflow
ll sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    // change to b[], than init tr[]
    for (int i = 1; i <= n; ++i) add(i, a[i] - a[i-1]);

    char op;
    while (m--) {
        int l, r, d;
        scanf(" %c%d", &op, &l);
        if (op == 'C') {
            scanf("%d%d", &r, &d);
            add(l, d); add(r+1, -d);
        } else if (op == 'Q') {
            printf("%lld\n", sum(l));
        }
    }

    return 0;
}