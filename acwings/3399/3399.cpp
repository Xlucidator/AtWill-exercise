#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const long long MOD = 1e9 + 7;
const int N = 1e5 + 1; 
const int M = 5 * 1e5 + 1;
const int INF = 0x7fffffff;

int n;
uint64_t last_time = 0;

struct Node {
    int time = -1;
    uint64_t ft = 0;
    uint64_t gt = INF;
    vector<int> from, to;
    Node(int t):time(t) {}
    ~Node() = default;
    inline void setFt(uint64_t in_ft) { ft = max(ft, in_ft); last_time = max(ft + time, last_time); }
    inline void setGt(uint64_t in_nxt_gt) { gt = min(gt, in_nxt_gt - time); }
    inline uint64_t getResult() { return gt - ft + 1; }
};

Node* nodes[N];   // nodes[no] = node
// int atime[N];
// uint64 ft[N], gt[N];
int in_degree[N], out_degree[N];


void topoSortRoundTrip() {
    queue<int> q;

    // Get ft
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
            nodes[i]->ft = 0;
        }
    }
    while (!q.empty()) {
        int nxt = q.front(); q.pop();
        Node* nxt_node = nodes[nxt];
        for (int i: nxt_node->to) {
            nodes[i]->setFt(nxt_node->time + nxt_node->ft); // also calculate last_time

            if (--in_degree[i] == 0) {
                q.push(i);
            }
        }
    }

    // Get gt
    for (int i = 0; i < n; ++i) {
        Node* node = nodes[i];
        if (out_degree[i] == 0) {
            q.push(i);
            node->gt = last_time - node->time;
        }
    }
    while (!q.empty()) {
        int nxt = q.front(); q.pop();
        Node* nxt_node = nodes[nxt];
        for (int i: nxt_node->from) {
            nodes[i]->setGt(nxt_node->gt);

            if (--out_degree[i] == 0) {
                q.push(i);
            }
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
 
    /* Read in */
    int time;
    for (int i = 0; i < n; ++i) {
        cin >> time;
        nodes[i] = new Node(time);
    }
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        nodes[--u]->to.push_back(--v);
        nodes[v]->from.push_back(u);
        out_degree[u]++;
        in_degree[v]++;
    }

    /* Algorithm: increase & decrease topo-sort */
    topoSortRoundTrip();

    /* Get result */
    uint64_t result = 1;
    for (int i = 0; i < n; ++i) {
        result = result * nodes[i]->getResult() % MOD;
    }
    cout << last_time << endl << result << endl;

    return 0;
}
