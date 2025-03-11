#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e5 + 2;

int A[N], B[N];
int n, m;
int x;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> x;
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int j = 0; j < m; ++j) cin >> B[j];

    int res;
    for (int i = 0, j = m - 1; i < n; ++i) {
        while (j >= 0 && (res = A[i] + B[j]) > x) j--;
        if (res == x) {
            cout << i << " " << j << endl;
            break;
        }
    }

    return 0;
}