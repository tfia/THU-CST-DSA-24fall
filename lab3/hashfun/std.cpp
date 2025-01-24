#include <iostream>
#include <map>

using namespace std;

map<string, int> mp;
int op, k;
string s;

int main()
{
    while (1)
    {
        cin >> op;
        if (op == 0)
        {
            cin >> s >> k;
            mp.insert(make_pair(s, k));
        }
        else if (op == 1)
        {
            cin >> s;
            if (mp.find(s) != mp.end())
                cout << mp[s] << endl;
            else
                cout << -1 << endl;
        }
        else
            break;
    }
    return 0;
}