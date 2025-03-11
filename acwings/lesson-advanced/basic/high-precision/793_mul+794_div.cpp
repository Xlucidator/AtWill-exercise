#include <iostream>
#include <vector>
#include <algorithm> // reverse()

using namespace std;
const int N = 1e6 + 2;
#define DIV

/*=== A * b = C ===*/
vector<int> mul(vector<int>& A, int b) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || t; ++i) {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

/*=== A / b = C ... r ===*/
vector<int> div(vector<int>& A, int b, int& r) {
    vector<int> C;
    r = 0;
    for (int i = A.size()-1; i >= 0; --i) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    string a; int b;
    cin >> a >> b;
    vector<int> A;
    for (int i = a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');

#ifdef MUL
    auto C = mul(A, b);
    for (int i = C.size() - 1; i >= 0; --i) printf("%d", C[i]);
    puts("");
#endif

#ifdef DIV
    int r;
    auto C = div(A, b, r);
    for (int i = C.size() - 1; i >= 0; --i) printf("%d", C[i]);
    printf("\n%d\n", r);
#endif

    return 0;
}