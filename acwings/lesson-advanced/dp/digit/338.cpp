#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

/* Calculate: num sequence -> number value */
int getNum(vector<int>& nums, int lo, int hi) {
    int res = 0;
    for (int i = hi; i >= lo; --i)
        res = res * 10 + nums[i];
    return res;
}

int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res *= a;
        a *= a; k >>= 1;
    }
    return res;
}

/* Count x in [1, n] */
int count(int n, int x) {
    //printf("[test n = %d x = %d]\n", n, x);
    if (n == 0) return 0;
    /* Preprocess n */
    vector<int> nums;
    for (int i = n; i; i /= 10) nums.push_back(i % 10);
    n = nums.size();

    /* Deal: 1 <= zzz'x'yyy <= abc'd'efg */
    int res = 0;
    for (int i = n-1; i >= 0; --i) {
        //printf("calculate bit %d: %d\n", i, nums[i]);
        // case 1: zzz = 000 ~ abc-1
        if (i < n-1) {
            int zzz_cnt = getNum(nums, i+1, n-1);
            if (x == 0) zzz_cnt--;  // leading zero
            res += zzz_cnt * qmi(10, i);
            //printf("  case 1: %d\n", zzz_cnt * qmi(10, i));
        } //else printf("  case 1: 0\n");

        // case 2: zzz = abc
        if (x == nums[i]) {         //// x == d : yyy = 000 ~ efg
            res += getNum(nums, 0, i-1) + 1; 
            // printf("  case 2: %d\n", getNum(nums, 0, i-1) + 1);
        } else if (x < nums[i]) {   //// x <  d : yyy = 000 ~ 999
            if (i == n-1 && x == 0) continue;  // leading zero
            res += qmi(10, i);
            // printf("  case 2: %d\n", qmi(10, i));   
        }
    }
    return res;
}

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b), a && b) {
        if (a > b) swap(a, b);
        for (int i = 0; i <= 9; ++i) {
            printf("%d ", count(b, i) - count(a-1, i));
        }
        puts("");
    }

    return 0;
}