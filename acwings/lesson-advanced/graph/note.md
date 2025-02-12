## 遍历

### 846. 树的重心

- 树重心的定义：删除重心后，剩余各连通块节点数的最大值最小（即尽可能拆得均匀）
  - dfs遍历可以求每个子树的节点个数
  - dfs遍历：知左子树节点数，知右子树节点数，则也可知将自己这颗子树删去后剩余全树的节点数
- 所以可知，一次树的dfs遍历即可求出各节点删除后各连通块中点数最大的值

### 847.图中点的层次

有重边和自环的图，求从1号点走到n号点的最短距离：可以用bfs求

### 848. 拓扑序列

略了略了

不过回忆一下，有两种写法：

- 正向的bfs
- dfs后反向输出；反向dfs

## 最短路 SP

分类

- 单源最短路
  - 全部正权边
    - 朴素Dijkstra : O(n^2)
    - 堆优化Dijkstra : O(m log n)
  - 存在负权边
    - Bellman-Ford : O(nm)
    - SPFA : 优化Bellman-Ford 平均O(m)，最坏O(nm) 不一定都能做
- 多源汇最短路
  - Floyd算法

注意点

- 认为稀疏图是 m ~ n，是比较常见的理解
- 考察难点：如何建图，如何将问题抽象为最短路
- Dijstra基于贪心，Floyd基于dp，Bellman-Ford基于离散数学

### 849. Dijkstra求最短路I

- 邻接矩阵存图
- 处理重边和自环：重边取最小，自环无用

复杂度

- 不在set中的距离最近的点 O(n*n)
- 将选定的t加入set中 O(n*1)
- 用t更新其他点的距离(与t临界的) O(m)

### 850. Dijkstra求最短路II

稀疏图，堆优化方式

- 手写堆，能维持n个数（支持修改操作）
- STL优先队列，不支持更新指定元素，所以每次更新就插入新值，所以堆中元素个数可能到m个

复杂度

- 不在set中的距离最近的点 O(n*1)
- 将选定的t加入set中 O(n*1)
- 用t更新其他点的距离(与t临界的) O(m*logn)
  - 考虑到STL实现，堆中元素可能到m，则变为O(m*logm)；不过由于m<n^2所以有可以发现logm < 2logn = O(logn)，所以不管怎么样数量级不会变
  - 所以**一般就不用手写堆**了

语法

greater<>反而是小顶堆，稍微反语义直觉；默认less<>是大顶堆

```cpp
struct greater : public binary_function<_Tp, _Tp, bool>
    {
      _GLIBCXX14_CONSTEXPR
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };
// less 反一反
// 应该就是调用时，返回true就交换，所以greater时交换，就是小顶堆了
```

## 最小生成树 MST

Prim和Kruskal

## 二分图

- 染色法 O(n+m)
- 匈牙利法 O(mn)
