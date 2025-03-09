T3

可以这么记 lower_bound和upper_bound的了：其实就是用于求有序数组中值在 `[l, r]` 区间的个数(指针首尾)

```c++
auto it_l = lower_bound(a, a+n, l);  // 大于等于l的最小数
auto it_r = lower_bound(a, a+n, r);  // 大于r的最小数
int cnt = it_r - it_l;  // 都找不到也满足，都是end()
```



T2  先是不熟multiset迭代器的一些操作；然后脑残了去写一个通用的remove元素+维护中位数迭代器的函数，完全忘了需要的操作仅有删除中位数，很简单的一个操作写得据复杂（2x2的if讨论，因为已经混了），结果还忘考虑删完后

- bug1：6号delete操作，it = xxx.erase(it) 后，无需再++了；这导致了几个WA
- bug2：3号move操作，脑残写了个乱七八糟的remove中位数的非通用（但自以为通用）函数，没考虑删完的情况；总之就是多此一举+写错；这导致了超多的RE.
  - 发觉原因，被add的操作给带偏了
- bug3：5号merge操作，由于是后来才加的中位数迭代器数组，所以swap时忘记交换中位数迭代器了；这导致了Task1的几个RE，除了段错误，还有Signal 6的错误 `Aborted / IOT trap ，乐`

把multiset当作红黑树用；想了下2号操作统一add的懒操作还是需要的
