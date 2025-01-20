#include <iostream>
#include <algorithm>

using namespace std;
#define CORRECT

const int MAXN = 1002, MAXV = 1002;


#ifdef CORRECT

int n, vlimit;
int volume[MAXN], weight[MAXN];
int dp[MAXV];

int main() {
    scanf("%d%d", &n, &vlimit);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &volume[i], &weight[i]);

    for (int i = 1; i <= n; ++i) {
        for (int j = volume[i]; j <= vlimit; ++j) {
            dp[j] = max(dp[j], dp[j-volume[i]] + weight[i]);
        }
    }

    printf("%d\n", dp[vlimit]);

    return 0;
}

#else

typedef pair<int, int> pii; // <volume, weight>

pii objs[MAXN];
float w_per_v[MAXN];
int n, vlimit;

int main() {
    scanf("%d%d", &n, &vlimit);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &objs[i].first, &objs[i].second);
        // w_per_v[i] = (float)objs[i].second / (float)objs[i].first;
    }

    sort(objs, objs + n, [](const pii& a, const pii& b){
        // int idx_a = &a - objs; printf("a = (%d, %d), idx_a = %d\n", a.first, a.second, idx_a);
        // int idx_b = &b - objs; printf("b = (%d, %d), idx_b = %d\n", b.first, b.second, idx_b);
        // return w_per_v[idx_a] > w_per_v[idx_b];
        float wpv_a = (float)a.second / a.first;
        float wpv_b = (float)b.second / b.first;
        if (wpv_a == wpv_b) {
            // ... no way
        }
        return wpv_a > wpv_b;
    });

    int maxw = 0, num;
    for (int i = 0; i < n; ++i) {
        auto obj = objs[i];
        num = vlimit / obj.first;

        maxw += num * obj.second;
        vlimit -= num * obj.first;
    }
    printf("%d\n", maxw);

    return 0;
}

#endif
