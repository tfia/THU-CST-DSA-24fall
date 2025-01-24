## 2A

输入规模为 $n$ 时，总执行时间为 $10n^2 \times 10^{-8}=10^{-7}n^2$ 秒。

时限为 $2$ 倍，因此需要满足 $2 \times 10^{-7}n^2 \leq 1$。

解得 $n \leq \sqrt{5 \times 10^6} \approx 2236$。$n$ 最大为 $2236$。

## 2B

总执行时间为 $20n\log_2n \times 10^{-8}$ 秒。

$2 \times 20n\log_2n \times 10^{-8} \leq 1$。

解得 $n\log_2n \leq 2.5 \times 10^6$。$n$ 最大为 $145746$。

## 3A

`solution_1.cpp`: 

- 数组开到 2e3，但是从下标 1 开始用，在最大规模数据下会发生数组越界
- 每次询问后 sum 变量未清零
- 使用 `int` 存储每次查询的答案，根据数据范围，答案最大可能为 $2000 \times 2000 \times 10^5 = 4 \times 10^{11}$，超出了 `int` 的表示范围

`solution_2.cpp`: 

- 同样存在数组越界、多测不清空、爆 `int` 的问题
- 查询前缀和时下标有误，应该改为 `sum += rowsum[x + j][y + b - 1] - rowsum[x + j][y - 1];`

查错方式：静态检查 + 输出调试。

GPT-4o-Mini 能够找到数组越界和多测不清空的 bug，经提示之后能找到爆 `int` 的 bug，但无法找到查询前缀和错误的 bug。

## 3B

使用 `-g` 选项编译。

`gdb ./a.out` 启动对 `a.out` 的调试。在 `gdb` 中，`run` 执行程序，`next` 一行行执行，遇到函数时跳过不进入内部，`step` 一行行执行，可进入函数内部。

## 3C

将当前时间作为随机数种子，使得每次调用数据生成器时生成的测试数据不一样。

## 3D

以`g++` 开头的 4 行命令使用 `g++` 编译两份待测代码、随机数据 generator 和输入数据 checker。

`./rand_input > rand.in` 等 4 行类似的命令分别重定向它们的输入输出。

判断 `system("./check_input < rand.in")!=0` 通过判断 checker 的返回值，判断输入是否合法。

`diff 1.out 2.out` 调用 `diff` 工具比较 `1.out` 和 `2.out`，即比较两份待测代码在同样输入下的输出是否相同。

## 3E

我的代码：

``` cpp
void g() {g();}

int main()
{
    g();
    return 0;
}
```

会观察到程序异常退出。

```
Program received signal SIGSEGV, Segmentation fault.
g () at rec.cpp:1
1       void g() {g();}
```

这表明程序由于无限递归造成了栈溢出，访问了非法内存，于是内核向其发送 `SIGSEGV` 将其 abort。造成这一现象的代码位于第 1 行。

## 4A

预处理二维前缀和即可。即，设输入矩阵为 $a$，计算矩阵 $s$，满足 $s_{x, y} = \sum_{i=1}^x\sum_{j=1}^x a_{i, j}$。这样每次查询可以在常数时间内给出答案。

## 4B

造了 20 个数据点。考虑到程序的复杂度只与 $n, m$ 有关，所以固定了 $q$ 的值。第 $i$ 个数据点满足 $n = m = 100i, q = 5 \times 10^4$。

使用自己编写的评测系统对三个程序分别进行测试，均开启了 O2 优化，每个测试点的时限设为 2 秒，超时会自动杀死进程。以下测试结果中第一列为测试点编号，第二列为评测状态，最后一列为用时，单位为微秒（$10^{-6}$s）。

**solution_3:**

1	Accepted	20846
2	Accepted	27411
3	Accepted	28510
4	Accepted	46561
5	Accepted	49933
6	Accepted	48155
7	Accepted	54825
8	Accepted	79563
9	Accepted	78909
10	Accepted	90556
11	Accepted	123159
12	Accepted	110556
13	Accepted	124752
14	Accepted	135406
15	Accepted	160241
16	Accepted	164873
17	Accepted	199827
18	Accepted	218341
19	Accepted	257673
20	Accepted	330586

**solution_2:**

1	Accepted	28734
2	Accepted	29062
3	Accepted	34362
4	Accepted	59563
5	Accepted	55366
6	Accepted	72914
7	Accepted	92997
8	Accepted	139114
9	Accepted	212302
10	Accepted	218315
11	Accepted	281658
12	Accepted	269939
13	Accepted	317650
14	Accepted	354347
15	Accepted	418953
16	Accepted	499607
17	Accepted	491731
18	Accepted	519379
19	Accepted	681232
20	Accepted	701612

**solution_1:**

1	Accepted	38892
2	Accepted	166060
3	Accepted	211800
4	Accepted	314766
5	Accepted	497028
6	Accepted	808134
7	Accepted	1157985
8	Accepted	1292343
9	Accepted	1703220
10	Time Limit Exceeded	2201671
11	Time Limit Exceeded	2201660
12	Time Limit Exceeded	2200871
13	Time Limit Exceeded	2201765
14	Time Limit Exceeded	2201657
15	Time Limit Exceeded	2201670
16	Time Limit Exceeded	2201675
17	Time Limit Exceeded	2201670
18	Time Limit Exceeded	2201607
19	Time Limit Exceeded	2201708
20	Time Limit Exceeded	2201617

## 4C

固定 $q = 5 \times 10^4$ 的情况下：

在 $n, m \leq 100$ 时，三个程序用时基本相同，solution_3 没有明显优势。

在 $100 \lt n, m \leq 700$ 时，solution_2 和 solution_3 用时基本相同，solution_3 没有明显优势。但此时 solution_1 展现出明显劣势。

在 $700 \lt n, m \leq 2000$ 时，solution_3 相较 solution_1 有明显优势，相较 solution_2 有优势但并不大（运行时间没有数量级上的区别）。在 $n, m \gt 1000$ 时，solution_1 已经无法在 2 秒内得出结果。

随着 $q$ 的变动，以上具体规律可能会发生变化，但总体规律为，矩阵规模较小时，三份程序没有明显差异，随着矩阵规模的增大，solution_1 先展现劣势，solution_2 其次，但总相较 solution_1 有优势；solution_3 在此过程中总有优势。