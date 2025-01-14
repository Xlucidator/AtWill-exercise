#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

int N;
string str;
unordered_map<string, int> swap_cnt;

int bfs() {
    if (str.find("2012") != string::npos) return 0;

    queue<string> q;
    q.push(str);
    swap_cnt[str] = 0;
    while (!q.empty()) {
        string nxt = q.front(); q.pop(); // nxt: cur + swap one time
        int nxt_depth = swap_cnt[nxt] + 1;
        for (int i = 0; i < N-1; ++i) {
            swap(nxt[i], nxt[i+1]);
            if (swap_cnt.find(nxt) == swap_cnt.end()) { // prune : only different one need checks
                if (nxt.find("2012") != string::npos) 
                    return nxt_depth;
                q.push(nxt);
                swap_cnt[nxt] = nxt_depth;
            }
            swap(nxt[i], nxt[i+1]);
        }
    }
    return -1;
}


int main() {
    cin >> N >> str;
    int res = bfs();
    printf("%d\n", res);
    return 0;
}