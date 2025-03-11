#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e5 + 2;

int n;
int a[N];
int st[N];

// return true when has duplication
// bool hasDup(int l, int r) { }  // no need

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int res = 0;
    for (int r = 0, l = 0; r < n; ++r) {
        st[a[r]]++;
        while (st[a[r]] > 1) {  // means has duplication
            st[a[l++]]--; // l would not move back
        }
        res = max(res, r - l + 1);
    }

    cout << res << endl;

    return 0;
}