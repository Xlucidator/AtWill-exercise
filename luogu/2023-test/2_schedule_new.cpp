#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 5e5 + 10;
typedef pair<int, pair<int, int>> piii;

int n, m;
int no;
int task_map[N];

// link list
// int h, ne[N], be[N], idx = 1;
// int ep[N], en[N];
// int tail_idx;
int ep[N], en[N], l[N], r[N], idx;
int cnt;

priority_queue<piii> pq;

void ll_init() {
    r[0] = 1, l[1] = 0; // [0] <-> [1]
    idx = 2;
}

int ll_insert_r(int no, int prior, int k) {
    en[idx] = no, ep[idx] = prior;
    l[idx] = k, r[idx] = r[k];
    l[r[k]] = idx, r[k] = idx;
    task_map[no] = idx;
    return idx++;
}

int ll_insert_l(int no, int prior, int k) {
    return ll_insert_r(no, prior, l[k]);
}
 
void ll_remove(int k) {
    int tar_no = en[k];
    task_map[tar_no] = 0;
    r[l[k]] = r[k], l[r[k]] = l[k];
}

void add(int prior) {
    no++;
    if (cnt == m) { printf("ERR\n"); return; }

    int i = ll_insert_l(no, prior, 1);
    pq.push({prior, {no, i}});
    cnt++;
    printf("%d\n", no);
}

void add(int prior, int task_no) {
    no++;
    if (cnt == m || cnt == 0) { printf("ERR\n"); return; }

    int task_idx = task_map[task_no];
    if (task_idx == 0) { printf("ERR\n"); return; }
    int i = ll_insert_l(no, prior, task_idx);
    pq.push({prior, {no, i}});
    cnt++;
    printf("%d\n", no);
}

void schedule_q() {
    if (cnt == 0) { printf("ERR\n"); return; }

    int cur_no = en[r[0]];
    ll_remove(r[0]); 
    cnt--;
    task_map[cur_no] = 0;
    printf("%d\n", cur_no);
}

void schedule_pq() {
    if (cnt == 0) { printf("ERR\n"); return; }

    int cur_no;
    while (task_map[(cur_no = pq.top().second.first)] == 0) {
        pq.pop();
    }
    int idx_to_remove = pq.top().second.second;
    ll_remove(idx_to_remove);
    pq.pop();
    cnt--;
    task_map[cur_no] = 0;
    printf("%d\n", cur_no);
}

int main() {
    ll_init();
    scanf("%d%d", &n, &m);

    int op, a, x;
    while (n--) {
        scanf("%d", &op);
        // printf("[debug] op = %d\n", op);
        switch (op) {
            case 1: {
                scanf("%d", &a);
                add(a);
                break;
            }
            case 2: {
                scanf("%d%d", &a, &x);
                add(a, x);
                break;
            }
            case 3: schedule_q(); break;
            case 4: schedule_pq(); break;
            default: break;
        }
    }

    return 0;
}