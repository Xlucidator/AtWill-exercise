#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int N = 32767 + 10, INF = 1e8;
typedef long long ll;

set<int> nums;
int n;

int main() {
    scanf("%d", &n);
    nums.insert(INF);
    nums.insert(-INF);

    int a;
    scanf("%d", &a); 
    nums.insert(a); n--;
    ll res = a;
    set<int>::iterator it_min, it_max;
    while (n--) {
        scanf("%d", &a);
        it_min = nums.lower_bound(a);
        if (*it_min != a) {
            // it_max = --upper_bound(nums.begin(), nums.end(), a);
            it_max = it_min;
            it_max--;
            res += min(abs(*it_min - a), abs(a - *it_max));
            nums.insert(a);
        }
    }
    printf("%lld\n", res);

    return 0;
}