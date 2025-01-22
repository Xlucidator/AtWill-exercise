## 多重背包问题 III (压成1维dp数组)

虽说视频里时y佬说压滚动数组也得存上一轮状态，但其实j从V开始逆序计算的话，还是可以
压成1维dp数组的。不过这样实现中似乎又会多些细节处理，总体上还是会更容易写错一些

### 思路区别

#### 正向优势
正向计算`dp[][j]`的优点在于，一开始单调队列未满(s+1)窗口数时，也天然符合`dp[][j]`的计算条件
```
dp[i][r   ] = max( dp[i-1][r] )
dp[i][r+ v] = max( dp[i-1][r]+w, dp[i-1][r+v] )
dp[i][r+2v] = max( dp[i-1][r]+2w, dp[i-1][r+v]+w, dp[i-1][r+2v] )
...
```
而逆向计算的话情况就相对复杂：在dp计算链数量足够时需要满足读入`s+1`窗口数后才能计算初始的`dp[][j]`；而计算链数量不足时则要全部读入后才能开始计算初始的`dp[][j]`
```
dp[i][j]   = max( dp[i-1][j], dp[i-1][j-v]+w, .. , dp[i-1][j-sv]+sw ) # window size = s+1
                                                 | 可能因为计算链数量不足被截断
dp[i][j-v] = max( dp[i-1][j-v], dp[i-1][j-2v]+w, .., dp[j-1][j-(s+1)v]+sw )
```
因而我在实现时直接分为2步：【预取阶段】先尝试向单调队列中装入 `s+1` 个数, `k`也跟着变化
记录实际装入的dp数组索引位置；【计算阶段】随后每一步都可计算一个`dp[][j-v]`直至0；

**注意**：若在预取阶段计算链就已不够`s+1`，则需手动将`k`调整为装满窗口的情况，即
`k -= (s + 1 - cnt) * v;`（这句写漏了调了一会儿才发现）
> 这就是不优雅的地方，正向能顺其自然解决的计算链不满窗口的问题，逆向就需要刻意调整才能解决

#### 逆向优势

1. 逆序计算不会提前覆盖要用的上一个状态，所以可以压成1维dp数组，从而可能快一些些，空间也少一些些(少20000 * 4B = 80KB)
2. 逆向与我们原始dp分析时的顺序一致，于是 向单调队列中加数时的偏移计算 和 取数后使用的偏移计算可以更好的合并，我将其定义为`offset_value(idx, base)`，更方便书写与思考
```cpp
#define offset_value(idx, base) (dp[idx] + ((base)-idx)/v * w)
```

### 实现

#### 逆向`dp[MAXV]`

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002;
const int MAXV = 20002, MAXS = 20002;

int q[MAXV]; // mono queue : decrease
int N, V;
int dp[MAXV];

#define offset_value(idx, base) (dp[idx] + ((base)-idx)/v * w)

int main() {
    scanf("%d%d", &N, &V);
    int v, w, s;

    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &v, &w, &s);
        for (int j = V; j > V-v; --j) {
            int head = 0, tail = -1;

            // Preload
            int k, cnt;
            for (k = j, cnt = 0; k >= 0 && cnt <= s; k -= v, cnt++) {
                while (head <= tail && offset_value(q[tail], j) <= offset_value(k, j)) tail--;
                q[++tail] = k;
            }
            k -= (s + 1 - cnt) * v; // IMPORTANT, to pretend the windows is full
            
            // Begin to Calculate dp[j], dp[j-v], ..., dp[j%v]
            for (int tar = j; tar > 0/* no need to update dp[0] */; tar -= v, k -= v) {
                dp[tar] = max(dp[tar], offset_value(q[head], tar));

                if (head <= tail && q[head] > k + s*v) head++;
                if (k >= 0) {
                    while (head <= tail && offset_value(q[tail], j) <= offset_value(k, j)) tail--;
                    q[++tail] = k;
                }
            }
        }
    }

    printf("%d\n", dp[V]);

    return 0;
}
```


#### 正向`dp[2][MAXV]`

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1002;
const int MAXV = 20002, MAXS = 20002;

int q[MAXV]; // mono queue : decrease
int N, V;
int dp[2][MAXV];

int main() {
    scanf("%d%d", &N, &V);
    int v, w, s;

    bool cur = 0, pre = 1;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &v, &w, &s);
        cur = !cur; pre = !cur; // switch state: may faster than memory copy
        for (int j = 0; j < v; ++j) {
            int head = 0, tail = -1;
            for (int k = j; k <= V; k += v) {
                if (head <= tail && q[head] < k - s*v) head++;
                while (head <= tail && 
                    dp[pre][q[tail]] - (q[tail]-j)/v * w
                    <= 
                    dp[pre][k]       - (k-j)/v * w
                ) tail--;
                q[++tail] = k;

                dp[cur][k] = max(dp[cur][k], dp[pre][q[head]] + (k - q[head])/v * w);
            }
        }
    }

    printf("%d\n", dp[cur][V]);

    return 0;
}

```

