## 不同 hash 策略的实现
### 坏 hash
设字符串为 $S$，长度为 $m$，哈希表大小为 $N$，则
$$
\text{hash}(S) = \left(\sum\limits_{i = 0}^{m - 1}(S_i \times (i + 1))\right) \bmod{N}
$$
这样会使得越靠后的位权重越大，导致哈希分布不均匀。

### 好 hash

设字符串为 $S$，长度为 $m$，哈希表大小为 $N$。记 $b = 233$（为质数），则
$$
\text{hash}(S) = \left(\sum\limits_{i = 0}^{m - 1}(S_i \times b^{m - i})\right) \bmod{N}
$$

### 双向平方试探

在 `quadratic_probe` 结构体中维护两个成员变量 `D` 和 `R`，分别表示当前探测的方向（0 向左，1 向右）和探测半径。

在 `init` 中，设置初始向右探测，半径为 0。

``` cpp
void quadratic_probe::init()
{
    D = 1; R = 0;
}
```

在 `operator()` 中，设当前探测半径为 $R$。若当前探测方向为向左，则不改变 $R$，从上一次探测位置向左跳 $R^2$；若当前探测方向为向右，则设置 $R \leftarrow R + 1$，再从上一次探测位置向右先跳 $(R - 1)^2$，再向右跳 $R^2$。每次探测都要反转探测方向。

``` cpp
int quadratic_probe::operator()(hash_entry* Table, int table_size, int last_choice)
{
    if(D == 0)
    {
        D ^= 1;
        return (last_choice - ((2LL * R * R) % table_size) + table_size) % table_size;
    }
    else
    {
        R++;
        D ^= 1;
        return (((last_choice + ((1LL * (R - 1) * (R - 1)) % table_size)) % table_size) + ((1LL * R * R) % table_size)) % table_size;
    }
}
```

### 公共溢出区

将 `hashtable.Table[]` 的一部分作为哈希表，一部分作为公共溢出区。公共溢出区内采用线性策略，当发生冲突时，将冲突的元素线性地插入公共溢出区中，添加在溢出区已有元素的末尾；在查找时，线性地在公共溢出区中进行查找。初始化时，将溢出区指针 `cur` 指向溢出区的开头。

``` cpp
void overflow_strategy::init()
{
    cur = real_size;
}

int overflow_strategy::operator()(hash_entry* Table, int table_size, int last_choice)
{
    return cur++;
}
```

在结构体 `overflow_strategy` 中，有静态成员变量 `real_size = 350771` 标记了哈希表的大小。这个数是质数且满足除 4 余 3。

## 我对实验框架改动的说明（此部分不在字数限制要求内）

在 `main.cpp` 开头，我添加了如下内容，用来根据命令行参数选择不同的哈希与冲突排解策略。

``` cpp
hashing_strategy* hs;
collision_strategy* cs;

if(atoi(argv[1]) == 1) hs = new bad_hashing();
else if(atoi(argv[1]) == 2) hs = new good_hashing();
else return -1;

if(atoi(argv[2]) == 1) cs = new linear_probe();
else if(atoi(argv[2]) == 2) cs = new quadratic_probe();
else if(atoi(argv[2]) == 3) cs = new overflow_strategy();
else return -1;

hashtable table(TABLE_SIZE,hs,cs);
```

向 `main` 传入的参数 1 代表哈希策略的编号，参数 2 代表冲突排解策略的编号。不同编号对应的策略见上述代码。若编号非法，则实验框架报错退出。

在 `hashtable.h` 中的 `hashtable::insert` 函数最前面，我增加了如下内容：

``` cpp
bool insert(hash_entry entry){ 
    if(dynamic_cast<overflow_strategy*>(my_collision))
        table_size = overflow_strategy::real_size;
	...
```

这里使用了 `dynamic_cast` 动态转换 `collision_strategy*` 类型到 `overflow_strategy*` 类型的方法，判断当前的冲突排解策略是否是公共溢出区策略。假如转换成功，则说明当前为公共溢出区策略，进入 if 分支设置新的 table size；假如转换失败，则说明当前策略非公共溢出区策略，不进入 if 分支。由于策略由用户实际输入决定，因此只能使用这种 RTTI 方法判断类型。

## 进行测试

三组数据都使用随机选取，只在规模上有区别。考虑到好坏哈希策略暗含了“哈希冲突概率”这一自变量，因此整个实验具有数据规模与哈希冲突概率两个自变量，能够有效起到对比不同冲突解决策略性能的作用。

`test1.in` 满足 $n = m = 2000$。生成命令 `./gen 2000 2000 1`。

`test2.in` 满足 $n = 90000, m = 50000$。生成命令 `./gen 90000 50000 2`。

`test3.in` 满足 $n = 90000, m = 80000$。生成命令 `./gen 90000 80000 3`。

构造方法均为 shuffle 所有数据，然后取前 $n$ 或 $m$ 个。generator 实现位于 `gen.cpp`。

采用自己编写的 checker 进行测试，并与 `std::map` 进行对拍来验证正确性。checker 实现位于 `checker.cpp`，使用了 STL 的实现位于 `std.cpp`。

checker 输出的原始测试结果位于 `results.txt`，调整了格式并添加了额外说明的测试结果位于 `results.md`。

## 分析测试结果

1. 数据较小时，好坏哈希区别不大。数据较大时，好哈希总优于坏哈希，因为前者冲突的概率更小，插入和查找中冲突排解次数少，效率高。

2. 使用好哈希时线性试探和双向平方差距并不明显，只在最大的 test3 上后者略快于前者。使用坏哈希时后者显著优于前者。原因是后者试探范围增长比前者要快，冲突多时能够避免聚集；而后者由于访存连续性更差，会损失一部分性能，冲突少时反而与前者总用时差不多。

3. 大多情况下封闭散列占优势。但由 test1，处理数据较小且冲突较多的实际数据时，因为公共溢出能避免过多试探，故效率较高，适合使用。在数据较大且冲突较多时，公共溢出也至少比线性探测快。

4. 可能造成使用这样的哈希函数时，实际的哈希分布并不均匀，哈希表性能降低。

5. 在负载因子到达某个阈值时，取出表中所有元素，然后重新插入一个更大/更小的哈希表（重构），以此实现动态扩容和缩容。