#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e5 + 2;
typedef pair<int, int> pii;

int n;
pii s[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    int l, r;
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        s[i] = {l, r};
    }

    // merge
    sort(s, s + n);
    int res = 1; int st = s[0].first, ed = s[0].second;
    for (int i = 1; i < n; ++i) {
        pii& cur = s[i];
        l = cur.first, r = cur.second;
        if (l > ed) {
            st = l, ed = r;
            res += 1;
        } else ed = max(ed, r);
    }

    printf("%d\n", res);

    return 0;
}

