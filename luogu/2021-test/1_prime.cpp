#include <iostream>

using namespace std;

inline bool testPrime(int x) {
    if ((x & 1) == 0) return false;
    for (int i = 3; i * i <= x; i +=2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int u;
    scanf("%d", &u);

    int offset = 10; int x;
    for (int i = 1; ; i += 2) {
        if (i > 100 && ((i / 10) % 10 == 0)) i += 10;
        if (i > 1000 && ((i / 100) % 10 == 0)) i += 100;
        if (i > 10000 && ((i / 1000) % 10 == 0)) i += 1000;
        if (i / offset != 0) {
            offset *= 10;
        }
        x = u * offset + i;
        // printf("[test] %d\n", x);
        if (testPrime(x)) {
            printf("%d\n", x);
            return 0;
        }
    }

    return 0;
}