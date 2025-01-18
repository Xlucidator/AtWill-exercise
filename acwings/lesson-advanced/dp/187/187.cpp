#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 52;

int height[MAXN];
int up[MAXN], down[MAXN];
int n;

int min_size;

void dfs(int u, int usize, int dsize) {
#ifdef MYDEBUG
    printf("[dfs] u = %d uszie = %d, dsize = %d\n", u, usize, dsize);
    printf("\t up : "); for (int i = 0; i < usize; i++) printf("%d ",   up[i]); putchar('\n');
    printf("\tdown: "); for (int i = 0; i < dsize; i++) printf("%d ", down[i]); putchar('\n');
#endif

    if (usize + dsize >= min_size) return; // prune: no need to continue, cannot be smaller
    if (u == n) {
        min_size = usize + dsize;
        return;
    }

    int target = height[u];

    /* Case 1: add to up[] */
    int k = 0;
    /////////// Binary Method ///////////
#define BIN_METHOD
#ifdef BIN_METHOD
    if (usize == 0 || target <= up[usize-1]) {
        k = usize; // up[usize++] = target;
    } else { // target > up[usize-1]
        int lo = 0, hi = usize - 2, mi;
        while (lo <= hi) {
            mi = (lo + hi) >> 1;
            if (target > up[mi]) hi = mi - 1;
            else lo = mi + 1;
        }
        k = lo; // up[lo] = target;
    }
#else 
    while (k < usize && target <= up[k]) k++;
#endif
    /////////// Binary Method ///////////
    int record = up[k];
    up[k] = target;
    if (k < usize) dfs(u + 1, usize, dsize);
    else dfs(u + 1, usize + 1, dsize);
    up[k] = record;

    /* Case 2: add to down[] */
    k = 0;
    /////////// Normal Method ///////////
    while (k < dsize && target >= down[k]) k++;
    /////////// Normal Method ///////////
    record = down[k];
    down[k] = target;
    if (k < dsize) dfs(u + 1, usize, dsize);
    else dfs(u + 1, usize, dsize + 1);
    down[k] = record;
}

int main() {
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) {
            cin >> height[i];
        }

        min_size = n;
        dfs(0, 0, 0);

        cout << min_size << endl;
    }

    return 0;
}