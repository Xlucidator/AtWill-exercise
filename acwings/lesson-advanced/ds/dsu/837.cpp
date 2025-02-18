#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;

int p[N], cnt[N];
int n, m;

void init(int num) { 
    for (int i = 1; i <= num; ++i) p[i] = i, cnt[i] = 1;
}

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void uunion(int x, int y) {
    int py = find(y), px = find(x);
    p[py] = px;
    cnt[px] += cnt[py];
}

int main() {
    scanf("%d%d", &n, &m);
    init(n);
    
    char op[3];
    int a, b;
    while (m--) {
        scanf("%s%d", op, &a);
        int pa = find(a);
        if (op[0] == 'C') {
            scanf("%d", &b);
            if(pa != find(b)) uunion(a, b);
        } else if (op[0] == 'Q') {
            if (op[1] == '1') {
                scanf("%d", &b);
                puts(pa == find(b) ? "Yes" : "No");
            } else if (op[1] == '2') {
                printf("%d\n", cnt[pa]);
            }
        }
    }
    
    return 0;
}