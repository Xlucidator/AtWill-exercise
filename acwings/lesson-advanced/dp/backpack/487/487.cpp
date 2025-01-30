#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 32000 + 2, MAXM = 60 + 2;

struct Object {
    int v, vp;
    Object() {}
    Object(int v, int vp):v(v), vp(vp) {}
};

Object main_objs[MAXM];
vector<Object> sub_objs[MAXM];
int dp[MAXN];
int N, m;

int main() {
    cin >> N >> m;
    int v, p, q;
    for (int i = 1; i <= m; ++i) {
        cin >> v >> p >> q;
        if (q == 0) {
            main_objs[i] = {v, v * p};
        } else {
            sub_objs[q].emplace_back(v, v * p);
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (main_objs[i].v == 0) continue;
        auto& mobj = main_objs[i];
        for (int j = N; j >= mobj.v; --j) {
            auto& sobjs = sub_objs[i];
            int range = 1 << sobjs.size();
            for (int k = 0; k < range; ++k) {
                int v = mobj.v, w = mobj.vp;
                if (k & 0b01) v += sobjs[0].v, w += sobjs[0].vp;
                if (k & 0b10) v += sobjs[1].v, w += sobjs[1].vp;
                if (j >= v) dp[j] = max(dp[j], dp[j-v] + w);
            }
        }
    }

    cout << dp[N] << endl;

    return 0;
}