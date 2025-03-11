#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const double PI = acos(-1);

#ifdef USE_STL

#include <complex>
using cd = complex<double>;
// using cf = complex<float>;

#else

template<typename T>
struct complex {
    T x, y;
    complex (T xx = 0, T yy = 0){ x = xx, y = yy; }
    T real() const { return x; }
    friend complex operator+(const complex& a, const complex& b){ return complex(a.x + b.x , a.y + b.y); }
    friend complex operator-(const complex& a, const complex& b){ return complex(a.x - b.x , a.y - b.y); }
    friend complex operator*(const complex& a, const complex& b){ return complex(a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x); }
    friend complex operator/(const complex& a, const T& b) { return complex(a.x / b, a.y / b); }
    complex& operator*=(const complex& b) { return *this = *this * b; }
    complex& operator/=(const T& b) { return *this = *this / b; }
    // friend complex& operator*=(complex& a, const complex& b) { return a = a * b; }
    // friend complex& operator/=(complex& a, const T& b) { return a = a / b; }
};
using cd = complex<double>;

#endif

void fft(vector<cd>& p, bool invert) {
    int n = p.size(); 
    if (n == 1) return; // P(x) = c : P(w) = c
    // assert((n & (n - 1)) == 0); // assume n is the power of 2

    /* Split to Pe & Po : P(x) = Pe(x^2) + xPo(x^2) */
    vector<cd> pe(n/2), po(n/2);
    for (int i = 0; i < n; i += 2) {
        pe[i>>1] = p[i];
        po[i>>1] = p[i+1];
    }

    /* Recursive Solving */
    fft(pe, invert); // P even
    fft(po, invert); // P odd 

    /* Merge Pe & Po */
    double angle = 2 * PI / n * (invert ? -1 : 1); // invert: still need 1/n
    cd w(1), wn(cos(angle), sin(angle));
    for (int i = 0; (i << 1) < n; i++) {
        // Caculate using Odevity : w^i, w^{i+n/2} are pm paired
        p[i]       = pe[i] + w * po[i];
        p[i + n/2] = pe[i] - w * po[i];
        // invert: make up the 1/n in the end
        if (invert) {
            p[i] /= 2;
            p[i + n/2] /= 2;
        }
        // Next Pair
        w *= wn; 
    }
}

vector<int> mul(vector<int>& A, vector<int>& B) {
    /* Normalize: let total size to be 2^x */
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    int size = 1;
    int max_size = A.size() + B.size() - 1; // n + m + 1 = (n+1) + (m+1) - 1 
    while (size < max_size) size <<= 1;
    fa.resize(size); fb.resize(size);

    /* Calculate through FFT */
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < size; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> C(size);
    for (int i = 0; i < size; ++i) {
        C[i] = round(fa[i].real());
    }

    /* Back to Number */
#ifdef BACK_TO_NUM
    int system = 10; // for decimal system
    int carry = 0;
    for (int i = 0; i < size; ++i) {
        C[i] += carry;
        carry = C[i] / system;
        C[i] %= system;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
#else
    C.resize(max_size);
#endif
    return C;
}


int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> A, B; int v;
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &v);
        A.push_back(v);
    } // order = n, A.size() = n+1
    for (int i = 0; i <= m; ++i) {
        scanf("%d", &v);
        B.push_back(v);
    } // order = m, A.size() = m+1

    auto C = mul(A, B);

    // C.resize(n + m + 1);
    for (int i = 0; i < C.size(); ++i) printf("%d ", C[i]);
    puts("");

    return 0;
}