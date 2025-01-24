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