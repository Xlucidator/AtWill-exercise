#include <iostream>
#include <vector>

using namespace std;
const int N = 1e6 + 2;
#define SUB

/*=== A + B ===*/
vector<int> add(vector<int>& A, vector<int>& B) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || i < B.size(); ++i) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t) C.push_back(1);
    return C;
}

/*=== A - B ===*/
// A >= B 
bool compare(vector<int>& A, vector<int>& B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; --i)
        if (A[i] != B[i]) 
            return A[i] > B[i];
    return true;
}

// assume A >= B
vector<int> sub(vector<int>& A, vector<int>& B) { 
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); ++i) {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        t = (unsigned)t >> 31; // t = (t < 0) ? 1 : 0;
    }
    // clear leading zero
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    string a, b;
    vector<int> A, B;
    cin >> a >> b;
    for (int i = a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; --i) B.push_back(b[i] - '0');

#ifdef ADD
    auto C = add(A, B);
    for (int i = C.size() - 1; i >= 0; --i) printf("%d", C[i]);
    puts("");
#endif

#ifdef SUB
    bool pos;
    auto C = (pos = compare(A, B)) ? sub(A, B) : sub(B, A);
    if (!pos) printf("-");
    for (int i = C.size() - 1; i >= 0; --i) printf("%d", C[i]);
    puts("");
#endif


    return 0;
}