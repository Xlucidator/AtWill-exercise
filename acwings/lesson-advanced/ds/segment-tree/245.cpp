#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e5 + 2;

int n, m;
struct Node {
    int l, r;
    int tar_max;
    int prefix_max, suffix_max;  // for cross interval answer
    int sum; // sum of the interval, to calculate prefix_max/suffix_max
} tr[N<<2];

#define LCHILD(x) (tr[(x)<<1])
#define RCHILD(x) (tr[(x)<<1|1])

void pushup(Node& u, Node& l, Node& r) {
    u.tar_max = max(l.suffix_max + r.prefix_max, max(l.tar_max, r.tar_max));
    u.prefix_max = max(l.sum + r.prefix_max, l.prefix_max); // u.prefix_max = (l.prefix_max == l.sum) ? l.prefix_max + r.prefix_max : l.prefix_max;
    u.suffix_max = max(l.suffix_max + r.sum, r.suffix_max); // u.suffix_max = (r.suffix_max == r.sum) ? l.suffix_max + r.suffix_max : r.suffix_max;
    u.sum = l.sum + r.sum;
}

void pushup(int u) { pushup(tr[u], LCHILD(u), RCHILD(u)); }

#ifdef EMPTY_BUILD

void build(int u, int l, int r) {
    // generate current node
    tr[u] = {l, r};
    if (l == r) return;

    int m = (l + r) >> 1;
    build(u << 1, l, m); build(u << 1 | 1, m+1, r);
}

#else

int A[N];
void build(int u, int l, int r) {
    // generate current node
    tr[u] = {l, r};
    if (l == r) {
        tr[u] = {l, r, A[l], A[l], A[l], A[l]}; // Attension: may have slips
        return;
    }

    int m = (l + r) >> 1;
    build(u << 1, l, m); build(u << 1 | 1, m+1, r);
    pushup(u);
}

#endif

// troublesome
Node query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) 
        return tr[u];
    
    int m = (tr[u].l + tr[u].r) >> 1;
    if (r <= m) return query(u<<1, l, r);
    if (l >  m) return query(u<<1|1, l, r);
    // than l <= m < r
    auto left = query(u<<1, l, r);
    auto right = query(u<<1|1, l, r);
    Node res;
    pushup(res, left, right);
    return res;
}

void modify(int u, int x, int c) {
    if (tr[u].l == x && tr[u].r == x) {
        // tr[u].tar_max = tr[u].prefix_max = tr[u].suffix_max = tr[u].sum = c;
        tr[u] = {x, x, c, c, c, c};
        return;
    }
    
    int m = (tr[u].l + tr[u].r) >> 1;
    if (x <= m) modify(u << 1, x, c);
    else modify(u << 1 | 1, x, c);
    pushup(u);
}

int main() {
    scanf("%d%d", &n, &m);

#ifdef EMPTY_BUILD
    build(1, 1, n);
    int a;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        modify(1, i, a);
    }
#else
    for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
    build(1, 1, n);
#endif

    int op, x, y;
    while (m--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            if (x > y) swap(x, y);
            printf("%d\n", query(1, x, y).tar_max);
        } else if (op == 2) {
            modify(1, x, y);
        }
    }
    return 0;
}