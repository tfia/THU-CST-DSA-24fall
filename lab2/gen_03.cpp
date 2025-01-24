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