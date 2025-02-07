#include <iostream>

using namespace std;

int main() {
    for (int i = 2e5 + 1; ; i += 2) {
        bool flag = true;
        for (int j = 3; j * j <= i; j += 2) {
            if (i % j == 0) {
                flag = false;
                break;
            }
        }
        if (flag) { printf("%d\n", i); break; }
    }
    return 0;
}