#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = 5e5 + 2;

int n, m;
struct Node {
   int l, r;
   ll sum, gcd;  // sum: for prefix sum
} tr[N<<2];
ll A[N];

ll gcd(ll a, ll b) { 
    // if (a < 0) a = -a; if (b < 0) b = -b;
    return b ? gcd(b, a % b) : a; 
}

void pushup(Node& u, Node& l, Node& r) {
    u.sum = l.sum + r.sum;
    u.gcd = gcd(l.gcd, r.gcd);
}

void pushup(int u) {
    pushup(tr[u], tr[u<<1], tr[u<<1|1]);
}

void build(int u, int l, int r) {
    if (l == r) {
        ll b = A[r] - A[r-1];
        tr[u] = {l, r, b, b};
        return ;
    }
    
    tr[u] = {l, r}; // always forget haha
    int m = l + r >> 1;
    build(u<<1, l, m); build(u<<1|1, m+1, r);
    pushup(u);
}

Node query(int u, int l, int r) {
    if (l > r) return {0}; // important
    if (l <= tr[u].l && tr[u].r <= r) return tr[u]; // only self

    int m = tr[u].l + tr[u].r >> 1;
    if (r <= m) return query(u<<1, l, r);   // only left child
    if (l >  m) return query(u<<1|1, l, r); // only right child
    // both left & right
    Node left = query(u<<1, l, r), right = query(u<<1|1, l, r);
    Node res; pushup(res, left, right); 
    return res;
}

void modify(int u, int x, ll c) {
    if (tr[u].l == x && tr[u].r == x) {
        ll b = tr[u].sum + c;
        tr[u] = {x, x, b, b};
        return;
    }

    int m = tr[u].l + tr[u].r >> 1;
    if (x <= m) modify(u<<1, x, c);
    else modify(u<<1|1, x, c);
    pushup(u);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", &A[i]);
    build(1, 1, n);

    int l, r; ll d;
    char op;
    while (m--) {
        scanf(" %c%d%d", &op, &l, &r);
        if (op == 'Q') {
            Node left = query(1, 1, l);
            Node right = query(1, l+1, r);
            printf("%lld\n", abs(gcd(left.sum, right.gcd)));
        } else if (op == 'C') {
            scanf("%lld", &d);
            modify(1, l, d);
            if (r + 1 <= n) modify(1, r+1, -d);
        }
    }

    return 0;
}