#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef pair<int, int> pii;
const int N = 5e4 + 2;
#define a first
#define b second

int n;
pii cow[N];

int main() {
    scanf("%d", &n);
    int w, s;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &w, &s);
        cow[i] = {w + s, w};
    }
    sort(cow, cow + n);

    int res = -1e9;
    for (int i = 0, sum = 0; i < n; ++i) {
        w = cow[i].b, s = cow[i].a - cow[i].b;
        res = max(res, sum - s);
        sum += w; 
    }
    printf("%d\n", res);
    
    return 0;
}