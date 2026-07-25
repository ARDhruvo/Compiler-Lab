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

void tokenizer()
{
    cout << "Sample Input: input.c" << endl;
    printFile("input.c");
    paragraph;

    tokenize();

    cout << "Sample Output: ";
    printFile("output.txt");
}

void spaceChecker(char c, ofstream &outFile, bool &space)
{
    if (space)
    {
        outFile << c;
        space = false;
    }
    else
    {
        outFile << ' ' << c;
    }
}

int main()
{
    tokenize();

    // Step 1: Separate the identifiers and keywords from the output.txt file

    ifstream inFile("output.txt");
    if (!inFile.is_open())
    {
        cout << "Error opening output file." << endl;
        exit(1);
    }

    ofstream outFile("step1.txt");

    bool space = false, sep = false, quote = false, brac = false;
    bool op = false, inc = false, dec = false;
    for (char c; inFile.get(c);)
    {
        switch (c)
        {
        case '+':
            if (inc)
            {
                outFile << c;
                inc = false;
            }
            else
            {
                inc = true;
                if (space)
                {
                    outFile << c;
                    space = false;
                }
                else
                {
                    outFile << ' ' << c;
                }
            }
            break;
        case '-':
            if (dec)
            {
                outFile << c;
                dec = false;
            }
            else
            {
                dec = true;
                if (space)
                {
                    outFile << c;
                    space = false;
                }
                else
                {
                    outFile << ' ' << c;
                }
            }
            break;
        case '*':
        case '/':
            op = true;
            if (space)
            {
                outFile << c;
                space = false;
            }
            else
            {
                outFile << ' ' << c;
            }
            break;
        case '(':
        case ')':
        case '{':
        case '}':
            brac = true;
            if (space)
            {
                outFile << c;
                space = false;
            }
            else
            {
                outFile << ' ' << c;
            }
            break;
        case '\'':
        case '\"':
            quote = true;
            spaceChecker(c, outFile, space);
            break;

        case ';':
            sep = true;
            if (space)
            {
                outFile << c;
                space = false;
            }
            else
            {
                outFile << ' ' << c;
            }
            break;
        case ' ':
            if (sep)
            {
                sep = false;
            }
            if (quote)
            {
                quote = false;
            }
            if (brac)
            {
                brac = false;
            }
            if (op)
            {
                op = false;
            }
            space = true;
            outFile << c;
            break;
        default:
            if (sep)
            {
                outFile << ' ';
                sep = false;
            }
            if (quote)
            {
                outFile << ' ';
                quote = false;
            }
            else if (brac)
            {
                outFile << ' ';
                brac = false;
            }
            else if (op)
            {
                outFile << ' ';
                op = false;
            }
            outFile << c;
            space = false;
            brac = false;
            inc = false;
            dec = false;
            break;
        }
    }

    inFile.close();
    outFile.close();

    printFile("step1.txt");

    // Step 2: Tokenize and classify the identifiers and keywords into their respective categories

    return 0;
}