#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.c", "r", stdin);
    freopen("output.txt", "w", stdout);

    int space = 0;
    char divide;
    bool lnComment = false, multiComment = false;

    for (char c; cin.get(c);)
    {
        if (c == ' ')
        {
            space++;
        }
        else
        {
            space = 0;
        }

        if (space < 2)
        {
            cout << c;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}