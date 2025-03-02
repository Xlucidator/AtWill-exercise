### 795. 前缀和

### 797. 差分

原数组区间加$\iff$差分数组两端做加减；原数组某点值$\iff$ 差分数组求前缀和


### 双指针算法

1. 两个序列两个指针：如归并排序
2. 一个序列两个指针：如快排，指向区间


### 位运算


### 离散化

整数保序离散化

值域很大(如$0\~10^9$)，个数较少(如$0\~10^5$)。所以将**大值域映射到小值域中**，方便hash

问题：
- 原数组a[]中可能有重复元素
- 如何快速映射: 快速算出 a[i] 离散化为何值

模板
```cpp
vector<int> alls; // 存储所有待离散化的值
sort(alls.begin(), alls.end());
alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 去掉重复元素
// unique会将区间内重复元素移至末尾，然后返回去重后有效区间的end()；因此之后的erase掉就可以了

// 二分求出x对应的离散化的值
int find(int x) // 找到第一个大于等于x的位置
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}
```

802. 区间和 - 离散化