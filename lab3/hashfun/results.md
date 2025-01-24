测试环境：

CPU: 8-core Intel(R) Core(TM) i7-10510U CPU @ 1.80GHz

RAM: 16.0 GB @ 2667 MHz

OS: Windows 10

---

Case 1 (test1.in, $n = m = 2000$)

|              | linear_probe | quadratic_probe | overflow_strategy |
| ------------ | ------------ | --------------- | ----------------- |
| bad_hashing  | 0.082s       | 0.087s          | 0.081s            |
| good_hashing | 0.089s       | 0.093s          | 0.08s             |

Case 2 (test2.in, $n = 90000, m = 50000$)

|              | linear_probe | quadratic_probe | overflow_strategy |
| ------------ | ------------ | --------------- | ----------------- |
| bad_hashing  | 68.957s      | 1.872s          | 36.487s           |
| good_hashing | 0.31s        | 0.314s          | 1.372s            |

Case 3 (test3.in, $n = 90000, m = 80000$)

|              | linear_probe | quadratic_probe | overflow_strategy |
| ------------ | ------------ | --------------- | ----------------- |
| bad_hashing  | 94.274s      | 2.442s          | 52.199s           |
| good_hashing | 0.387s       | 0.339s          | 1.884s            |

