#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2000+2;
typedef long long ll;

int n, q;
vector<ll> fleets[N];
// ll bonus[N];

inline ll find_median(vector<ll>& fleet) { // return location
    int n = fleet.size();
    int mid = (n-1) / 2;
    nth_element(fleet.begin(), fleet.begin() + mid, fleet.end());
    swap(fleet[mid], fleet.back());
    return fleet.back();
}

// fleets[x]: add level v ships
void add(int x, ll v) {
    fleets[x].push_back(v); // -bonus[x]
}

// fleets[x]: add level v for all ships
void train(int x, ll v) {
    for (auto& num : fleets[x]) num += v;
}

// move fleets[x].median to fleets[y]
void move(int x, int y) {
    if (fleets[x].empty()) return;
    ll v = find_median(fleets[x]);
    add(y, v);
    fleets[x].pop_back();
}

// query flees[x].median
ll query(int x) {
    if (fleets[x].empty()) return 0;
    return find_median(fleets[x]);
}

// move all ships from fleets[x] to fleets[y]
void merge(int x, int y) {
    fleets[y].insert(fleets[y].end(), fleets[x].begin(), fleets[x].end());
    fleets[x].clear();
}

// remove ships that <= v from fleets[x]
void remove(int x, ll v) {
    fleets[x].erase(
        std::remove_if(fleets[x].begin(), fleets[x].end(), [&](long long num) { return num <= v; }),
        fleets[x].end()
    );
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