#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 33000 + 10, INF = 1e8;
typedef long long ll;

int n;
struct Node {
    int l, r;
    int key, val;
} tr[N];
int root, idx;

int createNode(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    return idx;
}

void build() {
    createNode(-INF); createNode(INF);
    root = 1, tr[1].r = 2;
}

void zig(int& p) {
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
}

void zag(int& p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
}

void insert(int& p, int key) {
    if (!p) p = createNode(key);
    else if (tr[p].key != key) { // this case: do not care equal
        if (tr[p].key > key) {
            insert(tr[p].l, key);
            if (tr[p].val < tr[tr[p].l].val) zig(p);
        } else {
            insert(tr[p].r, key);
            if (tr[p].val < tr[tr[p].r].val) zag(p);
        }
    }
}

int getPred(int p, int key) {
    if (!p) return -INF;
    if (tr[p].key > key) return getPred(tr[p].l, key); // this case: can use equal
    return max(tr[p].key, getPred(tr[p].r, key));
}

int getSucc(int p, int key) {
    if (!p) return INF;
    if (tr[p].key < key) return getSucc(tr[p].r, key); // this case: can use equal
    return min(tr[p].key, getSucc(tr[p].l, key));
}

int main() {
    build();
    scanf("%d", &n);
    
    int a;
    scanf("%d", &a);
    ll res = a; insert(root, a);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &a);
        res += min(a - getPred(root, a), getSucc(root, a) - a);
        insert(root, a);
    }
    printf("%lld\n", res);

    return 0;
}