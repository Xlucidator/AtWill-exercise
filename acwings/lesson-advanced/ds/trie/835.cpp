#include <iostream>

using namespace std;

const int MAXN = 1e5+2, CHARSET = 26;

int N;
char str[MAXN];
int children[MAXN][CHARSET], cnt[MAXN], idx;
// for idx = p, children[p] is all the children node of node p, cnt[p] is the cnt of p

void init() { idx = 1; } // set idx = 0 the root node

void insert(char str[]) {
    int p = 0, u;
    for (int i = 0; str[i]; ++i) {
        u = str[i] - 'a';
        if (!children[p][u]) children[p][u] = idx++;
        p = children[p][u];
    }
    cnt[p] ++;
}

int search(char str[]) {
    int p = 0, u;
    for (int i = 0; str[i]; ++i) {
        u = str[i] - 'a';
        if (!children[p][u]) return 0;
        p = children[p][u];
    }
    return cnt[p];
}

int main() {
    scanf("%d", &N);
    init();
    while (N--) {
        char op;
        scanf(" %c%s", &op, str); // another way: ' %c' to escape white character
        if (op == 'I') {
            insert(str);
        } else if (op == 'Q') {
            printf("%d\n", search(str));
        }
    }
    return 0;
}