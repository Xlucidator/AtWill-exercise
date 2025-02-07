#include <iostream>

using namespace std;

const int N = 1e5 + 2;

int h[N], hsize;
int k;
int ph[N]; // ph[k]: p to h, the kth insert element's loc in heap; ph[k] = i
int hp[N]; // hp[i]: h to p, the insert sequence of element in h[i]   ; hp[i] = k

void heap_swap(int i, int j) {
    ph[hp[i]] = j, ph[hp[j]] = i;
    std::swap(hp[i], hp[j]);
    std::swap(h[i], h[j]);
}

void down(int x) {
    int t = x, sx = x << 1;
    if (sx <= hsize && h[sx] < h[t]) t = sx;
    if (sx+1 <= hsize && h[sx+1] < h[t]) t = sx+1;
    if (t != x) {
        heap_swap(t, x);
        down(t);
    }
}

void up(int x) {
    int fx;
    while ((fx = (x >> 1)) && h[fx] > h[x]) {
        heap_swap(x, fx);
        x = fx;
    }
}

void insert(int x) {
    h[++hsize] = x;
    hp[hsize] = ++k; ph[k] = hsize;
    up(hsize);
}

void delMin() {
    heap_swap(1, hsize--);
    down(1);
}

void remove(int k) {
    int loc = ph[k];
    heap_swap(loc, hsize--);
    up(loc); down(loc);
}

void update(int k, int x) {
    int loc = ph[k];
    h[loc] = x;
    up(loc); down(loc);
}

int main() {
    int n; scanf("%d", &n);
    char op[3];
    int k, x;
    while (n--) {
        scanf("%s", op);
        if (op[0] == 'I') { // can use !strcmp(op, "I");
            scanf("%d", &x);
            insert(x);
        } else if (op[0] == 'P') {
            printf("%d\n", h[1]);
        } else if (op[0] == 'D' && op[1] == 'M') {
            delMin();
        } else if (op[0] == 'D' && op[1] == '\0') {
            scanf("%d", &k);
            remove(k);
        } else if (op[0] == 'C') {
            scanf("%d%d", &k, &x);
            update(k, x);
        }
    }

    return 0;
}