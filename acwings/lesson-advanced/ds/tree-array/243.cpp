#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 1e5 + 2;

int a[N];
ll tr_b[N], tr_ib[N]; // b[i] prefix_sum, b[i] * i prefix_sum
int n, m;

inline int lowbit(int x) { return x & -x; }

void add(int x, ll c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr_b[i] += c;
        tr_ib[i] += c * x;  // be careful: should be x, not i
    }
}

ll sum(int l, int r) { // [l, r]
    // Calculate [0, l-1]
    ll l_res_b = 0, l_res_ib = 0;
    for (int i = l-1; i; i -= lowbit(i)) {
        l_res_b += tr_b[i];
        l_res_ib += tr_ib[i];
    }
    ll sum_l = l_res_b * l - l_res_ib;

    // Calculate [0, r]
    ll r_res_b = 0, r_res_ib = 0;
    for (int i = r; i; i -= lowbit(i)) {
        r_res_b += tr_b[i];
        r_res_ib += tr_ib[i];
    }
    ll sum_r = r_res_b * (r+1) - r_res_ib;

    return sum_r - sum_l;
}

void printArrayFromTree(ll* ar, int n, const char* name) {
    printf("[%s] ", name);
    for (int i = 1; i <= n; ++i) printf("%lld ", ar[n]);
    puts("");
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        add(i, a[i] - a[i-1]);
    }

    char op;
    int l, r, d;
    while (m--) {
        scanf(" %c%d%d", &op, &l, &r);
        if (op == 'C') {
            scanf("%d", &d);
            add(l, d); add(r+1, -d);
        } else if (op == 'Q') {
            printf("%lld\n", sum(l, r));
        }
    }

    return 0;
}


// Another Implementation
void add(ll tr[], int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

ll sum(ll tr[], int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

ll prefix_sum(int x) {
    return sum(tr_b, x) * (x + 1) - sum(tr_ib, x);
}