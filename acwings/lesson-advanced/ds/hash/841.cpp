#include <iostream>

using namespace std;

typedef uint64_t ull;

const int N = 1e5 + 2;
const int P = 131;

int n, m;
char str[N];
ull h[N], p[N]; // p[i] is scale, p[i] == p^i

void init(int len) {
    p[0] = 1;
    for (int i = 1; i <= len; ++i) {
        p[i] = p[i-1] * P;
        h[i] = h[i-1] * P + str[i];
    }
}

ull get(int l, int r) {
    return h[r] - h[l-1] * p[r-l+1];
}

int main() {
    scanf("%d%d%s", &n, &m, str+1);

    init(n);

    int l1, r1, l2, r2;
    while (m--) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (get(l1, r1) == get(l2, r2)) puts("Yes");
        else puts("No");
    }

    return 0;
}