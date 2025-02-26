#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 2;

int m, p;
struct Node {
    int l, r;
    int max;
} tr[N<<2];

// caculate parent node 'u' from its schildren nodes
void pushup(int u) {
    tr[u].max = max(tr[u<<1].max, tr[u<<1 | 1].max);
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int m = (l + r) >> 1;
    build(u << 1, l, m); build(u << 1 | 1, m+1, r);
}

int query(int u, int l, int r) {
    // case 1: tr[u] belongs to [l, r]
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].max;

    // case 2: tr[u] intersects with [l, r], contain case 3 [l, r] belongs to tr[u]
    int m = (tr[u].l + tr[u].r) >> 1;
    int v = 0;
    if (l <= m) v = query(u << 1, l, r);
    if (r >  m) v = max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].max = v;
    else {
        int m = (tr[u].l + tr[u].r) >> 1;
        if (x <= m) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

int main() {
    int n = 0, last = 0;
    scanf("%d%d", &m, &p);
    build(1, 1, m);

    char op;
    int x;
    while (m--) {
        scanf(" %c%d", &op, &x);
        if (op == 'Q') {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        } else if (op == 'A') {
            modify(1, ++n, (unsigned)(x + last) % p);
            // attention: should be unsigned
        }
    }

    return 0;
}