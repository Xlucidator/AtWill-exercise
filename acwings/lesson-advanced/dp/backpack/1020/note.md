## 1020. 潜水员

氧气量和氮气量是二维费用，要求满足氧气和氮气需求的最少重量，这与正常背包有区别（正常背包后能求最大汽缸重量）

和小精灵中第二问求最少消耗血量类似，都是要在满足某条件的情况下，最少的量
- 小精灵：`dp[血量][球数] = 最多球数`，然后再遍历求最多球数的情况下，最少的耗血量
- 潜水员

### 方案1
不如倒反天罡`dp1[重量] = 最多氧气量, dp2[重量] = 最多氮气量`，求到达标后位置，遍历选出最小的重量

整合一下：`dp[重量] = 最多{氧气量, 氮气量}`

这样的话感觉不能说是二维费用，应该是二维结果；如此，1000个数据*最大800重，dp规模是800000 * 4B = 3.2MB 倒是可以
但每轮都要800000的规模怎么想都不值；
- 记录一下总重，从总重开始计算 -> 必须是完整的总重！

！错误的地方：
- 二维费用不可拆，如上的取max，会导致O和氮各取最大的分家了；而如果想不分家，也无法判断究竟选那边，所以完全不对
- 每轮不能仅更新至当下的`max_weight`，这是我的思考错误



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
```



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