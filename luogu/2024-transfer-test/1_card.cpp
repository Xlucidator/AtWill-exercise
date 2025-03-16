#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 5000 + 10;
typedef long long ll;
typedef pair<ll, ll> pii;

int n, k;
vector<pii> cards; // <b, a>
ll res;
ll a_res, b_res;
vector<ll> seq;  // idx

void dfs(int sel_left, int low) {
    if (sel_left == 0) {
        res = max(res, a_res - b_res);
        return;
    }

    for (int i = low; i <= n - sel_left; ++i) {
        auto& c = cards[i]; ll b_add;
        if (seq.empty()) {
            a_res += c.second;
            seq.push_back(i);
            dfs(sel_left - 1, i + 1);
            seq.pop_back();
            a_res -= c.second;
        } else {
            b_add = c.first - cards[seq.back()].first;
            a_res += c.second;
            b_res += b_add;
            seq.push_back(i);
            dfs(sel_left - 1, i + 1);
            seq.pop_back();
            b_res -= b_add;
            a_res -= c.second;
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    int a, b;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        cards.push_back({b, a});
    }
    sort(cards.begin(), cards.end());

    dfs(k, 0);
    printf("%lld\n", res);

    return 0;
}