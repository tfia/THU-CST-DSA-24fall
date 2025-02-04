## 算法思路和实现要点

子树的规模很好维护。在每个节点内维护一个以其为根的子树的 size，通过 dfs 初始化，时间复杂度 $O(n)$。每次删除或插入时，更新子树根部父节点的 size，然后通过一级一级向上跳父亲的方式，更新所有可能受影响的节点的 size。每次更新操作的时间复杂度为 $O(h)$，其中 $h$ 为树高。

容易发现，一个节点的高度总是小于或等于按照“通路表示法”访问其的“成本”。由于题目保证所有操作的“成本”之和小于 $10^6$，因此这么做的复杂度满足题目要求。

对于子树的高度，可以将一个节点的所有子节点视作一个序列，维护其后缀最大子树高度。这样，查询以一个节点为根的子树的高度，等同于查询其第一个子节点的后缀最大高度。每次插入或删除之后，只需更新变动的节点之前的所有子节点的后缀高度，然后向上跳到父亲节点重复更新操作。

容易发现，这样一次更新遍历的子节点数即是题目中描述的“成本”。由于题目保证所有操作的“成本”之和小于 $10^6$，因此这么做的复杂度满足题目要求。

## 渐进时间复杂度的分析

建树、初始化子树规模和后缀最大高度的时间复杂度为 $O(n)$。每次操作，时间复杂度为 $O(w)$，其中 $w$ 为这次操作的“成本”。总时间复杂度为 $O(n + \sum w)$。

## 渐进空间复杂度的分析

使用数组模拟链表存储树。对每个节点，保存其前后兄弟、父节点、第一个子节点、和最后一个子节点所在的下标。总空间复杂度为 $O(n)$。