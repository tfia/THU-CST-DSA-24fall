## 01

### 代码在评测时会出现的最严重错误类型

Runtime Error

### 代码出现这个错误结果的原因

第 20 行，递归调用 `play` 函数时，没有对 `rank` 做检查，导致可能传负数值。在下一层递归中，第 10 行就会以负数 `rank` 访问 `a`，导致 RE。

### 测例构造思路

要想以负数参数递归调用 `play`，需要使得 `left` 在上一层为 0。使得最左侧元素可被消除即可。

我提交的测试用例是手造的。

## 02

### 代码在评测时会出现的最严重错误类型

Runtime Error

### 代码出现这个错误结果的原因

没有对字符串判空，当消除空了之后，仍然尝试以下标 0 去访问字符串中的元素。

### 测例构造思路

使得最后能被消成空串即可。

我提交的测试用例是手造的。

## 03

### 代码在评测时会出现的最严重错误类型

Time Limit Exceeded

### 代码出现这个错误结果的原因

由于需要移动后面所有的字符，在 `std::string` 的头部 `insert` 和 `erase` 的时间复杂度是 $O(n)$，因而，总时间复杂度为 $O(nm)$。对于大规模数据，无法通过。

### 测例构造思路

构造规模最大的测试用例，每次操作在字符串头部插入、头部消除。

我提交的测试用例是程序生成的。附我的 generator 代码如下：

``` cpp
// gen_03.cpp
#include <iostream>

using namespace std;

int main()
{
    freopen("03.in", "w", stdout);
    for(int i = 1; i <= 125000; i++) cout << "AABB";
    cout << endl << "500000" << endl;
    for(int i = 1; i <= 250000; i++)
    {
        cout << "0 A" << endl;
        cout << "0 B" << endl;
    }
}
```

## 04

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

第 12 行在找 `left` 时多减了 1，导致多移除了左侧的一个元素。

### 测例构造思路

构造在某位置消除后左侧仍有剩余的串即可。

我提交的测试用例是手造的。

## 05

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

27 行使用 `cin` 读入初始字符串，无法处理初始串为空的情形。

### 测例构造思路

构造任意初始串为空的合法输入即可。

我提交的测试用例是手造的。

## 06

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

完全没有判断 `plen_bound`，即没有考虑块的最大长度。若往一块持续插入而不发生消除，这一块的块长超过块的最大长度之后，调用 `p2a` 时会使用过长块的尾部覆盖后一块头部的内容。

### 测例构造思路

构造有 2 块及以上的初始串，然后持续向位置 0 插入大于块长个字符，使得第 1 块的大小大于最大块长，并不发生任何消除，这样第 2 块头部就会被第 1 块末尾覆盖。保证覆盖之后答案错误即可。

我提交的测试用例是程序生成的。附我的 generator 代码如下：

``` cpp
// gen_06.cpp
#include <iostream>

using namespace std;

int main()
{
    freopen("06.in", "w", stdout);
    for(int i = 1; i <= (1 << 11); i++)
    {
        cout << char((i % 26) - 1 + 'A');
    }
    for(int i = 1; i <= (1 << 11); i++)
    {
        cout << char((i % 26) - 1 + 'A');
    }
    cout << endl << (1 << 11) + 1 << endl;
    for(int i = 1; i <= (1 << 11) + 1; i++)
    {
        cout << "0 " << char((i % 26) + 'A') << endl;
    }
}
```

## 07

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

第 96 行，使用了 if 而不是 while 来统计需要消除的块，导致无法跳过空块，处理空块两侧的合并时会出错。

### 测例构造思路

构造被分为 3 块的初始输入，将第 2 块消除为空块，然后设法使 1，3 块的交界处发生消除，就会出错。

我提交的测试用例是程序生成的。附我的 generator 代码如下：

``` cpp
// gen_07.cpp
#include <iostream>
#include <stack>

using namespace std;

const int plen_target = 1 << 11;
const int plen_bound = 1 << 12;

stack<char> st;

int main()
{
    freopen("07.in", "w", stdout);
    for(int i = 1; i <= (1 << 11) - 2; i++)
    {
        cout << char((i - 1) % 26 + 'A');
    }
    cout << "XA";
    // cout << endl;
    for(int i = 1; i <= 682; i++)
    {
        cout << char(i % 26 + 'A');
        st.push(char(i % 26 + 'A'));
        // BCDDCCBB
    }
    cout << "XX";
    while(!st.empty())
    {
        char c = st.top();
        cout << c << c;
        st.pop();
    }
    // cout << endl;
    for(int i = 1; i <= (1 << 11); i++)
    {
        cout << char((i - 1) % 26 + 'A');
    }
    cout << endl << "2" << endl;
    cout << (1 << 11) + 682 << " X" << endl;
    cout << (1 << 11) << " A" << endl;
}
```

## 08

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

没有考虑块间连消。

### 测例构造思路

构造被分为 3 块的初始输入，使得消除第 2 块之后，立刻引发1，3块的边界处发生连消即可。

我提交的测试用例是程序生成的。附我的 generator 代码如下：

``` cpp
// gen_08.cpp
#include <iostream>
#include <stack>

using namespace std;

const int plen_target = 1 << 11;
const int plen_bound = 1 << 12;

stack<char> st;

int main()
{
    freopen("08.in", "w", stdout);
    for(int i = 1; i <= (1 << 11) - 2; i++)
    {
        cout << char((i - 1) % 26 + 'A');
    }
    cout << "AA";
    // cout << endl;
    for(int i = 1; i <= 682; i++)
    {
        cout << char(i % 26 + 'A');
        st.push(char(i % 26 + 'A'));
        // BCDDCCBB
    }
    cout << "XX";
    while(!st.empty())
    {
        char c = st.top();
        cout << c << c;
        st.pop();
    }
    // cout << endl;
    for(int i = 1; i <= (1 << 11); i++)
    {
        cout << char((i - 1) % 26 + 'A');
    }
    cout << endl << "1" << endl;
    cout << (1 << 11) + 682 << " X" << endl;
}
```

## 09

### 代码在评测时会出现的最严重错误类型

Runtime Error

### 代码出现这个错误结果的原因

“执行消除”部分，没有考虑 `l.first` 与 `r.first` 相等的情况，即发生块内（不含块边界）的消除时，“执行消除”部分，

``` cpp
if (l.first >= 0) {
    plen[l.first] = l.second + 1;
}
if (r.first < pn) {
    int len = plen[r.first] - r.second;
    if (len > 0) {
        memmove(&p[r.first][0], &p[r.first][r.second], len);
    }
    plen[r.first] = len;
}
```

计算出来的 `len` 是负数，且被保存到了 `plen` 中。接着，在计算完毕，将块组装回序列时，

``` cpp
// p to a：将 p “组装”回 a
void p2a() {
    int copied = 0;
    for (int i = 0; i < pn; i++) {
        memcpy(&a[copied], p[i], plen[i]);
        copied += plen[i];
    }
}
```

导致以负数调用 `memcpy`，发生 RE。

### 测例构造思路

默认块长很长，任意构造不在块边缘处消除的数据即可。

我提交的测试用例是手造的。

## 10

### 代码在评测时会出现的最严重错误类型

Wrong Answer

### 代码出现这个错误结果的原因

“执行消除”部分，有

``` cpp
for (int i = l.first; i < r.first; i++)
	plen[i] = 0;
```

导致如果发生跨块消除，消除边界的左侧整块都会被消除掉。

### 测例构造思路

利用与上文卡掉 08 的完全相同的 hack 数据即可卡掉 10。

我提交的测试用例是程序生成的，使用了与 08 相同的 generator。