#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1e6 + 2;

int n, c;
int a[N];

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    if (c <= 2) { printf("0\n"); return 0; }
    sort(a, a+n);

    int limit = (c-1) / 2 + 1;
    int res = 0; int cnt;
    for (int i = 0; i < n-2; ++i) {
        for (int j = 1; j < n-1; ++j) {
            if (a[j]-a[i] >= limit) continue;
            int max = a[j] + limit - 1;
            int min = a[i] + c - limit + 1;
            // a[k]: should be min <= a[k] <= max
            // for (int k = 2; k < n; ++k) {
            //     if (a[k]-a[j] >= limit) continue;
            //     if (a[i]+c-a[k] >= limit) continue;
            //     res ++;
            // }
            int* low = lower_bound(a+j+1, a+n, min);
            int* high = upper_bound(a+j+1, a+n, max);
            cnt = high - low;
            if (cnt > 0) res += cnt;
        }
    }
    printf("%d\n", res);

    return 0;
}