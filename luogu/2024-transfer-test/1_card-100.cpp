#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int N = 5000 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
ll ans = -INF;
pii cards[N];
priority_queue<int, vector<int>, greater<int>> pq; // min heap

inline ll calculat_b(int l, int r) {
    return cards[r].first - cards[l].first;
}

int main() {
    scanf("%d%d", &n, &k);
    int a, b;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        cards[i] = {b, a};
    }
    sort(cards, cards + n);

    ll cur_res_a;
    for (int l = 0; l <= n - k; ++l) {
        cur_res_a = cards[l].second;
        int r = l + k - 1;
        pq = priority_queue<int, vector<int>, greater<int>>();
        // pq = {};

        for (int i = l + 1; i < r; ++i) {
            pq.push(cards[i].second);
            cur_res_a += cards[i].second;
        }
        ans = max(ans, cur_res_a + cards[r].second - calculat_b(l, r));
        while (++r < n) {
            if (k > 2 && pq.top() < cards[r-1].second) {
                pq.push(cards[r-1].second);
                cur_res_a += cards[r-1].second - pq.top(); pq.pop();
            }
            ans = max(ans, cur_res_a + cards[r].second - calculat_b(l, r));
        }
    }
    printf("%lld\n", ans);

    return 0;
}