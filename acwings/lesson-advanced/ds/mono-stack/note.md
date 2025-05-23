## 栈&单调栈

一般的情况：找某个数某侧第一个比他大/小的数

### 830. 单调栈

找数左侧第一个比他小的数

从暴力做法中提取思路

- 暴力思路：因此在从左往右遍历选定 `a[i]` ；对于每个 `a[i]`，从其左侧开始向左遍历寻找首个**小于**它的值 => 这相当于，循遍历依次将 `a[0] ~ a[i-1]`的内容依次加入栈中，然后从栈顶向下遍历找首个小于 `a[i]`的值
- 记左侧为栈底，向右生长；可以发现如果有 `| .. , a[i], a[j], ..`且有 `a[i] >= a[j]`，则 `a[i]`必然不会被选中（因为它比它右侧的数**不大**，要么右侧数被选中，要么就都不被选中），因而此时 `a[i]`可以被剔除 => 即在这个栈中从左到右的**降序**(非升序)都不出现，即每次数据入栈时如果栈顶**大于等于**新数据则弹栈，即最终仅会生成从左向右升序的单调栈
  - 那每次 `a[i]`要入栈时，可能经过多次弹栈后 最终合格的栈顶就是 `a[i]` 要找的左侧第一个比它小的数

复杂度：所有元素都会进栈一次，有些元素可能还会出栈一次，所以最多2n，时间复杂度$O(n)$
