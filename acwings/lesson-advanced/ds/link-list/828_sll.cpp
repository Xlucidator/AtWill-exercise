#include <iostream>

using namespace std;

const int N = 1e5 + 2;

int head, e[N], ne[N], idx;

void init() { head = -1, idx = 0; }

void insert(int k, int elm) {
    if (k == -1) { e[idx] = elm, ne[idx] = head, head = idx++; return; }
    e[idx] = elm, ne[idx] = ne[k], ne[k] = idx++;
}

void remove(int k) {
    if (k == -1) { head = ne[head]; return; }
    ne[k] = ne[ne[k]];
}

int main() {
    int M;
    init();

    cin >> M;
    while (M--) {
        char op;
        int k, x;
        cin >> op;
        if (op == 'H') {
            cin >> x;
            insert(-1, x);
        } else if (op == 'D') {
            cin >> k;
            remove(k-1);
        } else if (op == 'I') {
            cin >> k >> x;
            insert(k-1, x);
        }
    }

    int tar = head;
    while (tar != -1) {
        cout << e[tar] << " ";
        tar = ne[tar];
    }
    cout << endl;

    return 0;
}

#ifdef SELF_TRIAL

void insert(int pos, int elm) {
    if (pos == 0) {
        e[idx] = elm, ne[idx] = head, head = idx++;
        return;
    }

    int tar = head;
    while (--pos) tar = ne[tar];
    e[idx] = elm, ne[idx] = ne[tar], ne[tar] = idx++;
}

void remove(int pos) {
    if (pos == 0) {
        head = ne[head];
    }

    int tar = head;
    while (--pos) tar = ne[tar];
}

#endif