#include <iostream>
#include <algorithm>

using namespace std;

#define COLLECT_MINV

const int MAXN = 102, MAXV = 102, MAXS = 102;

struct Object {
    int v, w;
    Object() {}
    Object(int volume, int weight): v(volume), w(weight) {}
};

#ifdef COLLECT_MINV
struct Group{
    vector<Object> objs;
    int min_v; // only a litter faster
};
Group groups[MAXN];
#else
vector<Object> groups[MAXN];
#endif
int dp[MAXV];
int N, S, V;


int main() {
    scanf("%d%d", &N, &V);

#ifdef COLLECT_MINV
    int tv, tw, minv;
    for (int i = 1; i <= N; i++) {
        auto& group = groups[i];
        auto& objs = group.objs;

        scanf("%d", &S);
        minv = MAXV;
        for (int j = 0; j < S; j++) {
            scanf("%d%d", &tv, &tw);
            objs.emplace_back(tv, tw);
            minv = min(minv, tv);
        }
        group.min_v = minv;
    }

    for (int i = 1; i <= N; ++i) {
        auto& group = groups[i];
        for (int j = V; j >= group.min_v; --j) {
            for (auto& obj : group.objs) {
                if (j >= obj.v) dp[j] = max(dp[j], dp[j-obj.v] + obj.w);
            }
        }
    }
#else
    int tv, tw;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S);
        for (int j = 0; j < S; j++) {
            scanf("%d%d", &tv, &tw);
            groups[i].emplace_back(tv, tw);
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = V; j >= 0; --j) {
            for (auto& obj : groups[i]) {
                if (j >= obj.v) dp[j] = max(dp[j], dp[j-obj.v] + obj.w);
            }
        }
    }
#endif

    printf("%d\n", dp[V]);

    return 0;
}