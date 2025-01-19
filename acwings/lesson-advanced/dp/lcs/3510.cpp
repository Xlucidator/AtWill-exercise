#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 1e6+2;

int q[MAXN];
int dp_seq[MAXN]; // LIS
int hash_idx[MAXN]; // hash index of a
int n;

int main() {
    scanf("%d", &n);
    int tmp;
    /* Read a[]: hash */
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        hash_idx[tmp] = i;
    }
    /* Read b[]: translate to q[] */
    for (int i = 0; i < n; ++i) {
        scanf("%d", &tmp);
        q[i] = hash_idx[tmp]; // character out of a[] would be 0
    }
    
    return 0;
}