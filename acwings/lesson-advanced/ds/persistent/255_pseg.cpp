#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 1e5 + 2, M = 1e4 + 2;
constexpr int logN = 17;

int n, m;
int a[N];
vector<int> nums;

struct Node {
    int l, r; // idx of left & right sons, not section [l, r]
    int cnt;
} tr[(N<<2) + N*logN];  // 6000,000 * 4B = 24MB
int root[N], idx = 1;

int find(int x) { return lower_bound(nums.begin(), nums.end(), x) - nums.begin(); }

int build(int l, int r) {
    int p = idx++;
    if (l == r) return p;

    int m = l + r >> 1;
    tr[p].l = build(l, m); tr[p].r = build(m+1, r);
    return p;
}

// modify -> insert
int insert(int p, int l, int r, int x) {
    int q = idx++;  // cur: q, pre: p
    tr[q] = tr[p];
    if (l == r) {
        tr[q].cnt++;
        return q;
    }

    int m = l + r >> 1;
    if (x <= m) tr[q].l = insert(tr[p].l, l, m, x);
    else tr[q].r = insert(tr[p].r, m+1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}

// query
int query(int p, int q, int l, int r, int k) {
    if (l == r) return r;

    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int m = l + r >> 1;
    if (k <= cnt) return query(tr[p].l, tr[q].l, l, m, k);
    else return query(tr[p].r, tr[q].r, m+1, r, k-cnt);
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size()-1);
    for (int i = 1; i <= n; ++i) 
        root[i] = insert(root[i-1], 0, nums.size()-1, find(a[i]));

    int l, r, k;
    while (m--) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[l-1], root[r], 0, nums.size()-1, k)]);
    }

    return 0;
}
