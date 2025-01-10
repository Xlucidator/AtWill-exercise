#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// #define DEBUG
#ifdef DEBUG
    #include <chrono>
    using namespace chrono;
#endif


const unsigned long long MOD = 1e9 + 7;
const int N = 1e5 + 1; 
const int M = 5 * 1e5 + 1;

uint64_t last_time = 0;

// struct Node {
//     vector<int> from, to;
// };
// Node* nodes[N];   // nodes[no] = node

int n;
int atime[N];
uint64_t ft[N], gt[N];
int in_degree[N], out_degree[N];
vector<int> from[N], to[N];

inline void topoSortRoundTrip() {
    queue<int> q;

    // Get ft
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
            ft[i] = 0;
        }
    }
    while (!q.empty()) {
        int nxt = q.front(); q.pop();
        for (int i: to[nxt]) { // Node* nxt_node = nodes[nxt]; nxt_node->to
            ft[i] = max(ft[i], atime[nxt] + ft[nxt]);
            last_time = max(last_time, ft[i] + atime[i]);

            if (--in_degree[i] == 0)
                q.push(i);
        }
    }

    // Get gt
    for (int i = 0; i < n; ++i) {
        gt[i] = last_time;
        if (out_degree[i] == 0) {
            q.push(i);
            gt[i] = last_time - atime[i];
        }
    }
    while (!q.empty()) {
        int nxt = q.front(); q.pop();
        for (int i: from[nxt]) { // Node* nxt_node = nodes[nxt]; nxt_node->from
            gt[i] = min(gt[i], gt[nxt] - atime[i]);

            if (--out_degree[i] == 0) {
                q.push(i);
            }
        }
    }
}

inline uint64_t quickMulMod(uint64_t a, uint64_t b) {
    uint64_t res = 0;
    while (b) {
        if (b & 1) res = (res + a) % MOD;
        a = (a << 1) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
#ifdef DEBUG
    auto start = high_resolution_clock::now();
#endif

    int m;
    scanf("%d%d", &n, &m);
 
    /* Read in */
    for (int i = 0; i < n; ++i) {
        scanf("%d", &atime[i]);
    }
    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        to[--u].push_back(--v); // nodes[--u]->to.push_back(--v);
        from[v].push_back(u);   // nodes[v]->from.push_back(u);
        out_degree[u]++;
        in_degree[v]++;
    }

    /* Algorithm: increase & decrease topo-sort */
    topoSortRoundTrip();

    /* Get result */
    uint64_t result = 1;
    for (int i = 0; i < n; ++i) {
        result = result * (gt[i] - ft[i] + 1) % MOD; // even slower in total
        // result = quickMulMod(result, gt[i] - ft[i] + 1);
    }
    printf("%lu\n%lu\n", last_time, result);

#ifdef DEBUG
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "[elapse time]: " << duration << " ms" << endl;
#endif

    return 0;
}
