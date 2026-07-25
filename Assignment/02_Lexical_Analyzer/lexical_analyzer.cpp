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

    cout << "Main file:" << endl;
    printFile("output.txt");
    paragraph;

    ifstream inFile("output.txt");
    if (!inFile.is_open())
    {
        cout << "Error opening output file." << endl;
        exit(1);
    }

    ofstream outFile("step1.txt");

    bool space = false, sep = false, quote = false, brac = false;
    bool op = false, inc = false, dec = false, comp = false;
    bool notOp = false, andOp = false, orOp = false;

    for (char c; inFile.get(c);)
    {
        switch (c)
        {
        case '&':
            if (andOp)
            {
                outFile << c;
                andOp = false;
            }
            else
            {
                andOp = true;
                spaceChecker(c, outFile, space);
            }
            break;
        case '|':
            if (orOp)
            {
                outFile << c;
                orOp = false;
            }
            else
            {
                orOp = true;
                spaceChecker(c, outFile, space);
            }
            break;
        case '!':
            notOp = true;
            spaceChecker(c, outFile, space);
            break;
        case '<':
        case '>':
        case '=':
            if (op || notOp)
            {
                outFile << c;
                op = false;
                notOp = false;
                comp = true;
            }
            else
            {
                op = true;
                spaceChecker(c, outFile, space);
            }
            break;
        case '+':
            if (inc)
            {
                outFile << c;
                inc = false;
            }
            else
            {
                inc = true;
                spaceChecker(c, outFile, space);
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
                spaceChecker(c, outFile, space);
            }
            break;
        case '*':
        case '/':
        case '%':
            op = true;
            spaceChecker(c, outFile, space);
            break;
        case '(':
        case ')':
        case '{':
        case '}':
            brac = true;
            spaceChecker(c, outFile, space);
            break;
        case '\'':
        case '\"':
            quote = true;
            spaceChecker(c, outFile, space);
            break;

        case ';':
        case ',':
            sep = true;
            spaceChecker(c, outFile, space);
            break;
        case ' ':
            sep = false;
            quote = false;
            brac = false;
            op = false;
            comp = false;
            notOp = false;
            andOp = false;
            orOp = false;
            space = true;
            outFile << c;
            break;
        default:
            if (sep)
            {
                outFile << ' ';
                sep = false;
            }
            else if (quote)
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
            else if (inc)
            {
                outFile << ' ';
                inc = false;
            }
            else if (dec)
            {
                outFile << ' ';
                dec = false;
            }
            else if (comp)
            {
                outFile << ' ';
                dec = false;
            }
            else if (notOp)
            {
                outFile << ' ';
                notOp = false;
            }
            else if (andOp)
            {
                outFile << ' ';
                andOp = false;
            }
            else if (orOp)
            {
                outFile << ' ';
                orOp = false;
            }
            outFile << c;
            space = false;
            brac = false;
            inc = false;
            dec = false;
            comp = false;
            notOp = false;
            andOp = false;
            orOp = false;
            break;
        }
    }

    inFile.close();
    outFile.close();

    printFile("step1.txt");

    // Step 2: Tokenize and classify the identifiers and keywords into their respective categories

    return 0;
}