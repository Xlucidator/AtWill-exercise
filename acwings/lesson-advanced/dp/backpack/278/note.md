## 278. 数字组合

求和为M的组合方案数

`dp[i][j]`：前i个数，加到j的方案数  `dp[i][j] = dp[i-1][j] + dp[i-1][j-a]` 

- 即 用第i个数 + 不用第i个数

01背包求方案（给定具体方案的情况下），并非完整的求方案
