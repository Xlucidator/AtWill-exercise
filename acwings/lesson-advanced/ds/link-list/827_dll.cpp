#include <iostream>
#include <string>

using namespace std;

const int N = 1e5 + 2;

int e[N], l[N], r[N], idx;

// 0 <-> 1
void init() { r[0] = 1, l[1] = 0, idx = 2; }

void insert_r(int k, int elm) {
    e[idx] = elm, l[idx] = k, r[idx] = r[k];
    l[r[k]] = idx, r[k] = idx++;
}

void insert_l(int k, int elm) {
    insert_r(l[k], elm);
}

void remove(int k) {
    r[l[k]] = r[k], l[r[k]] = l[k];
}

int main() {
    int M;
    cin >> M;
    init();

    while (M--) {
        string op;
        int x, k;
        cin >> op;
        if (op == "R") {
            cin >> x;
            insert_l(1, x);
        } else if (op == "L") {
            cin >> x;
            insert_r(0, x);
        } else if (op == "D") {
            cin >> k;
            remove(k+1); // the kth insert num located in (idx=k+1)
        } else if (op == "IL") {
            cin >> k >> x;
            insert_l(k+1, x);
        } else if (op == "IR") {
            cin >> k >> x;
            insert_r(k+1, x);
        }
    }

    int pos = r[0];
    while (pos != 1) {
        cout << e[pos] << " ";
        pos = r[pos];
    }
    cout << endl;

    return 0;
}