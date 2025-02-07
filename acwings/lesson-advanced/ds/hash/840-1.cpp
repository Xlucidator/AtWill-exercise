/* Open Hashing + Close Addressing */
// Separate Chaining

#include <iostream>
#include <cstring>

using namespace std;

const int N = 100003; // first prime number over 1e5, calculate by programming

int h[N], e[N], ne[N], idx;

void insert(int x) {
    int k = (x % N + N) % N; // attention: to avoid negative number
    e[idx] = x, ne[idx] = h[k], h[k] = idx++; // insert head
}

bool query(int x) {
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])
        if (x == e[i]) return true;
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof h);

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