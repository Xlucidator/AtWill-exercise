#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1e5, MAXNODE = 31 * 1e5;

int children[MAXNODE][2], idx = 1;
bool flag[MAXNODE];
int N;

int A[MAXN];

void insert(int a) {
    int p = 0;
    for (int i = 30; ~i/* i >= 0 */; --i) {
        int& s = children[p][(a >> i) & 0b1];
        if (!s) s = idx++;
        p = s;
    }
    flag[p] = 1;
}

int query(int a) {
    int p = 0, res = 0, u;
    for (int i = 30; ~i; --i) {
        u = a >> i & 0b1;
        res <<= 1;
        if (children[p][!u]) { // other side exists
            res += 1;
            u = !u;
        } 
        p = children[p][u];
    }
    return res;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
        insert(A[i]);
    }

    int res = 0;
    for (int i = 0; i < N; ++i)
        res = max(res, query(A[i]));
    printf("%d\n", res);

    return 0;
}