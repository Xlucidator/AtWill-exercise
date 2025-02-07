/* Closed Hashing + Open Addressing */

#include <iostream>
#include <cstring>

using namespace std;

const int N = 200003; // 2 ~ 3 times of input scale
const int NUL = 0x3f3f3f3f; // > 10^9

int h[N];

int find(int x) {
    int k = (x % N + N) % N;
    while (h[k] != NUL && h[k] != x) {
        k++;
        if (k == N) k = 0;
    }
    return k; // k in hash, then it's k; k not in hash, then it should be there
}

void insert(int x) {
    int k = find(x);
    h[k] = x;
}

bool query(int x) {
    int k = find(x);
    return h[k] == x;
}

int main() {
    int n;
    scanf("%d", &n);
    memset(h, 0x3f, sizeof h);

    char op; int x;
    while (n--) {
        scanf(" %c%d", &op, &x);
        if (op == 'I') {
            insert(x);
        } else if (op == 'Q') {
            printf(query(x) ? "Yes\n" : "No\n");
        }
    }

    return 0;
}