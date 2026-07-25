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

void lexemeSeparator()
{
    // Step 1: Separate the identifiers and keywords from the output.txt file

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
}

bool isKeyword(string lex)
{
    set<string> keywords = {
        "int", "char", "float", "double", "void", "long", "short",
        "signed", "unsigned", "if", "else", "for", "while", "do",
        "switch", "case", "default", "break", "continue", "return",
        "struct", "union", "typedef", "enum", "const", "static",
        "extern", "register", "volatile", "sizeof", "goto"};
    if (keywords.find(lex) != keywords.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isOperator(string lex)
{
    set<string> ops = {
        "=", "+", "-", "*", "/", "%",
        "==", "!=", "<=", ">=", "<", ">",
        "&&", "||", "!", "&", "|", "++", "--"};
    if (ops.find(lex) != ops.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int id_rec(string lex)
{
    int state = 0;
    if (isalpha(lex[0]) || lex[0] == '_')
        state = 1;
    else
        return 0;

    for (size_t i = 1; i < lex.size(); i++)
    {
        if (isalnum(lex[i]) || lex[i] == '_')
            state = 1;
        else
        {
            state = 0;
            break;
        }
    }
    return state;
}

int num_rec(string lex)
{
    int i = 0, len = lex.size(), state;

    if (isdigit(lex[i]))
    {
        state = 1;
        i++;
    }
    else if (lex[i] == '.')
    {
        state = 2;
        i++;
    }
    else
        state = 0;

    if (state == 1)
        for (; i < len; i++)
        {
            if (isdigit(lex[i]))
                state = 1;
            else if (lex[i] == '.')
            {
                state = 2;
                i++;
                break;
            }
            else
            {
                state = 0;
                break;
            }
        }

    if (state == 2)
    {
        if (i < len && isdigit(lex[i]))
        {
            state = 3;
            i++;
        }
        else
            state = 0;
    }

    if (state == 3)
        for (; i < len; i++)
        {
            if (isdigit(lex[i]))
                state = 3;
            else
            {
                state = 0;
                break;
            }
        }

    if (state == 3)
        state = 1;
    return state;
}

bool isSeparator(string lex)
{
    return lex == ";" || lex == "," || lex == "'" || lex == "\"";
}

bool isParen(string lex)
{
    return lex == "(" || lex == ")";
}

bool isBrace(string lex)
{
    return lex == "{" || lex == "}" || lex == "[" || lex == "]";
}

string tagger(string lex)
{
    if (isKeyword(lex))
        return "kw";
    if (id_rec(lex))
        return "id";
    if (num_rec(lex))
        return "num";
    if (isOperator(lex))
        return "op";
    if (isSeparator(lex))
        return "sep";
    if (isParen(lex))
        return "par";
    if (isBrace(lex))
        return "brac";
    return "unkn";
}

void identifier()
{
    // Step 2: Tokenize and classify the identifiers and keywords into their respective categories
    ifstream inFile("step1.txt");
    if (!inFile.is_open())
    {
        cout << "Error opening step1.txt." << endl;
        exit(1);
    }
    ofstream outFile("step2.txt");

    string lex;
    while (inFile >> lex)
    {
        string tag = tagger(lex);
        outFile << "[" << tag << " " << lex << "] ";
    }

    inFile.close();
    outFile.close();
}

int main()
{
    cout << "Original File:" << endl;
    printFile("input.c");
    paragraph;

    tokenize();
    cout << "Tokenized and without space:" << endl;
    printFile("output.txt");
    paragraph;

    lexemeSeparator();
    cout << "Separated Lexemes:" << endl;
    printFile("step1.txt");
    paragraph;

    identifier();
    cout << "Tagged Lexemes:" << endl;
    printFile("step2.txt");

    return 0;
}