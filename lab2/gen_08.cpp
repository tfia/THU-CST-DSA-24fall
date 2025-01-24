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