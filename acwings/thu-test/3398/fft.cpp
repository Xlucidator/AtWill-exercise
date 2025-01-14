#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
#include <string>

using namespace std;

#define DEBUG
#ifdef DEBUG
    #include <chrono>
    using namespace chrono;
#endif

const double PI = acos(-1);
using cd = complex<double>;
using cf = complex<float>;

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

vector<int> multiply(const vector<int>& a, int n, const vector<int>& b, int m) {
    /* Normalize: let total size to be 2^x */
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int size = 1;
    while (size < n + m - 1) size <<= 1;
    fa.resize(size); fb.resize(size);

    /* Calculate through FFT */
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < size; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = round(fa[i].real());
    }

    /* Back to Number */
    int system = 10; // for decimal system
    int carry = 0;
    for (int i = 0; i < size; ++i) {
        result[i] += carry;
        carry = result[i] / system;
        result[i] %= system;
    }
    // erase head zero
    while (result.size() > 1 && result.back() == 0) result.pop_back();

    return result;
}

inline void printVecNum(const vector<int>& vec_num) {
    for (int i = vec_num.size()-1; i >= 0; --i) {
        printf("%d", vec_num[i]);
    }
    printf("\n");
}

int main() {
    string sa, sb;
    cin >> sa >> sb;

    // sa, sb -> vec_a, vec_b
    vector<int> vec_a, vec_b;
    for (int i = sa.size()-1; i >= 0; --i) vec_a.push_back(sa[i] - '0');
    for (int i = sb.size()-1; i >= 0; --i) vec_b.push_back(sb[i] - '0');
    vector<int> vec_res = multiply(vec_a, vec_a.size(), vec_b, vec_b.size());
    printf("FFT result:\t");
    printVecNum(vec_res);

    // sa, sb -> a, b
    uint64_t a = 0, b = 0;
    for (int i = 0; i < sa.size(); ++i) {
        a *= 10;
        a += (sa[i] - '0');
    }
    for (int i = 0; i < sb.size(); ++i) {
        b *= 10;
        b += (sb[i] - '0');
    }
    uint64_t res = a * b;
    printf("Int result:\t%lu\n", res);

    return 0;
}