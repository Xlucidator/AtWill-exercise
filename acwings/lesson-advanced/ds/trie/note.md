## Trie树

用于快速存储/查找字符串集合

- 字符串统计


从根节点出发，一个节点一个字符，到单词的词尾时打一个标记表示到此处有单词存在

- 所以字符集有$|\Sigma|$个字符，就最多为$|\Sigma|$叉树


### 143. 最大异或对

n个数，求两两异或所得值最大的那个

暴力算法：对于每个a[i]，枚举a[j]

改进算法：对于每个a[i]，找最大的a[j]

- 从a[i]的最高位向下依次贪心的选择；这个过程暗合trie树
- 所以所有数均可事先构建为trie树

trie树存本身还是挺明显，但后续具体怎么操作就一时没想通；还是从暴力算法中优化出的

复杂度：空间上最多$10^5$个数，每个数最多31位，所以总共最多（必然好多重复）$31 \cdot 10^5$ 个trie节点，其实每个节点可以用bool，就算1B，最多 $3\cdot 10^6$B = 3MB，完全够；时间上，外循环遍历每个数$10^5$次，内循环贪心的找最大最多31次，总共$31\cdot 10^5$次，也完全够
