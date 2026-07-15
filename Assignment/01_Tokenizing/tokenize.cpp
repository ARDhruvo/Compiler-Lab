#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

void printFile(string filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        cout << line << endl;
    }
    inputFile.close();
}

void tokenize()
{
    ifstream inFile("input.c");
    if (!inFile.is_open())
    {
        cout << "Error opening input file." << endl;
        return;
    }
    ofstream outFile("output.txt");
    if (!outFile.is_open())
    {
        cout << "Error opening output file." << endl;
        return;
    }

    int space = 0, newLine = 0;
    bool div = false, mul = false;
    bool lnComment = false, multiComment = false;

    for (char c; inFile.get(c);)
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
                    outFile << '/';
                    div = false;
                }
            }

            if (c == ' ')
            {
                space++;
            }
            else if (c == '\n')
            {
                newLine++;
                space = 0;
            }
            else if (c == '/')
            {
                div = true;
            }
            else
            {
                space = 0;
                newLine = 0;
            }

            if (!div)
            {
                if (space < 2 && newLine < 2)
                {
                    if (c == '\n')
                    {
                        outFile << ' ';
                        newLine++;
                    }
                    else
                        outFile << c;
                }
            }
        }
        if (lnComment)
        {
            if (c == '\n')
            {
                lnComment = false;
                newLine++;
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
    inFile.close();
    outFile.close();
}

int main()
{
    cout << "Sample Input: input.c" << endl;
    printFile("input.c");
    paragraph;

    tokenize();

    cout << "Sample Output: ";
    printFile("output.txt");
    return 0;
}