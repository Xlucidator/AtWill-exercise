### vector

两个vector之间已重载比较运算符（看作数就行了） `vector<int> a(4, 3), b(3, 4);` 则有 `a < b` 为真

### pair

构造 `make_pair(10, "xyz")`，或者  `{10, "xyz"}`

但是肯定比自己定义的struct慢

### tuple

多个组合数据又不想写struct的时候可以用用；但肯定比自己定义的struct慢

### string

length和size作用一样

```
s.substr(start, size)
```

### queue

没有 `clear`函数（queue, priority_queue, stack没有）

```
front() back() pop() push()
和栈差不多其实
```

### stack

### priority_queue

```cpp
push() top() pop()
默认大顶堆

小顶堆：
- 插入负数
- priority<int, vector<int>, greater<int>> heap; 多写后两个模板
```

### deque

### set & multiset

是否有重复元素

++, -- 返回前驱和后继，时间复杂度 O(logn)

```
insert() find()返回迭代器 count()
erase() 删除x or 删除迭代器  O(k + logn) k是x的个数

lower_bound(x) 返回大于等于x的最小数的迭代器
upper_bound(x) 返回大于x的最小数的迭代器
```

### map & multimap

```
insert()  插入的数是一个pair find()
erase()  输入的参数是pair或者迭代器

[]  注意multimap不支持此操作。 时间复杂度是 O(logn)
lower_bound()/upper_bound()
```

### unordered版

不支持 `lower_bound` 和 `upper_bound()` ，++/-- 这种基于排序的操作

### bitset

```
bool matrix[10000][10000] 要100MB  => bitset

bitset<10000> s; 看作一个整数
~ & | ^ << >> == !=
[]

count() 返回1的割术
any()  是否有1
none() 是否全0

set()      把所有位置成1
set(k, v)  将第k位变成v
reset() 清零
flip()  取反 ~  flip(k) 把第k位取反

```
