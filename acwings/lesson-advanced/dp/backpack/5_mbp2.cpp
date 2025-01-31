#define SIMPLE
#ifdef SIMPLE

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXV = 2002;

int dp[MAXV];
int N, V;

int main() {
    cin >> N >> V;
    int v, w, s;
    for (int i = 1; i <= N; ++i) {
        cin >> v >> w >> s;
        
        int k = 1, kv, kw;
        while (s) {
            kv = k * v, kw = k * w;
            for (int j = V; j >= kv; --j)
                dp[j] = max(dp[j], dp[j-kv] + kw);
            s -= k;
            k = min(s, k << 1);
        }
    }
    cout << dp[V] << endl;
    return 0;
}


#else

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXV = 2002, MAXS = 2002;
const int MAXN = 2000 * 11 + 2;

#define USE_PAIR
#define USE_SELF_STRUCT

#ifdef USE_PAIR
    #ifdef USE_SELF_STRUCT
        struct pii {
            int first, second;
            pii() {}
            pii(int v, int w): first(v), second(w) {}
        };
    #else
        typedef pair<int, int> pii;
    #endif
    vector<pii> objs(MAXN);
#else
    vector<int> v(MAXN), w(MAXN);
#endif
int N, V, realN;
int dp[MAXV];

int main() {
    int tv, tw, ts;
    scanf("%d%d", &N, &V);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &tv, &tw, &ts);
        for (int k = 1; k < ts; k <<= 1) {
        #ifdef USE_PAIR
            objs.emplace_back(tv * k, tw * k);
        #else
            v.push_back(tv * k); w.push_back(tw * k);
        #endif
            ts -= k;
        }
    #ifdef USE_PAIR
        objs.emplace_back(tv * ts, tw * ts);
    #else
        v.push_back(tv * ts); w.push_back(tw * ts);
    #endif
    }

#ifdef USE_PAIR
    for (auto& obj: objs) {
        for (int j = V; j >= obj.first; --j) {
            dp[j] = max(dp[j], dp[j-obj.first] + obj.second);
        }
    }
#else
    realN = v.size();
    for (int i = 0; i < realN; ++i) {
        for (int j = V; j >= v[i]; --j) {
            dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
        }
    }
#endif
    

    printf("%d\n", dp[V]);

    return 0;
}

#endif