#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int N = 4e5 + 2;
typedef long long ll;

int n, q;
multiset<ll> fleets[N];
// multiset<int>::iterator median_it;
ll bonus[N];

// fleets[x]: add level v ships
void add(int x, ll v) {
    fleets[x].insert(v-bonus[x]);
}

// fleets[x]: add level v for all ships
void train(int x, ll v) {
    if (fleets[x].empty()) return;
    bonus[x] += v;
}

// move fleets[x].median to fleets[y]
void move(int x, int y) {
    auto& from = fleets[x];
    if (from.empty()) return;
    auto it = next(from.begin(), (from.size()-1)/2);
    fleets[y].insert(*it + bonus[x] - bonus[y]);
    from.erase(it);
}

// query flees[x].median
ll query(int x) {
    auto& target = fleets[x];
    if (target.empty()) return 0;
    auto it = next(target.begin(), (target.size()-1)/2);
    return *it + bonus[x];
}

// move all ships from fleets[x] to fleets[y]
void merge(int x, int y) {
    auto& from = fleets[x];
    auto& to = fleets[y];
    if (from.size() > to.size()) {
        swap(from, to);
        swap(bonus[x], bonus[y]); 
    }
    for (int v: from)
        to.insert(v + bonus[x] - bonus[y]);
    from.clear();
    bonus[x] = 0;
}

// remove ships that <= v from fleets[x]
void remove(int x, ll v) {
    v -= bonus[x];
    auto& target = fleets[x];
    for (auto it = target.begin(); it != target.end() && *it <= v; it++) {
        it = target.erase(it);
    }
    if (target.empty()) bonus[x] = 0;
}

void print_fleets() {
    puts("[current state]");
    for (int i = 1; i <= n; ++i) {
        printf("\tfleets[%2d]: ", i);
        for (const ll& val : fleets[i]) {
            printf("%lld ", val + bonus[i]);
        }
        puts("");
    }
}

int main() {
    scanf("%d%d", &n, &q);

    int op;
    int x, y;
    while (q--) {
        scanf("%d%d", &op, &x);
        if (op == 4) {
            printf("%lld\n", query(x));
        } else {
            scanf("%d", &y);
            switch (op) {
                case 1: add(x, y); break;
                case 2: train(x, y); break;
                case 3: move(x, y); break;
                case 5: merge(x, y); break;
                case 6: remove(x, y); break;
                default: break;
            }
        }
        // print_fleets();
    }

    return 0;
}