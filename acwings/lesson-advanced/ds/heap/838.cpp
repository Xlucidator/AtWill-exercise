#include <iostream>

using namespace std;

const int N = 1e5 + 2;

int h[N], hsize; // x start from 1
int n, m;

void swap(int i, int j) { int tmp = h[i]; h[i] = h[j], h[j] = tmp; }

// min heap
// total heapsort: max heap would be properer, but not for this problem

void up(int x) {  // non-recursive version
    int fx;
    while ((fx = x<<1) && h[fx] > h[x]) {
        swap(x, fx);
        x = fx;
    }
}

void down(int x) { // recursive version
    int sx = x << 1, t = x;
    if (sx <= hsize && h[sx] < h[t]) t = sx;
    if (sx + 1 <= hsize && h[sx+1] < h[t]) t = sx + 1;
    if (t != x) { swap(t, x); down(t); }
} // 100 0000 elms -> height = 20, so recursive is entirely ok

void delMin() { h[1] = h[hsize]; hsize--; down(1); }

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    hsize = n;

    for (int i = hsize / 2; i >= 1; --i) down(i);

    while (m--) {
        printf("%d ", h[1]);
        delMin();
    }
    puts("");
    
    return 0;
}