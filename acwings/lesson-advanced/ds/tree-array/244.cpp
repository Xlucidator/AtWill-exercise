#ifndef WRONG_CASE

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;

int n;
int A[N], a[N];
int tr[N];  // for set[N]

inline int lowbit(int x) { return x & -x; }

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int findKthNumMin(int k) {
    // printf("[find %dth num]\n", k);
    int l = 1, r = n, mid;
    int res;
#ifndef BETTER
    while (l <= r) {
        mid = (l + r) >> 1;
        if (k > sum(mid)) l = mid + 1;
        else r = mid - 1;  // k <= res
    }
#else
    while (l < r) {
        mid = (l + r) >> 1;
        if (k > sum(mid)) l = mid + 1;
        else r = mid;
    }
#endif
    return l;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) scanf("%d", &A[i]);

#ifndef BETTER
    for (int i = 1; i <= n; ++i) add(i, 1);
#else
    for (int i = 1; i <= n; ++i) tr[i] = lowbit(i);
#endif
    for (int i = n; i >= 1; --i) {
        a[i] = findKthNumMin(A[i] + 1);
        add(a[i], -1);
    }

    for (int i = 1; i <= n; ++i) printf("%d\n", a[i]);

    return 0;
}


#else

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;

int n;
int A[N], a[N];
int tr_b_A2a[N]; // tree array of the difference array of A2a[]

inline int lowbit(int x) { return x & -x; }

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr_b_A2a[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr_b_A2a[i];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) scanf("%d", &A[i]);

    // init tr_b_A2a[] : A2a[] = 1, 2, 3, 4, ..., n  => b_A2a[] = 1, 1, ..., 1
    for (int i = 1; i <= n; ++i) add(i, 1);
    for (int i = n; i >= 1; --i) {
        a[i] = sum(A[i] + 1);
        add(A[i]+1, 1);
    }

    for (int i = 1; i <= n; ++i) printf("%d\n", a[i]);

    return 0;
}

#endif