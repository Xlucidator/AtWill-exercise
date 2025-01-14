#include <iostream>
#include <algorithm>

#include <vector>

using namespace std;

void printVec(const vector<uint8_t>& vec, const char* name) {
    printf("[vector %s] ", name);
    for (auto i : vec) printf("%d ", i);
    putchar('\n');
}

void printVec(int (*arr)[MAX_M], int n, int m, const char* name) {
    printf("[vector %s]\n", name);
    for (int i = 0; i < n; ++i) {
        printf("\t[%d] ", i);
        for (int j = 0; j < m; ++j) {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }
}