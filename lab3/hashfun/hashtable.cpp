#include "hashtable.h"

int overflow_strategy::real_size = 350771;

int naive_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    else
        return (str[0] + N) % N;
}

int bad_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    int res = 0;
    for (int i = 0; str[i]; i++)
        res = (res + str[i] * (i + 1)) % N;
    return res;
}

int good_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    int b = 233;
    int res = 0;
    for (int i = 0; str[i]; i++)
        res = ((long long)res * b + str[i]) % N;
    return res;
}

int linear_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    return (last_choice + 1) % table_size;
}
void linear_probe::init()
{
    return; // do nothing
}

void quadratic_probe::init()
{
    D = 1;
    R = 0;
}

int quadratic_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    if (D == 0)
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

void overflow_strategy::init()
{
    cur = real_size;
}

int overflow_strategy::operator()(hash_entry *Table, int table_size, int last_choice)
{
    return cur++;
}