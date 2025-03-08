#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 5e5 + 2;
typedef pair<int, int> pii;
// struct pii {
//     int no, prior, idx;
// };

int n, m;
int no;
bool finished[N];
// int task_map[N];

// common queue: link list
int h, ne[N], idx;
int ep[N], en[N];
int* tail; // reverse: tail is the queue top
int cnt;
// deque<pii> q;

// priority queue
priority_queue<pii> pq;

void ll_pushback(int no, int prior) {
    // en[idx] = no, ep[idx] = prior;
    // if (tail_idx == -1) {
    //     ne[idx] = h, h = idx;
    // } else {
    //     ne[idx] = ne[tail_idx], ne[tail_idx] = idx;
    // }
    // tail_idx = idx++;

    en[idx] = no, ep[idx] = prior, ne[idx] = *tail, *tail = idx;
    tail = &(ne[idx]);
    idx++;
    // if (*tail != -1) tail = &(ne[*tail]);
}

void ll_pushfront(int no, int prior) {
    en[idx] = no, ep[idx] = prior, ne[idx] = h, h = idx;
    // if (tail_idx == -1) tail_idx = idx - 1;
    if (*tail != -1) tail = &(ne[*tail]);
    idx++;
}

void ll_remove(int k) {
    if (k == -1) { // remove head
        if (tail == &(ne[h])) tail = &h;
        h = ne[h]; 
        return; 
    }
    if (tail == &(ne[ne[k]])) tail = &(ne[k]);
    ne[k] = ne[ne[k]];
}

void add(int prior) {
    no++;
    if (cnt == m) { printf("ERR\n"); return; }

    // q.push_back({no, prior});
    ll_pushback(no, prior);
    pq.push({prior, no});
    cnt++;
    printf("%d\n", no);
}

void add(int prior, int task_no) {
    no++;
    if (cnt == m || cnt == 0) { printf("ERR\n"); return; }
    // if (finished[task_no]) { printf("ERR\n"); return; }

    /* not full, not empty */
    // head
    if (en[h] == task_no) {
        if (finished[task_no]) {
            ll_remove(-1); // remove first elm
            printf("ERR\n"); return;
        }
        ll_pushfront(no, prior);
        pq.push({prior, no});
        cnt++;
        printf("%d\n", no);
        return;
    }
    // other
    int cur_no;
    // int pre_i = h;
    for (int pre_i = h, i = ne[pre_i]; i != -1; pre_i = i, i = ne[i]) {
        cur_no = en[i];
        if (cur_no == task_no) {
            if (finished[cur_no]) {
                ll_remove(pre_i);
                printf("ERR\n"); return;
            }
            en[idx] = no, ep[idx] = prior, ne[idx] = ne[pre_i], ne[pre_i] = idx++;
            pq.push({prior, no});
            cnt++;
            printf("%d\n", no);
            return;
        }
    }
    printf("ERR\n");
}

void schedule_q() {
    if (cnt == 0) { printf("ERR\n"); return; }
    int cur_no;
    while (/* h != -1 && */finished[(cur_no = en[h])]) {
        // ll_remove(-1);
        h = ne[h];
    }
    ll_remove(-1); cnt--; finished[cur_no] = 1;
    printf("%d\n", cur_no);
}

void schedule_pq() {
    if (cnt == 0) { printf("ERR\n"); return; }
    int cur_no;
    while (/* !pq.empty() && */finished[(cur_no = pq.top().second)]) {
        pq.pop();
    }
    pq.pop(); cnt--; finished[cur_no] = 1;
    printf("%d\n", cur_no);
}

int main() {
    h = -1; tail = &h;
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
