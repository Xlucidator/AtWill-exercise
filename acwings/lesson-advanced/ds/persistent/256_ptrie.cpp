#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 6e5 + 2, M = N * 25;  // N: max len, M: trie nodes

int n, m;
// persistant trie
int root[N];
int tr[M][2], max_id[M], idx;
// prefix xor
int s[N];

void init() { idx = 1; }

// recursive version
void insert(int i, int k, int pre, int cur) { // i: s[i]   k: bit to deal with
    if (k < 0) {
        max_id[cur] = i;
        return;
    }

    int u = s[i] >> k & 1;
    if (pre) tr[cur][u ^ 1] = tr[pre][u ^ 1];
    tr[cur][u] = idx++;
    insert(i, k - 1, tr[pre][u], tr[cur][u]);
    max_id[cur] = max(max_id[tr[cur][0]], max_id[tr[cur][1]]);
}

int query(int rt, int c, int l) { // c = s[n] ^ x, [l, r] : r decides the root[r-1]
    int p = rt, u;
    for (int i = 23; i >= 0; i--) {
        u = c >> i & 1;
        if (max_id[tr[p][u^1]] >= l) p = tr[p][u^1];
        else p = tr[p][u];
    }
    return c ^ s[max_id[p]];
}

int main() {
    init();
    scanf("%d%d", &n, &m);

    // init version 0 for null 
    max_id[0] = -1;
    root[0] = idx++;
    insert(0, 23, 0, root[0]);

    int x;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        s[i] = s[i-1] ^ x;
        root[i] = idx++;
        insert(i, 23, root[i-1], root[i]);
    }

    char op;
    int l, r;
    while (m--) {
        scanf(" %c", &op);
        if (op == 'A') {
            scanf("%d", &x);
            n++, s[n] = s[n-1] ^ x;
            root[n] = idx++;
            insert(n, 23, root[n-1], root[n]);
        } else if (op == 'Q') {
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(root[r-1], s[n] ^ x, l-1));
        }
    }

    return 0;
}