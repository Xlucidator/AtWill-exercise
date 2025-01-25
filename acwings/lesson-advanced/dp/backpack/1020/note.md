## 1020. 潜水员

总结：3种状态定义

- 体积至多是j：初始化 `dp[i] = 0`，索引大于等于0
- 体积恰好是j：初始化 `dp[0] = 0, dp[i] = NUL`，索引大于等于0
- 体积至少是j：初始化 `dp[0] = 0, dp[i] = NUL`，索引可小于0

---



氧气量和氮气量是二维费用，要求满足氧气和氮气需求的最少重量，这与正常背包有区别（正常背包后能求最大汽缸重量）

和小精灵中第二问求最少消耗血量类似，都是要在满足某条件的情况下，最少的量

- 小精灵：`dp[血量][球数] = 最多球数`，然后再遍历求最多球数的情况下，最少的耗血量
- 潜水员

### 方案1

不如倒反天罡 `dp1[重量] = 最多氧气量, dp2[重量] = 最多氮气量`，求到达标后位置，遍历选出最小的重量

整合一下：`dp[重量] = 最多{氧气量, 氮气量}`

这样的话感觉不能说是二维费用，应该是二维结果；如此，1000个数据*最大800重，dp规模是800000 * 4B = 3.2MB 倒是可以
但每轮都要800000的规模怎么想都不值；

- 记录一下总重，从总重开始计算 -> 必须是完整的总重！

！错误的地方：

- 二维费用不可拆，如上的取max，会导致O和氮各取最大的分家了；而如果想不分家，也无法判断究竟选那边，所以完全不对
- 每轮不能仅更新至当下的 `max_weight`，这是我的思考错误

### 方案2

还是二维费用 `dp[氧气][氮气] = 重量`
就改用min，初始化为INF, 语义为未知方案；在计算时，若为INF，则视为。。

怎么想都不行，做不到 -> 就是上述，只不过状态语义变了

---

还是太死板啦，状态变更可以更灵活些；虽然如下的变更有些憋屈

`dp[j][k]`

- 状态表示：（从前i个物品中选）氧气量**恰好是j**，氮气量**恰好是k**的选法中，**最小**重量值
- 状态计算

最后还需**遍历满足条件的部分**，即从规定量向上，取min值；所以变化就是j和k不再从输入量开始向下循环，而是从理论最大可能量向下循环（即将整个dp都用满）

理论氧气最大就是 $\sum_{k} a_i \leq 1000 \cdot 21 = 21000$, 氮气最大是 $\sum_k b_i \leq 1000 \cdot 79 = 79000$ 这样显然过大不能做

---

状态调整为 **至少是**

### 样例

```
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

输出： 249

---
5 5
9
1 1 12
3 1 52
1 3 71
2 1 33
3 2 86
2 3 91
2 2 43
3 3 113
1 2 28

输出： 104

---
5 60
5
21 1 120
21 50 129
21 5 250
21 2 130
21 2 119

输出：全加起来的值

---
5 60
9
3 36 120
10 25 129
5 50 250
1 45 130
1 79 1
1 69 1
1 78 1
1 77 1
1 76 1

输出： 5
```

### 题目

潜水员为了潜水要使用特殊的装备。
他有一个带2种气体的气缸：一个为氧气，一个为氮气。
让潜水员下潜的深度需要各种数量的氧和氮。
潜水员有一定数量的气缸。
每个气缸都有重量和气体容量。
潜水员为了完成他的工作需要特定数量的氧和氮。
他完成工作所需气缸的总重的最低限度的是多少？

例如：潜水员有5个气缸。每行三个数字为：氧，氮的（升）量和气缸的重量：

```
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
```

如果潜水员需要5升的氧和60升的氮则总重最小为249（1，2或者4，5号气缸）。

你的任务就是计算潜水员为了完成他的工作需要的气缸的重量的最低值。

#### 输入格式

第一行有2个整数  m，n
 。它们表示氧，氮各自需要的量。

第二行为整数  k
  表示气缸的个数。

此后的  k
  行，每行包括 ai，bi，ci
 ，3个整数。这些各自是：第  i
  个气缸里的氧和氮的容量及气缸重量。

#### 输出格式

仅一行包含一个整数，为潜水员完成工作所需的气缸的重量总和的最低值。

数据范围

$$
1≤m≤21
 ,\\
1≤n≤79
 ,\\
1≤k≤1000
 ,\\
1≤a_i≤21
 ,\\
1≤b_i≤79
 ,\\
1≤c_i≤800
$$

#### 输入样例：

```
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
```

#### 输出样例：

```
249
```

### Record

方案一错误代码 record

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXO = 22, MAXN = 80, MAXK = 1002;
const int MAXW = 800 * 1000 + 2;

struct Gas {
    int O, N;
    Gas() {}
    Gas(int o, int n):O(o), N(n) {}
    Gas add(int o, int n) { 
        return Gas(O+o, N+n);
    }
    inline void max(const Gas& other) { 
        O = std::max(O, other.O);
        N = std::max(N, other.N); 
    } // wrong: for O & N would be update seperately
    inline bool pass(int o, int n) { return O >= o && N >= n; }
    void printGas() { printf("O = %d, N = %d ", O, N); }
};

Gas dp[MAXW];
int m/* Oxygen */, n/* Nitrogen */, k;
int max_weight;
int a[MAXK], b[MAXK], c[MAXK];

int main() {
    scanf("%d%d%d", &m, &n, &k);

    for (int i = 1; i <= k; ++i) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        max_weight += c[i];
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = max_weight/* must be final max_weight, higher dp need to update too */; j >= c[i]; --j) {
            dp[j].max(dp[j-c[i]].add(a[i], b[i]));
        }
    }

    int res = max_weight;
    while (dp[res-1].pass(m, n)) {
        res--;
    }

    // int res = 0;
    // while (dp[res].pass(m, n) == false) {
    //     printf("dp[%d]:", res); dp[res].printGas();
    //     printf("(%d >= %d : %d, %d >= %d : %d)\n", dp[res].O, m, dp[res].O >= m, dp[res].N, n, dp[res].N >= n);
    //     res++;
    // }

    printf("%d\n", res);

    return 0;
}
```

错误2:卡了好久啊

```
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXO = 21 + 21 + 2, MAXN = 79 + 79 + 2;
const int NUL = 0x3f3f3f3f;

int M/* Oxygen */, N/* Nitrogen */, K;
int dp[21000][MAXN];

void printDPLegal(int round) {
    printf("[Round %d]\n", round);
    for (int j = 0; j < MAXO; ++j) {
        for (int k = 0; k < MAXN; ++k) {
            if (dp[j][k] != NUL) printf("f[%d][%d]: %d\n", j, k, dp[j][k]);
        }
    }
    puts("");
}

int main() {
    scanf("%d%d%d", &M, &N, &K);

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    printDPLegal(0);

    int a, b, c;
    for (int i = 0; i < K; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        for (int j = MAXO - 1; j >= a; --j) {
            for (int k = MAXN - 1; k >= b; --k) {
                dp[j][k] = min(dp[j][k], dp[j-a][k-b] + c);
            }
        }
        printDPLegal(i+1);
    }

    int res = NUL;
    for (int j = M; j < MAXO; ++j) {
        for (int k = N; k < MAXN; ++k) {
            res = min(res, dp[j][k]);
        }
    }

    printf("%d\n", res);

    return 0;
}
```
