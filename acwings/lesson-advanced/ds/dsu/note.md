## 并查集

`p[x] = x`

- 判断x是否为树根：`p[x] == x`
- find 求x的集合编号：`while(p[x] != x) x = p[x];`
- union 合并集合

```cpp
int  find (int a) { /* ... */ }
void uunion(int a, int b) { p[find(a)] = find(b); }
```

#### 优化1：路径压缩

基本认为是$O(1)$；

但是其实是$O(log n)$，需要在加上按秩合并，才能真正算是$O(\alpha(n))$，无限近似于常系数数

```cpp
// recursive
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]); 
    return p[x];
}

// non-recursive
int find(int x) {
    // 836.cpp中的写法，似乎做不到路径上所有节点的压缩，并不对
    // 需要记录沿途的所有节点
    while (p[x] != x) stack.push(x), x = p[x];
    while (!stack.empty()) p[stack.pop()] = x;
}
```

#### 优化2：按秩压缩

很少写，优化不多


### 1250. 格子游戏

加入一条边后成环 $\iff$ 在加入边前，边的两个点已经在一个集合中

（其实也可用无向图的tarjan算法求全联通分量，不过小题大做
