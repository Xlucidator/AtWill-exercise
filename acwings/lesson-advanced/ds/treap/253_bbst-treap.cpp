#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1e5 + 10, INF = 1e9;
#define LChild(p) (tr[tr[p].l])
#define RChild(p) (tr[tr[p].r])

int n;
struct Node {
    int l, r;
    int key, val;
    int cnt, size; // cnt: count of the number; size: node size of this subtree
} tr[N];
int root, idx;

void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int createNode(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void build() {
    createNode(-INF), createNode(INF);
    root = 1; tr[1].r = 2;
    pushup(root);
}

void zig(int& p) {
    int q = tr[p].l; 
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
    pushup(tr[p].r), pushup(p);
}

void zag(int& p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    pushup(tr[p].l), pushup(p);
}

void insert(int& p, int key) {
    if (!p) p = createNode(key);
    else if (tr[p].key == key) tr[p].cnt++;
    else {
        if (tr[p].key > key) {
            insert(tr[p].l, key);
            if (tr[tr[p].l].val > tr[p].val) zig(p);
        } else {
            insert(tr[p].r, key);
            if (tr[tr[p].r].val > tr[p].val) zag(p);
        }
    }
    pushup(p);
}

void remove(int& p, int key) {
    if (!p) return;
    if (tr[p].key == key) {
        if (tr[p].cnt > 1) tr[p].cnt--;
        else if (tr[p].l || tr[p].r) {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                zig(p);
                remove(tr[p].r, key);
            } else {
                zag(p);
                remove(tr[p].l, key);
            }
        } else p = 0;
    } else {
        if (tr[p].key > key) remove(tr[p].l, key);
        else remove(tr[p].r, key);
    }
    pushup(p);
}

int getRankByKey(int p, int key) {
    if (!p) return 0;
    if (tr[p].key == key) return tr[tr[p].l].size + 1;
    if (tr[p].key > key) return getRankByKey(tr[p].l, key);
    return tr[tr[p].l].size + tr[p].cnt + getRankByKey(tr[p].r, key);
}

int getKeyByRank(int p, int rank) {
    // printf("[Node %d] key = %d, size = %d, cnt = %d, find rank %d\n", p, tr[p].key, tr[p].size, tr[p].cnt, rank);
    // printf("\t[lchild Node %d] key = %d, size = %d, cnt = %d\n", tr[p].l, tr[tr[p].l].key, tr[tr[p].l].size, tr[tr[p].l].cnt);
    // printf("\t[rchild Node %d] key = %d, size = %d, cnt = %d\n", tr[p].r, tr[tr[p].r].key, tr[tr[p].r].size, tr[tr[p].r].cnt);
    if (!p) return INF;
    if (tr[tr[p].l].size >= rank) return getKeyByRank(tr[p].l, rank);
    // printf("[1]\n");
    if (tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
    // printf("[2]\n");
    return getKeyByRank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt); // miswrite getRankByKey
}

int getPrev(int p, int key) { // < key
    if (!p) return -INF;
    if (tr[p].key >= key) return getPrev(tr[p].l, key);
    return max(tr[p].key, getPrev(tr[p].r, key));
}

int getSucc(int p, int key) { // > key
    if (!p) return INF;
    if (tr[p].key <= key) return getSucc(tr[p].r, key);
    return min(tr[p].key, getSucc(tr[p].l, key));
}

int main() {
    build();
    scanf("%d", &n);

    int op, x;
    while (n--) {
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1: insert(root, x); break;
            case 2: remove(root, x); break;
            case 3: printf("%d\n", getRankByKey(root, x) - 1); break;
            case 4: printf("%d\n", getKeyByRank(root, x + 1)); break;
            case 5: printf("%d\n", getPrev(root, x)); break;
            case 6: printf("%d\n", getSucc(root, x)); break;
            default: break;
        }
    }

    return 0;
}