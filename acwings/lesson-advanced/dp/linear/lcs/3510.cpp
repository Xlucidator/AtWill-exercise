#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define USE_VECTOR

const int MAXN = 1e6+2;

int q[MAXN];
int hash_idx[MAXN]; // hash index of a
int n;

// LIS
#ifdef USE_VECTOR
    vector<int> dp_seq; // to use lower_bound
#else 
    int dp_seq[MAXN]; 
    int len;
#endif

int main() {
    scanf("%d", &n);
    int tmp;
    /* Read a[]: hash */
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        hash_idx[tmp] = i;
    }
    /* Read b[]: translate to LIS q[] */
    for (int i = 0; i < n; ++i) {
        scanf("%d", &tmp);
        q[i] = hash_idx[tmp]; // character out of a[] would be 0
    }


    for (int i = 0; i < n; ++i) {
        if (q[i] == 0) continue;
        int target = q[i];
    #ifdef USE_VECTOR
        auto it = lower_bound(dp_seq.begin(), dp_seq.end(), target);
        if (it == dp_seq.end()) dp_seq.push_back(target);
        else *it = target;
    #else 
        if (len == 0 || target > dp_seq[len-1]) dp_seq[len++] = target;
        else { // target <= dp_seq[len-1]
            int lo = 0, hi = len - 2, mi;
            while (lo <= hi) {
                mi = (lo + hi) >> 1;
                if (target <= dp_seq[mi]) hi = mi - 1;
                else lo = mi + 1;
            }
            dp_seq[lo] = target;
        }
    #endif
    }

#ifdef USE_VECTOR
    printf("%d\n", dp_seq.size());
#else 
    printf("%d\n", len);
#endif
    
    
    return 0;
}