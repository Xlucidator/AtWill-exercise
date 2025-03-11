#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 3e5 + 2;
typedef pair<int, int> pii;

int n, m;
int a[N], s[N]; // s is prefix sum

vector<int> alls;
vector<pii> add, query;

int find(int x) {
    int l = 0, r = alls.size() - 1;
    while (l < r) {  // // can use lower_bound(alls.)
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // alls[r] = x, but r in [0, xx]. we want to map to [1, xx]
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;

    // Read in all numbers that
    int x, c;
    for (int i = 0; i < n; ++i) {
        cin >> x >> c;
        add.push_back({x, c});

        alls.push_back(x);
    }
    int l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        query.push_back({l, r});

        alls.push_back(l); 
        alls.push_back(r);
    }

    // 'Cook' for Discretize : unique and sort
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    ////// start to operate
    // add operation
    for (auto item : add) {
        x = find(item.first);
        a[x] += item.second;
    }
    // for prefix sumary
    for (int i = 1; i <= alls.size(); ++i) s[i] = s[i-1] + a[i];
    // query operation
    for (auto item : query) {
        l = find(item.first); r = find(item.second);
        cout << s[r] - s[l-1] << endl;
    }

    return 0;
}