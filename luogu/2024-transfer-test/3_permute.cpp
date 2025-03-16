#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
const int N = 5e5 + 10;
typedef pair<int, int> pii; 

int n, k;
int a[N];
bool flags[N];
int tr[N]; // tree-array
// set<int> tr_back, tr;

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
    int l = 1, r = n, mid;
    int res;
    while (l <= r) {
        mid = l + r >> 1;
        if (k > sum(mid)) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

int main() {
    int T, p, x;
    scanf("%d", &T);

    vector<pii> limits;
    while (T--) {
        /* Clear 1 */
        limits.clear();

        /* New Round */
        // read in
        scanf("%d%d", &n, &k);
        // printf("[debug] n = %d, k = %d\n", n, k);
        bool fail = 0;
        for (int i = 0; i < k; ++i) {
            scanf("%d%d", &p, &x);
            if (!fail) {
                if (p < x) { fail = 1; continue; }
                limits.push_back({p, x});
            }
        }
        if (fail) {
            printf("-1\n");
            continue;
        }

        // Clear 2
        memset(flags, 0, n);
        memset(a, 0, sizeof a);
        memset(tr, 0, sizeof tr);
        for (int i = 1; i <= n; ++i) add(i, 1);
        // deal with legal limits
        sort(limits.begin(), limits.end(), greater<pii>());
        for (auto item: limits) {
            a[item.first] = findKthNumMin(item.second);
            add(a[item.first], -1);
            flags[a[item.first]] = 1;
        }

        /* Out */
        int free_num = 1;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0) {
                while (flags[free_num]) free_num++;
                printf("%d ", free_num++);
            } else {
                printf("%d ", a[i]);
            }
        }
        puts("");

        // int free_num = 1;
        // for (int i = 1; i <= n; ++i) {
        //     if (a[i] == 0) {
        //         while (flags[free_num]) free_num++;
        //         a[i] = free_num++;
        //     }
        // }
        // if (free_num > n + 1) printf("-1\n");
        // else {
        //     for (int i = 1; i <= n; ++i) {
        //         printf("%d ", a[i]);
        //     }
        //     puts("");
        // }
    }

    return 0;
}