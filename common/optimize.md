```cpp
# cin / cout concerned
ios::sync_with_stdio(false);  // 快不了多少，单调栈那道快了个200ms的样子
cin.tie(0);  // 再加上这个，单调栈那道快了1000ms，和只用scanf/printf差不多了(小慢10ms)
// 更好的写法：C++17以上才是安全的
cin.tie(nullptr)->sync_with_stdio(false);

```
