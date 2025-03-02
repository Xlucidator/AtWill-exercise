可以这么记 lower_bound和upper_bound的了：其实就是用于求有序数组中值在 `[l, r]` 区间的个数(指针首尾)

```c++
auto it_l = lower_bound(a, a+n, l);  // 大于等于l的最小数
auto it_r = lower_bound(a, a+n, r);  // 大于r的最小数
int cnt = it_r - it_l;  // 都找不到也满足，都是end()
```
