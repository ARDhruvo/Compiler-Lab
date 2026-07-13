#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.c", "r", stdin);
    freopen("output.txt", "w", stdout);

    int space = 0, line = 0;
    char divide;
    bool lnComment = false, multiComment = false;

    for (char c; cin.get(c);)
    {
        if (c == ' ')
        {
            space++;
            line = 0;
        }
        else
        {
            space = 0;
            line = 0;
        }

        if (space < 2)
        {
            if (c == '\n' && line < 2)
            {
                cout << ' ';
                line++;
            }
            else
                cout << c;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}