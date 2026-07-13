#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.c", "r", stdin);
    freopen("output.txt", "w", stdout);

    int space = 0, line = 0;
    bool div = false, mul = false;
    bool lnComment = false, multiComment = false;

    for (char c; cin.get(c);)
    {
        if (!lnComment && !multiComment)
        {
            if (div)
            {
                if (c == '/')
                {
                    lnComment = true;
                    div = false;
                    continue;
                }
                else if (c == '*')
                {
                    multiComment = true;
                    div = false;
                    continue;
                }
                else
                {
                    cout << '/';
                    div = false;
                }
            }

            if (c == ' ')
            {
                space++;
            }
            else if (c == '\n')
            {
                line++;
                space = 0;
            }
            else if (c == '/')
            {
                div = true;
            }
            else
            {
                space = 0;
                line = 0;
            }

            if (!div)
            {
                if (space < 2 && line < 2)
                {
                    if (c == '\n')
                    {
                        cout << ' ';
                        line++;
                    }
                    else
                        cout << c;
                }
            }
        }
        if (lnComment)
        {
            if (c == '\n')
            {
                lnComment = false;
                line++;
            }
        }
        if (multiComment)
        {
            if (mul)
            {
                if (c == '/')
                {
                    multiComment = false;
                    mul = false;
                    continue;
                }
                else
                {
                    mul = false;
                }
            }
            if (c == '*')
            {
                mul = true;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}