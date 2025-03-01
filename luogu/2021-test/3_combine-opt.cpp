#include <iostream>

using namespace std;

const int N = 262143 + 2;

int n, p;
int a[N], b[N];
int c[N];

// i + j = k
void calculate_p1() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, k; (k = i+j) <= n; ++j) {
            c[k] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i - j = k
void calculate_p2() {
    int i;
    for (int k = 1; k <= n; ++k) {
        for (int j = 1; (i = j + k) <= n; ++j) {
            c[k] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i * j = k
void calculate_p3() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, k; (k = j * i) <= n; ++j) {
            c[k] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i / j = k
void calculate_p4() {
    for (int j = 1; j <= n; ++j) {
        for (int k = 1, i; (i = j * k) <= n; ++k) {
            c[k] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// [i / j] = k
void calculate_p5() {
    int i;
    for (int k = 1; k <= n; ++k) {
        for (int j = 1; (i = k * j) <= n; ++j) {
            for (int di = 0; di < j && i <= n; ++di, ++i) {
                c[k] += a[i] * b[j];
            }
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i & j = k
void calculate_p6() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            c[i&j] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i | j = k
void calculate_p7() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            c[i|j] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// i ^ j = k
void calculate_p8() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            c[i^j] += a[i] * b[j];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// min(i, j) = k
void calculate_p9() {
    for (int k = 1; k <= n; ++k) {
        c[k] += a[k] * b[k];
        for (int ij = k+1; ij <= n; ++ij) {
            c[k] += a[k] * b[ij] + a[ij] * b[k];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

// max(i, j) = k
void calculate_p10() {
    for (int k = 1; k <= n; ++k) {
        c[k] += a[k] * b[k];
        for (int ij = 1; ij < k; ++ij) {
            c[k] += a[k] * b[ij] + a[ij] * b[k];
        }
    }
    for (int k = 1; k <= n; ++k) printf("%d ", c[k]);
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);

    switch (p) {
        case 1: calculate_p1(); break;
        case 2: calculate_p2(); break;
        case 3: calculate_p3(); break;
        case 4: calculate_p4(); break;
        case 5: calculate_p5(); break;
        case 6: calculate_p6(); break;
        case 7: calculate_p7(); break;
        case 8: calculate_p8(); break;
        case 9: calculate_p9(); break;
        case 10: calculate_p10(); break;
        default: ;
    }
    
    puts("");
    return 0;
}