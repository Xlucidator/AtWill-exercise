#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 2;

typedef unsigned long long ull;

int n;
int a[N], tr[N];  // tr[i]: the number of i that has appear (i in a[], or y_k)
int higher[N], lower[N];

inline int lowbit(int x) { return x & -x; }

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    // left -> right
    for (int i = 1; i <= n; ++i) {
        int y = a[i];
        higher[i] = sum(n) - sum(y);
        lower[i] = sum(y-1);
        add(y, 1);
    }

    memset(tr, 0, sizeof tr);
    ull res_down = 0, res_up = 0;
    // right -> left
    for (int i = n; i >= 1; --i) {
        int y = a[i];
                /* (0 -> i-1) i (i+1 -> n)*/
        res_down += higher[i] * (ull)(sum(n) - sum(y));
        res_up   += lower[i]  * (ull)(sum(y-1));
        add(y, 1);
    }

    printf("%lld %lld\n", res_down, res_up);
    
    return 0;
}