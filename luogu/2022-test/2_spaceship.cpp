#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int N = 4e5 + 2;
typedef long long ll;

int n, q;
multiset<ll> fleets[N];
multiset<ll>::iterator median_it[N];
ll bonus[N];

// fleets[x]: add level v ships
void add(int x, ll v) {
    v -= bonus[x];
    fleets[x].insert(v);

    if (fleets[x].size() == 1) median_it[x] = fleets[x].begin();
    else {
        if (v < *median_it[x]) {
            if (fleets[x].size() % 2 == 0) // after add: became even
                median_it[x]--;
        } else {
            if (fleets[x].size() % 2 == 1)
                median_it[x]++;
        }
    }
}

void remove(int x, multiset<ll>::iterator it) {
    if (fleets[x].empty()) return;

    if (fleets[x].size() % 2 == 1) { // former odd
        if (it == median_it[x]) {
            median_it[x] = fleets[x].erase(it);
            median_it[x]--;
        } else {
            if (distance(it, median_it[x]) > 0) median_it[x]--;
            fleets[x].erase(it);
        }
    } else {
        if (it == median_it[x]) {
            median_it[x] = fleets[x].erase(it);
        } else {
            if (distance(it, median_it[x]) < 0) median_it[x]++;
            fleets[x].erase(it);
        }
    }
}

// fleets[x]: add level v for all ships
void train(int x, ll v) {
    bonus[x] += v;
}

// move fleets[x].median to fleets[y]
void move(int x, int y) {
    if (fleets[x].empty()) return;
    
    add(y, *median_it[x] + bonus[x]);
    remove(x, median_it[x]);
}

// query flees[x].median
ll query(int x) {
    if (fleets[x].empty()) return 0;
    return *median_it[x] + bonus[x];
}

// move all ships from fleets[x] to fleets[y]
void merge(int x, int y) {
    if (fleets[x].size() > fleets[y].size()) {
        swap(fleets[x], fleets[y]);
        swap(bonus[x], bonus[y]); 
    }
    for (ll v: fleets[x])
        add(y, v + bonus[x]);

    fleets[x].clear();
    median_it[x] = fleets[x].end();
}

// remove ships that <= v from fleets[x]
void remove(int x, int v) {
    v -= bonus[x];
    auto& target = fleets[x];
    for (auto it = target.begin(); it != target.end() && *it <= v; it++) {
        it = target.erase(it);
    }
    median_it[x] = target.empty() ? target.end() : next(target.begin(), (target.size() - 1) / 2);
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
    }

    return 0;
}