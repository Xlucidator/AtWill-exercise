#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 1e5 + 2;

int n;
struct Segment {
    double x, y1, y2;
    int v; // value: +1, -1
    bool operator<(const Segment& other) const { return x < other.x; }
} segs[N<<1];

struct Node { // each segment-tree node represent a 'section', even for the leaf node
    int l, r;
    int cnt; 
    double len;
} tr[N<<3]; //  *2*4 = *8

vector<double> alls_y;

int find(double y) {
    return lower_bound(alls_y.begin(), alls_y.end(), y) - alls_y.begin();
}

void pushup(int u) {
    if (tr[u].cnt) tr[u].len = alls_y[tr[u].r + 1] - alls_y[tr[u].l];
    else { // cnt = 0, but children nodes may have len, only if it has (not leaf node)
        if (tr[u].l != tr[u].r) { // has children nodes
            tr[u].len = tr[u<<1].len + tr[u<<1|1].len;
        } else { // leaf node, than it's beyond remedy
            tr[u].len = 0.0;
        }
    }
    // printf("   pushup: tr[%d] = {cnt=%d, len=%f}\n", u, tr[u].cnt, tr[u].len);
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;

    int m = l + r >> 1;
    build(u<<1, l, m); build(u<<1|1, m+1, r);
}

void modify(int u, int l, int r, int c) {
    // printf(" modify: tr[%d] = {%d, %d, cnt=%d, len=%f}, (l = %d, r = %d), c = %d\n", u, tr[u].l, tr[u].r, tr[u].cnt, tr[u].len, l, r, c);
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].cnt += c;
        pushup(u); // update self if possible
        return;
    }

    int m = tr[u].l + tr[u].r >> 1;
    if (l <= m) modify(u<<1, l, r, c);
    if (r >  m) modify(u<<1|1, l, r, c);
    pushup(u);
}

int main() {
    double x1, y1, x2, y2; int k = 0;
    while (scanf("%d", &n), n) {
        // Read in & Discretize
        alls_y.clear();
        for (int i = 0, j = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            segs[j++] = {x1, y1, y2, 1};
            segs[j++] = {x2, y1, y2, -1};
            alls_y.push_back(y1); alls_y.push_back(y2);
        }
        sort(alls_y.begin(), alls_y.end());
        alls_y.erase(unique(alls_y.begin(), alls_y.end()), alls_y.end());
        
        // Operate & Segment Tree
        build(1, 0, alls_y.size()-2);  // 'size() points' means 'size()-1 sections' : [l,r] = [0, size()-2]
        // for point alls_y[0, 1, 2, 3], there are 3 intervals
        // we use interval as leaf node: tr[1] = {0, 2}, tr[1] = {0, 1}, tr[2] = {2, 2}, tr[3] = {0, 0}, tr[4] = {1, 1},
        //      where {0, 0} represents alls_y[0~1], {1, 1} represents alls_y[1~2], {2,2} represents alls_y[2~3] 
        sort(segs, segs + n*2);
        double res = 0.0;
        for (int i = 0; i < n * 2; ++i) {
            // printf("[seg %d] y1, y2 = (%f, %f), maps to (%d, %d)\n", i, segs[i].y1, segs[i].y2, find(segs[i].y1), find(segs[i].y2)-1);
            if (i > 0) {
                // printf("\ttr[1],len = %f, x interval = %f\n", tr[1].len, segs[i].x - segs[i-1].x);
                res += tr[1].len * (segs[i].x - segs[i-1].x);
            }
            modify(1, find(segs[i].y1), find(segs[i].y2) - 1, segs[i].v);
        }

        // Output
        printf("Test case #%d\n", ++k);
        printf("Total explored area: %.2lf\n\n", res);
    }
    return 0;
}