#include <iostream>

const int N = 5e4 + 2;

int p[N], d[N]; // d[x]: dance of x to the root in its union-find set
// d[x] % 3 == 1: root eat x
// d[x] % 3 == 2: x eat root
// d[x] % 3 == 0: x equal root 
int n, k;

#define MOD3_POSI(x) (((x) % 3 + 3) % 3)
// C++ mod: res has the same sign with divident a ( a % b = res)
// -5 %  3 = -2 : -5+  3 =-2
// -5 % -3 = -2 : -5-(-3)=-2
//  5 % -3 =  2 :  5+(-3)= 2
//  5 %  3 =  2 :  5-  3 = 2

void init(int size) { for (int i = 0; i < size; ++i) p[i] = i; }

int find(int x) {
    if (x != p[x]) {
        int tmp = p[x];
        p[x] = find(p[x]);
        d[x] += d[tmp];
    }
    return p[x];
}

bool x_equal_y(int x, int y) { return (d[x] - d[y]) % 3 == 0; }

bool x_eat_y(int x, int y) { return MOD3_POSI(d[x] - d[y]) == 2; }


int main() {
    scanf("%d%d", &n, &k);
    init(n);

    int op, x, y;
    int cnt = 0;
    while (k--) {
        scanf("%d%d%d", &op, &x, &y);
        if (x > n || y > n) { cnt++; continue; }
        int px = find(x), py = find(y);
        if (op == 1) { // x equals y
            if (px == py) {
                if (!x_equal_y(x, y)) { cnt++; continue; }
            } else {
                p[px] = py;  // d[x] + d[px] - d[y] ≡ 0 (mod 3) => d[px] ≡ d[y] - d[x] (mod 3)
                d[px] = d[y] - d[x];
            }
        } else if (op == 2) { // x eat y
            if (x == y) { cnt++; continue; }
            if (px == py) {
                if(!x_eat_y(x, y)) { cnt++; continue; }
            } else {
                p[px] = py; // d[x] + d[px] - d[y] ≡ 2 (mod 3)
                d[px] = d[y] - d[x] + 2;
            }
        }
    }
    printf("%d\n", cnt);

    return 0;
}