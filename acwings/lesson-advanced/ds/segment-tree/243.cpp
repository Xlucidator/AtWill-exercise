/* Rewrite with Segment Tree */

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;
typedef long long ll;

int n, m;
int A[N];
struct Node {
    int l, r;
    ll sum, add;
} tr[N<<2];


inline void pushup(Node& u, Node& l, Node& r) {
    u.sum = l.sum + r.sum;
}

inline void pushup(int u) {
    pushup(tr[u], tr[u<<1], tr[u<<1|1]);
}

inline void pushdown(Node& u, Node& l, Node& r) {
    if (u.add) {
        l.add += u.add; l.sum += (ll)(l.r - l.l + 1) * u.add;
        r.add += u.add; r.sum += (ll)(r.r - r.l + 1) * u.add;
        u.add = 0;
    }
}

inline void pushdown(int u) {
    pushdown(tr[u], tr[u<<1], tr[u<<1|1]);
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, A[r], 0};
        return;
    }

    tr[u] = {l, r};
    int m = l + r >> 1;
    build(u<<1, l, m); build(u<<1|1, m+1, r);
    pushup(u);
}

void modify(int u, int l, int r, ll d) {
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].sum += (ll)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
        return;
    }
    // need seperate
    pushdown(u);
    int m = tr[u].l + tr[u].r >> 1;
    if (l <= m) modify(u<<1, l, r, d);
    if (r >  m) modify(u<<1|1, l, r, d);
    pushup(u);
}

ll query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

    pushdown(u);
    int m = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= m) sum = query(u<<1, l, r);
    if (r >  m) sum += query(u<<1|1, l, r);
    return sum;
}

#ifdef ANOTHER
Node query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];

    pushdown(u);
    int m = tr[u].l + tr[u].r >> 1;
    if (r <= m) return query(u<<1, l, r);
    if (l >  m) return query(u<<1|1, l, r);
    Node left = query(u<<1, l, r), right = query(u<<1|1, l, r);
    Node res;
    pushup(res, left, right);
    return res;
}
#endif

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
    build(1, 1, n);

    char op;
    int l, r, d;
    while (m--) {
        scanf(" %c%d%d", &op, &l, &r);
        if (op == 'C') {
            scanf("%d", &d);
            modify(1, l, r, d);
        } else if (op == 'Q') {
            printf("%lld\n", query(1, l, r));
        }
    }

    return 0;
}