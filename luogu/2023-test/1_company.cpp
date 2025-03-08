#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 2;

int n, m;
int a[N];
double s[N];
int cnt[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    int x, y;
    while (m--) {
        scanf("%d%d", &x, &y);
        s[x] += a[y];
        cnt[x] ++;
    }

    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] > 0 && (s[i] / cnt[i] > a[i])) res++;
    }
    printf("%d\n", res);

    return 0;
}