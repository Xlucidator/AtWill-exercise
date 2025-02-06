#include <iostream>

using namespace std;

const int N = 200 * 200 + 2;

int p[N];
int n;

#define value(x, y) (((y)-1) + ((x)-1) * n)  // start from (0, 0)

void init(int n2) { for (int i = 0; i < n2; ++i) p[i] = i; }

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void uunion(int a, int b) {
    p[find(b)] = find(a);
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    init(n * n);

    int x, y, va, vb;
    char op[2];
    int cnt = 0; bool flag = false;
    while (m--) {
        scanf("%d%d%s", &x, &y, op); // if (flag) continue;
        va = value(x, y);
        vb = op[0] == 'D' ? value(x+1, y) : value(x, y+1);
        cnt ++;
        if (find(va) == find(vb)) { flag = true; break; }
        uunion(va, vb);
    }

    if (flag) printf("%d\n", cnt);
    else printf("draw\n");

    return 0;
}