#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 102;

int dp_left[MAXN], dp_right[MAXN];
int height[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &height[i]);
    
    for (int i = 0; i < N; ++i) {
        dp_left[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (height[i] > height[j]) {
                dp_left[i] = max(dp_left[i], dp_left[j] + 1);
            }
        }
    }
    for (int i = N-1; i >= 0; --i) {
        dp_right[i] = 1;
        for (int j = N-1; j > i; --j) {
            if (height[i] > height[j]) {
                dp_right[i] = max(dp_right[i], dp_right[j] + 1);
            }
        }
    }
    
    int max_student = 0;
    for (int i = 0; i < N; ++i) max_student = max(max_student, dp_left[i] + dp_right[i] - 1);
    printf("%d\n", N - max_student);
    
    return 0;
}