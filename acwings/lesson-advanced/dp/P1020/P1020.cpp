/* Luogu P1020 <=> acwings 1010 */
// LIS: greedy & binary search

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

const int MAXN = 1e5+10;

int height[MAXN];
int dp_seq[MAXN];
int n = 0;
int len = 0, cnt = 0;

void printSeq(int size) {
    printf("[dp_seq] ");
    for (int i = 0; i < size; ++i) printf("%d ", dp_seq[i]);
    printf("size = %d \n", size);
}

int main() {
    // string line;
    // getline(cin, line);
    // stringstream ssin(line);
    // while (ssin >> height[n]) n++;

    while (cin >> height[n]) n++;

    /* Question 1 */
    // Size of Longest Non-Increase Subsequence
    dp_seq[len++] = height[0];
    for (int i = 1; i < n; ++i) {
        int target = height[i];
        if (target <= dp_seq[len-1]) {
            dp_seq[len++] = target;
        } else { // target > dp_seq[len-1]
            int lo = 0, hi = len - 2, mi;
            while (lo <= hi) {
                mi = (lo + hi) >> 1;
                if (target > dp_seq[mi]) hi = mi - 1; // [tips]: has the same direction as the current branch
                else lo = mi + 1;
            }
            dp_seq[lo] = target;
        }
    }

    /* Question 2: dual question */
    // Size of Longest Increase Subsequence <=> Minimal Nums of Longest Non-Increase Subsequences to Cover the Whole Sequence
    dp_seq[cnt++] = height[0];
    for (int i = 1; i < n; ++i) {
        int target = height[i];
        if (target > dp_seq[cnt-1]) {
            dp_seq[cnt++] = target;
        } else { // target <= dp_seq[cnt-1]
            int lo = 0, hi = cnt - 2, mi;
            while (lo <= hi) {
                mi = (lo + hi) >> 1;
                if (target <= dp_seq[mi]) hi = mi - 1;
                else lo = mi + 1;
            }
            dp_seq[lo] = target;
        }
    }

    printf("%d\n%d\n", len, cnt);

    return 0;
}