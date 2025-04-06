#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <stack>
#include <set>
#include <sstream>
#include <iomanip>
#include <Windows.h>
using namespace std;
// Lexical analysis
const int MAXSIZE = 1000;
char token[MAXSIZE];
char Test[1000][1000];
char ch;
FILE *f;
int flag = 0;
int row = 1;
int token_num = 0;
int state = 0;
// const char Keyword[33][10] = { "auto","double","int","struct","break","else","long","switch",
// "case","enum","register","typedef","char","extern","return","union","const","float","short",
// "unsigned","for","signed","void","default","goto","sizeof","volatile","do","if","continue",
// "static","while","main" }; // keywords
const char Keyword[5][10] = {"int", "float", "double", "void", "char"};
const char Headfile[4][10] = {"iostream", "string", "algorithm", "iomanip"};
queue<string> tape; // Record the results of the lexical analyzer and transmit them to the syntax analyzer
bool judge = true;
void ReadTest() // read-in
{
    int i = 1, j = 0;
    ch = getc(f);
    while (ch != EOF)
    {
        if (ch != '\n')
        {
            Test[i][j++] = ch;
        }
        if (ch == '\n')
        {
            i++;
            j = 0;
        }
        ch = getc(f);
    }
    rewind(f);
}
void Reset() // reset
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        token[i] = NULL;
        token_num = 0;
    }
}
int GetToken() // Initiate lexical analysis
{
    Reset(); // Reset token character array
    if (flag == 0)
    {
        ch = getc(f);
    }
    flag = 1;                                     // First analysis mark
    state = 0;                                    // State variable initialization
    while (ch == ' ' || ch == '\t' || ch == '\n') // Filter whitespace, tab, and line breaks
    {
        if (ch == '\n')
        {
            row++;                                    // Add 1 to the number of rows
            cout << row << ": " << Test[row] << endl; // Output the line to be analyzed
        }
        ch = getc(f);
    }
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')) // keywords and identifiers
    {
        while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
        {
            token[token_num++] = ch;
            ch = getc(f);
        }
        for (int i = 0; i < 5; i++)
        {
            if (strcmp(token, Keyword[i]) == 0)
            {
                return i + 1;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (strcmp(token, Headfile[i]) == 0)
            {
                return i + 6;
            }
        }
        if (strcmp(token, "main") == 0)
        {
            return 10;
        }
        else if (strcmp(token, "include") == 0)
        {
            return 11;
        }
        else if (strcmp(token, "return") == 0)
        {
            return 12;
        }
        else if (strcmp(token, "using") == 0)
        {
            return 13;
        }
        else if (strcmp(token, "namespace") == 0)
        {
            return 14;
        }
        else if (strcmp(token, "std") == 0)
        {
            return 15;
        }
        else if (strcmp(token, "while") == 0)
        {
            return 16;
        }
        else if (strcmp(token, "if") == 0)
        {
            return 17;
        }
        else if (strcmp(token, "else") == 0)
        {
            return 18;
        }
        else if (strcmp(token, "break") == 0)
        {
            return 19;
        }
        else
        {
            return 67;
        }
    }
    else if (ch >= '0' && ch <= '9') // Unsigned integer or floating-point number
    {
        while (1) // DFA for unsigned numbers
        {
            switch (state)
            {
            case 0:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 1;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                }
                break;
            case 1:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 1;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                case '.':
                    state = 2;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                case 'E':
                    state = 4;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return 68;
                }
                break;
            case 2:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 3;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return -2;
                }
                break;
            case 3:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 3;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                case 'E':
                    state = 4;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return 69;
                }
                break;
            case 4:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 6;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                case '+':
                case '-':
                    state = 5;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return -2;
                }
                break;
            case 5:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 6;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return -2;
                }
                break;
            case 6:
                switch (ch)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = 6;
                    token[token_num++] = ch;
                    ch = getc(f);
                    break;
                default:
                    return 69;
                }
                break;
            }
        }
    }
    else // symbol
    {
        token[token_num++] = ch;
        switch (ch)
        {
        case ',':
            ch = getc(f);
            return 34;
        case '%':
            ch = getc(f);
            return 35;
        case '{':
            ch = getc(f);
            return 36;
        case '_':
            ch = getc(f);
            return 37;
        case '}':
            ch = getc(f);
            return 38;
        case '(':
            ch = getc(f);
            return 39;
        case ')':
            ch = getc(f);
            return 40;
        case '+':
            ch = getc(f);
            if (ch == '+')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 52;
            }
            else
            {
                return 41;
            }
        case '-':
            ch = getc(f);
            if (ch == '-')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 53;
            }
            else
            {
                return 42;
            }
        case '*':
            ch = getc(f);
            if (ch == '/')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return -4;
            }
            else
            {
                return 43;
            }
        case '/':
            while (1)
            {
                switch (state)
                {
                case 0:
                    switch (ch)
                    {
                    case '/':
                        state = 1;
                        ch = getc(f);
                        break;
                    }
                    break;
                case 1:
                    switch (ch)
                    {
                    case '*':
                        state = 2;
                        token[token_num++] = ch;
                        ch = getc(f);
                        break;
                    default:
                        return 44;
                    }
                    break;
                case 2:
                    switch (ch)
                    {
                    case '*':
                        state = 3;
                        token[token_num++] = ch;
                        ch = getc(f);
                        break;
                    case EOF:
                        return -4;
                    default:
                        state = 2;
                        token[token_num++] = ch;
                        ch = getc(f);
                        if (ch == '\n')
                        {
                            row++;
                            cout << row << ": " << Test[row] << endl;
                        }
                        break;
                    }
                    break;
                case 3:
                    switch (ch)
                    {
                    case '/':
                        token[token_num++] = ch;
                        ch = getc(f);
                        return 70;
                    default:
                        return -4;
                    }
                    break;
                }
            }
        case '=':
            ch = getc(f);
            if (ch == '=')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 60;
            }
            else
            {
                return 45;
            }
        case '>':
            ch = getc(f);
            if (ch == '=')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 47;
            }
            else
            {
                return 46;
            }
        case '<':
            ch = getc(f);
            if (ch == '=')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 49;
            }
            else
            {
                return 48;
            }
        case '\"':
            ch = getc(f);
            return 50;
        case ';':
            ch = getc(f);
            return 51;
        case '!':
            ch = getc(f);
            if (ch == '=')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 57;
            }
            else
            {
                return 56;
            }
        case '\'':
            ch = getc(f);
            return 58;
        case '#':
            ch = getc(f);
            return 59;
        case '&':
            ch = getc(f);
            if (ch == '&')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 62;
            }
            else
            {
                return 61;
            }
        case '|':
            ch = getc(f);
            if (ch == '|')
            {
                token[token_num++] = ch;
                ch = getc(f);
                return 64;
            }
            else
            {
                return 63;
            }
        case '[':
            ch = getc(f);
            return 65;
        case ']':
            ch = getc(f);
            return 66;
        case EOF:
            return 0; // End of analysis
        default:
            ch = getc(f);
            return -3;
        }
    }
}
void Scanner() // Start the lexical analyzer, output the recognized lexical units based on the return value of the function Get Token, and pass them to the syntax analyzer
{
    cout << row << ": " << Test[row] << endl; // Output the line being recognized
    int temp;
    while (1)
    {
        temp = GetToken();
        if (temp >= 1 && temp <= 5) // keyword
        {
            cout << "    " << "Keyword: " << token << endl;
            tape.push("k");
        }
        else if (temp >= 6 && temp <= 9) // Header file name
        {
            cout << "    " << "Headfile: " << token << endl;
            tape.push("h");
        }
        else if (temp == 10) // main
        {
            cout << "    " << "MAIN: " << token << endl;
            tape.push("m");
        }
        else if (temp == 11) // include
        {
            cout << "    " << "INCLUDE: " << token << endl;
            tape.push("n");
        }
        else if (temp == 12) // return
        {
            cout << "    " << "RETURN: " << token << endl;
            tape.push("r");
        }
        else if (temp == 13) // using
        {
            cout << "    " << "USING: " << token << endl;
            tape.push("u");
        }
        else if (temp == 14) // namespace
        {
            cout << "    " << "NAMESPACE: " << token << endl;
            tape.push("p");
        }
        else if (temp == 15) // std
        {
            cout << "    " << "STD: " << token << endl;
            tape.push("t");
        }
        else if (temp == 16) // while
        {
            cout << "    " << "WHILE: " << token << endl;
            tape.push("w");
        }
        else if (temp == 17) // if
        {
            cout << "    " << "IF: " << token << endl;
            tape.push("f");
        }
        else if (temp == 18) // else
        {
            cout << "    " << "ELSE: " << token << endl;
            tape.push("e");
        }
        else if (temp == 19) // break
        {
            cout << "    " << "BREAK: " << token << endl;
            tape.push("g");
        }
        else if (temp >= 34 && temp <= 66) // symbol
        {
            if (temp == 47)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push(">");
                tape.push("=");
            }
            else if (temp == 49)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push("<");
                tape.push("=");
            }
            else if (temp == 57)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push("!");
                tape.push("=");
            }
            else if (temp == 60)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push("=");
                tape.push("=");
            }
            else if (temp == 62)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push("&");
                tape.push("&");
            }
            else if (temp == 64)
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push("|");
                tape.push("|");
            }
            else
            {
                cout << "    " << "Symbol: " << token << endl;
                tape.push(token);
            }
        }
        else if (temp == 67) // identifier
        {
            cout << "    " << "ID" << ", name = " << token << endl;
            tape.push("b");
        }
        else if (temp == 68) // integer
        {
            cout << "    " << "NUM-I" << ", value = " << token << endl;
            tape.push("s");
        }
        else if (temp == 69) // floating point number
        {
            cout << "    " << "NUM-F" << ", value = " << token << endl;
            tape.push("s");
        }
        else if (temp == 70) // explanatory note
        {
            cout << "    " << "Note" << ", content = ";
            for (int i = 2; i < token_num - 2; i++)
            {
                if (token[i] == '\n')
                {
                    cout << " ";
                }
                else
                {
                    cout << token[i];
                }
            }
            cout << endl;
        }
        else if (temp == -1) // Incorrect identifier
        {
            cout << "    " << "ERROR: " << "incorrect identifier." << endl;
            judge = false;
        }
        else if (temp == -2) // Numeric error
        {
            cout << "    " << "ERROR: " << "incorrect number." << endl;
            judge = false;
        }
        else if (temp == -3) // Unrecognized errors
        {
            cout << "    " << "ERROR: " << "unrecognized character." << endl;
            judge = false;
        }
        else if (temp == -4) // Annotation error
        {
            cout << "    " << "ERROR: " << "note not closed." << endl;
            judge = false;
        }
        else
        {
            break;
        }
    }
}
// LR(0) Syntax analysis
int numvt = 0, numvn = 0; // The number of terminal and non-terminal symbols
const int MAXNUM = 100;
string Finalchar[MAXNUM];             // Terminal Symbol
string NotFinalchar[MAXNUM];          // Non-terminal Symbols
map<char, int> Getnum;                // Terminator->Number
map<int, char> Getchar;               // Number->Terminator
string FIRST[MAXNUM];                 // FIRST Set
string FOLLOW[MAXNUM];                // FOLLOW Set
map<int, map<string, string>> ACTION; // ACTION Table
map<int, map<string, int>> GOTO;      // GOTO Table
stack<string> Symbol;                 // Symbol Stack
stack<int> Status;                    // State Stack
struct production                     // Production
{
    string Leftpart;  // Left Part
    string Rightpart; // Right Part
};
vector<production *> Productions; // Production Set
struct DFA                        // Automaton State
{
    int num;
    vector<string> Left;  // Production Left Part
    vector<string> Right; // Production Right Part
    map<char, int> Next;  // Transfer direction and transfer conditions
};
vector<DFA *> StatusSet;        // State Set
bool FLAG[MAXNUM] = {true};     // Flag Array
int Getdotpos(const string str) // Obtain '.' where
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            return i;
        }
    }
    return -1;
}
bool Candotmove(const string str) // Determine whether the '.' can be moved.
{
    if (str[str.length() - 1] == '.')
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Movedot(string &str) // Move the position of the '.'
{
    int pos = Getdotpos(str);
    if (pos == str.length() - 1)
    {
        return;
    }
    else
    {
        string tmp = "";
        for (int i = 0; i < pos; i++)
        {
            tmp += str[i];
        }
        tmp += str[pos + 1];
        tmp += '.';
        for (int i = pos + 2; i < str.length(); i++)
        {
            tmp += str[i];
        }
        str = tmp;
    }
}
string Leftadddot(string str) // Add a dot ('.') to the beginning of the right-hand side of the grammar production.
{
    str = '.' + str;
    return str;
}
production *Rightadddot(production *str) // Get a reduce item
{
    production *p = new production();
    p->Leftpart = str->Leftpart;
    p->Rightpart = str->Rightpart + '.';
    return p;
}
void ReadGrammar() // Read in information
{
    ifstream is1("E:/Code Repository/C++/Code/Group/Simple Compiler/data/Finalchar.txt", ios::in);
    if (!is1.is_open())
    {
        cout << "Error: Could not open the Finalchar.txt!" << endl;
    }
    string t;
    char r;
    int num = 0;
    while (!is1.eof())
    {
        is1 >> t;
        r = t[0];
        Getchar[num] = r; // Get the character-to-number mapping
        Getnum[r] = num;
        num++;
        Finalchar[numvt++] = t;
    }
    is1.close();
    cout << "Terminal Symbol: " << endl;
    for (int i = 0; i < numvt; i++)
    {
        cout << Finalchar[i] << " ";
    }
    cout << endl
         << endl;
    ifstream is2("E:/Code Repository/C++/Code/Group/Simple Compiler/data/NotFinalchar.txt", ios::in);
    if (!is2.is_open())
    {
        cout << "Error: Could not open the NotFinalchar.txt!" << endl;
    }
    while (!is2.eof())
    {
        is2 >> t;
        r = t[0];
        Getchar[num] = r; // Get the character-to-number mapping
        Getnum[r] = num;
        num++;
        NotFinalchar[numvn++] = t;
    }
    Getchar[num] = '@';
    Getnum['@'] = num;
    cout << "Non-terminal Symbol: " << endl;
    for (int i = 0; i < numvn; i++)
    {
        cout << NotFinalchar[i] << " ";
    }
    cout << endl
         << endl;
    is2.close();
    ifstream is3("E:/Code Repository/C++/Code/Group/Simple Compiler/data/Grammar.txt", ios::in);
    if (!is3.is_open())
    {
        cout << "Error: Could not open the Grammar.txt!" << endl;
    }
    while (!is3.eof())
    {
        production *tmp = new production();
        string s1, s2, s3;
        is3 >> s1 >> s2 >> s3;
        tmp->Leftpart = s1;
        tmp->Rightpart = s3;
        Productions.push_back(tmp);
    }
    is3.close();
    cout << "Production Rule:" << endl;
    for (int i = 0; i < Productions.size(); i++)
    {
        cout << Productions[i]->Leftpart << "->" << Productions[i]->Rightpart << endl;
    }
    cout << endl;
}
bool Emptystring(char x) // Determine whether the FIRST set of symbol x contains the empty string.
{
    int t = Getnum[x];
    string r = FIRST[t];
    for (int i = 0; i < r.size(); i++)
    {
        if (r[i] == '@')
        {
            return true;
        }
    }
    return false;
}
void AddFIRST(string &x, string y) // Merge two FIRST sets
{
    set<char> tmp;
    for (int i = 0; i < x.size(); i++)
    {
        tmp.insert(x[i]);
    }
    for (int i = 0; i < y.size(); i++)
    {
        tmp.insert(y[i]);
    }
    x.clear();
    set<char>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); it++)
    {
        x += *it;
    }
}
void GetFIRST(char x, bool flag[], int p) // Recursively compute the FIRST set of symbol x, where flag[] is the flag array and p is the index corresponding to x
{
    for (int i = 1; i < Productions.size(); i++)
    {
        if (Productions[i]->Leftpart[0] == x)
        {
            char tmp = Productions[i]->Rightpart[0];
            if (tmp == x) // If the first character of the right-hand side is equal to the left-hand side (i.e., left recursion), skip it
            {
                continue;
            }
            else
            {
                int t = Getnum[tmp];
                if (flag[t]) // Determine if the FIRST set for t has already exists
                {
                    AddFIRST(FIRST[p], FIRST[t]);
                }
                else
                {
                    GetFIRST(tmp, flag, t);
                    AddFIRST(FIRST[p], FIRST[t]);
                }
            }
        }
        for (int j = 1; j < Productions[i]->Rightpart.size() - 1; j++) // If there is a production for the empty string
        {
            if (Emptystring(Productions[i]->Rightpart[j]))
            {
                int t = Getnum[Productions[i]->Rightpart[j + 1]];
                if (flag[t])
                {
                    AddFIRST(FIRST[p], FIRST[t]);
                }
                else
                {
                    GetFIRST(Productions[i]->Rightpart[j + 1], flag, t);
                    AddFIRST(FIRST[p], FIRST[t]);
                }
            }
            else
            {
                break;
            }
        }
    }
    flag[p] = true; // The FIRST set of x is computed, and the flag is updated
}
void GetFIRSTSet() // Calculate the FIRST set
{
    bool flag[MAXSIZE] = {false};
    for (int i = 0; i < numvt; i++)
    {
        string r = Finalchar[i];
        FIRST[Getnum[r[0]]] += r[0];
    }
    FIRST[Getnum['@']] = '@'; // Add the empty string
    for (int i = 0; i < numvn; i++)
    {
        string x = NotFinalchar[i];
        int p = Getnum[x[0]];
        if (flag[p])
        {
            continue;
        }
        else
        {
            GetFIRST(x[0], flag, p);
        }
    }
}
void PrintFIRSTSet() // Output the FIRST set
{
    cout << "FIRST Set:" << endl;
    for (int i = 0; i < numvt + numvn; i++)
    {
        char x = Getchar[i];
        cout << "FIRST" << "[" << x << "]" << ": ";
        cout << FIRST[i] << endl;
    }
    cout << endl;
}
void AddFOLLOW(string &x, string y) // Merge two FOLLOW sets, or merge a FOLLOW set and a FIRST set, excluding the empty string
{
    set<char> tmp;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == '@') // Remove the empty string
        {
            continue;
        }
        tmp.insert(x[i]);
    }
    for (int i = 0; i < y.size(); i++)
    {
        if (y[i] == '@')
        {
            continue;
        }
        tmp.insert(y[i]);
    }
    x.clear();
    set<char>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); it++)
    {
        x += *it;
    }
}
void GetFOLLOW(char x, bool flag[], int p) // Compute the FOLLOW set of symbol x, where flag[] is the flag array and p is the index of symbol x
{
    for (int i = 1; i < Productions.size(); i++) // Scan each production rule
    {
        for (int j = 0; j < Productions[i]->Rightpart.size(); j++) // Scan if x appears in the right-hand side of this production
        {
            if (Productions[i]->Rightpart[j] == x) // x appears in the right-hand side
            {
                if (j == Productions[i]->Rightpart.size() - 1) // The position of x is at the end
                {
                    int t = Getnum[Productions[i]->Leftpart[0]];
                    if (Productions[i]->Leftpart[0] == x) // If x is at the end of the right-hand side and the left-hand side is also x, then skip this production
                    {
                        continue;
                    }
                    if (flag[t]) // Determine if the FOLLOW set for the left-hand side of this production exists
                    {
                        AddFOLLOW(FOLLOW[p], FOLLOW[t]);
                    }
                    else
                    {
                        GetFOLLOW(Productions[i]->Leftpart[0], flag, t); // Calculate the FOLLOW set for the left-hand side of this production rule
                        AddFOLLOW(FOLLOW[p], FOLLOW[t]);
                    }
                }
                else // x is not at the end
                {
                    int t = Getnum[Productions[i]->Rightpart[j + 1]];
                    AddFOLLOW(FOLLOW[p], FIRST[t]);                    // Add the FIRST set of the next symbol to the FOLLOW set of x
                    if (Emptystring(Productions[i]->Rightpart[j + 1])) // Determine if the FIRST set of x's next symbol includes the empty string
                    {
                        if (flag[t]) // If the empty string is in the FIRST set and the FOLLOW set of the next symbol exists
                        {
                            AddFOLLOW(FOLLOW[p], FOLLOW[t]);
                        }
                        else
                        {
                            GetFOLLOW(Productions[i]->Rightpart[j + 1], flag, t);
                            AddFOLLOW(FOLLOW[p], FOLLOW[t]);
                        }
                    }
                }
            }
        }
    }
    flag[p] = true; // Calculate the FOLLOW set for symbol x
}
void GetFOLLOWSet() // Calculate the FOLLOW set for the non-terminal
{
    bool flag[MAXSIZE] = {false};
    char tmp = Productions[1]->Leftpart[0];
    FOLLOW[Getnum[tmp]] += '$'; // Add '$' to the FOLLOW set of the start symbol E
    for (int i = 1; i < Productions.size(); i++)
    {
        int t = Productions[i]->Rightpart.size();
        if (t != 1)
        {
            if (Productions[i]->Rightpart[t - 1] < 'A' || Productions[i]->Rightpart[t - 1] > 'Z')
            {
                int p = Getnum[Productions[i]->Leftpart[0]];
                FOLLOW[p] += Productions[i]->Rightpart[t - 1];
            }
        }
    }
    for (int i = 0; i < numvn; i++)
    {
        string x = NotFinalchar[i];
        int p = Getnum[x[0]];
        if (flag[p])
        {
            continue;
        }
        else
        {
            GetFOLLOW(x[0], flag, p);
        }
    }
}
void PrintFOLLOWSet() // Output the FOLLOW set
{
    cout << "FOLLOW Set:" << endl;
    for (int i = 0; i < numvn; i++)
    {
        string x = NotFinalchar[i];
        int t = Getnum[x[0]];
        cout << "FOLLOW" << "[" << x << "]" << ": ";
        cout << FOLLOW[t] << endl;
    }
    cout << endl;
}
void GetClosure(vector<string> &Left, vector<string> &Right, string x) // Calculate the closure of the item set
{
    for (int i = 0; i < Productions.size(); i++)
    {
        if (x == Productions[i]->Leftpart)
        {
            if (Productions[i]->Rightpart == "@") // There is a production rule for the empty string
            {
                Left.push_back(x);
                Right.push_back(".");
            }
            else
            {
                Left.push_back(x);
                Right.push_back(Leftadddot(Productions[i]->Rightpart));
                if (Productions[i]->Rightpart[0] >= 'A' && Productions[i]->Rightpart[0] <= 'Z')
                {
                    if (Productions[i]->Leftpart[0] == Productions[i]->Rightpart[0])
                    {
                        continue;
                    }
                    else
                    {
                        string newx = "";
                        newx += Productions[i]->Rightpart[0];
                        GetClosure(Left, Right, newx);
                    }
                }
            }
        }
    }
}
void GetStatus(DFA *&x) // Obtain a state of the DFA
{
    string tmp = x->Right[0];
    int length = tmp.length();
    int pos = Getdotpos(tmp);
    if (pos < length - 1 && (x->Right[0][pos + 1] >= 'A' && x->Right[0][pos + 1] <= 'Z'))
    {
        vector<string> tmpLeft;
        vector<string> tmpRight;
        string t = "";
        t += tmp[pos + 1];
        GetClosure(tmpLeft, tmpRight, t);
        for (int i = 0; i < tmpLeft.size(); i++)
        {
            x->Left.push_back(tmpLeft[i]);
            x->Right.push_back(tmpRight[i]);
        }
    }
}
int DeletedupStatus() // Check if there are duplicate states
{
    int n = StatusSet.size();
    for (int i = 0; i < n - 1; i++)
    {
        if (StatusSet[i]->Left[0] == StatusSet[n - 1]->Left[0] && StatusSet[i]->Right[0] == StatusSet[n - 1]->Right[0])
        {
            StatusSet.pop_back();
            return i;
        }
    }
    return -1;
}
void CreateStatus(vector<string> Left, vector<string> Right) // Construct a DFA state
{
    DFA *tmp = new DFA();
    tmp->num = StatusSet.size();
    for (int i = 0; i < Left.size(); i++)
    {
        tmp->Left.push_back(Left[i]);
        Movedot(Right[i]);
        tmp->Right.push_back(Right[i]);
    }
    StatusSet.push_back(tmp);
}
void InitFLAG() // Initialize the flag array
{
    for (int i = 0; i < MAXNUM; i++)
    {
        FLAG[i] = true;
    }
}
void GetStatusSet() // Obtain the LR(0) canonical collection of items
{
    DFA *tmp = new DFA();
    tmp->num = 0;
    tmp->Left.push_back(Productions[0]->Leftpart);
    tmp->Right.push_back(Leftadddot(Productions[0]->Rightpart));
    GetStatus(tmp);
    StatusSet.push_back(tmp);
    for (int i = 0; i < StatusSet.size(); i++)
    {
        InitFLAG();
        for (int j = 0; j < StatusSet[i]->Left.size(); j++)
        {
            if (FLAG[j])
            {
                string t = StatusSet[i]->Right[j];
                if (!Candotmove(t))
                {
                    continue;
                }
                int p = Getdotpos(t);
                vector<string> Left, Right;
                Left.push_back(StatusSet[i]->Left[j]);
                Right.push_back(StatusSet[i]->Right[j]);
                FLAG[j] = false;
                for (int k = j + 1; k < StatusSet[i]->Left.size(); k++)
                {
                    string z = StatusSet[i]->Right[k];
                    if (!Candotmove(z))
                    {
                        continue;
                    }
                    int v = Getdotpos(z);
                    if (t[p + 1] == z[v + 1])
                    {
                        Left.push_back(StatusSet[i]->Left[k]);
                        Right.push_back(StatusSet[i]->Right[k]);
                        FLAG[k] = false;
                    }
                }
                CreateStatus(Left, Right);
                ;
                int w = DeletedupStatus();
                if (w == -1)
                {
                    GetStatus(StatusSet[StatusSet.size() - 1]);
                    int pos = Getdotpos(t);
                    StatusSet[i]->Next[t[pos + 1]] = StatusSet.size() - 1;
                    // cout << "I" << i << "input" << t[pos + 1] << "transfer to" << StatusSet.size() - 1 << endl;
                }
                else
                {
                    int pos = Getdotpos(t);
                    StatusSet[i]->Next[t[pos + 1]] = w;
                    // cout << "I" << i << "input" << t[pos + 1] << "transfer to" << k << endl;
                }
            }
        }
    }
}
void PrintStatusSet() // Output the LR(0) canonical collection of items
{
    for (int i = 0; i < StatusSet.size(); i++)
    {
        map<char, int>::iterator it;
        for (it = StatusSet[i]->Next.begin(); it != StatusSet[i]->Next.end(); it++)
        {
            cout << "I " << i << " input " << it->first << " transfer to " << it->second << endl;
        }
    }
    for (int i = 0; i < StatusSet.size(); i++)
    {
        cout << "I" << i << ":" << endl;
        for (int j = 0; j < StatusSet[i]->Left.size(); j++)
        {
            cout << StatusSet[i]->Left[j] << "->" << StatusSet[i]->Right[j] << endl;
        }
    }
}
bool FindProduction(production *p, DFA *x) // Check if there is a reduction item in state x
{
    production *tmp = Rightadddot(p);
    for (int i = 0; i < x->Left.size(); i++)
    {
        if (x->Left[i] == tmp->Leftpart && x->Right[i] == tmp->Rightpart)
        {
            return true;
        }
    }
    return false;
}
void GetR0Table() // Construct the LR(0) parsing table
{
    for (int i = 0; i < StatusSet.size(); i++)
    {
        for (int j = 0; j < numvt; j++)
        {
            ACTION[i][Finalchar[j]] = "error";
        }
    }
    for (int i = 0; i < StatusSet.size(); i++)
    {
        for (int j = 0; j < numvn; j++)
        {
            GOTO[i][NotFinalchar[j]] = -1;
        }
    }
    // Fill the GOTO table
    for (int i = 0; i < StatusSet.size(); i++)
    {
        map<char, int>::iterator it;
        for (it = StatusSet[i]->Next.begin(); it != StatusSet[i]->Next.end(); it++)
        {
            if (it->first >= 'A' && it->first <= 'Z')
            {
                string tmp = "";
                tmp += it->first;
                GOTO[i][tmp] = it->second;
            }
        }
    }
    // Fill the ACTION table
    // Fill the accept rule in the ACTION table
    string tmp1 = Productions[0]->Leftpart;
    string tmp2 = Productions[0]->Rightpart + ".";
    for (int i = 0; i < StatusSet.size(); i++)
    {
        if (StatusSet[i]->Left[0] == tmp1 && StatusSet[i]->Right[0] == tmp2)
        {
            ACTION[i]["$"] = "acc";
        }
    }
    // Fill the shift rule in the ACTION table
    for (int i = 0; i < StatusSet.size(); i++)
    {
        map<char, int>::iterator it;
        for (it = StatusSet[i]->Next.begin(); it != StatusSet[i]->Next.end(); it++)
        {
            if (it->first < 'A' || it->first > 'Z')
            {
                string tmp = "";
                tmp += it->first;
                ACTION[StatusSet[i]->num][tmp] = "s" + to_string(it->second);
            }
        }
    }
    // Fill the reduction rules in the ACTION table
    for (int i = 1; i < Productions.size(); i++)
    {
        for (int j = 0; j < StatusSet.size(); j++)
        {
            if (FindProduction(Productions[i], StatusSet[j]))
            {
                char tmp = Productions[i]->Leftpart[0];
                int t = Getnum[tmp];
                string r = FOLLOW[t];
                for (int k = 0; k < r.size(); k++)
                {
                    string tmp = "";
                    tmp += r[k];
                    ACTION[j][tmp] = "r" + to_string(i);
                }
            }
        }
    }
}
void PrintLR0Table()
{
    cout << "Parse Table: " << endl;
    // cout << "State" << setw(30) << "ACTIONS" << setw(32) << "GOTO" << endl;
    cout << "    ";
    for (int i = 0; i < numvt; i++)
    {
        cout << setw(10) << setiosflags(ios::left) << Finalchar[i];
    }
    for (int i = 0; i < numvn; i++)
    {
        cout << setw(10) << setiosflags(ios::left) << NotFinalchar[i];
    }
    cout << endl;
    for (int i = 0; i < StatusSet.size(); i++)
    {
        cout << setw(4) << setiosflags(ios::left) << i;
        for (int j = 0; j < numvt; j++)
        {
            cout << setw(10) << setiosflags(ios::left) << ACTION[i][Finalchar[j]];
        }
        for (int j = 0; j < numvn; j++)
        {
            cout << setw(10) << setiosflags(ios::left) << GOTO[i][NotFinalchar[j]];
        }
        cout << endl;
    }
    cout << endl;
}
void GetAnalysis(int x, int y, int z) // Real-time output of the parsing process
{
    cout << setw(4) << setiosflags(ios::left) << x;
    string S1, S2, S3, S4;
    stack<int> s1, s2;
    s2 = Status;
    while (!s2.empty())
    {
        s1.push(s2.top());
        s2.pop();
    }
    while (!s1.empty())
    {
        S1 += to_string(s1.top());
        s1.pop();
    }
    cout << setw(60) << S1;
    stack<string> s3, s4;
    s4 = Symbol;
    while (!s4.empty())
    {
        s3.push(s4.top());
        s4.pop();
    }
    while (!s3.empty())
    {
        S2 += s3.top();
        s3.pop();
    }
    cout << setw(40) << S2;
    queue<string> q = tape;
    while (!q.empty())
    {
        S3 += q.front();
        q.pop();
    }
    cout << setw(70) << S3;
    if (y == -1)
    {
        S4 = "wrong";
        cout << setw(40) << S4;
        cout << endl
             << endl;
        cout << "Syntax analysis result: " << endl;
        cout << "Cannot be generated by the grammar of the source language!" << endl;
    }
    else if (y == 0)
    {
        S4 = "Move In";
        cout << setw(40) << S4;
    }
    else if (y == 1)
    {
        S4 = "According to " + Productions[z]->Leftpart + "->" + Productions[z]->Rightpart + " Reduction";
        cout << setw(40) << S4;
    }
    else
    {
        S4 = "Accept";
        cout << setw(40) << S4;
        cout << endl
             << endl;
        cout << "The grammar of the source language can generate!" << endl;
    }
    cout << endl;
}
int Changenum(string str) // Convert a string variable to an integer variable
{
    int tmp = 0;
    for (int i = 1; i < str.size(); i++)
    {
        tmp *= 10;
        tmp += (str[i] - '0');
    }
    return tmp;
}
void Analysis() // Initialize the syntax parser to check if the string can be derived from the source language's grammar
{
    Status.push(0);
    int x, y, z, length, w;
    string tmp;
    x = 0;
    z = -1;
    while (1)
    {
        x++;
        tmp = ACTION[Status.top()][tape.front()];
        if (tmp[0] == 'e')
        {
            y = -1;
            GetAnalysis(x, y, z);
        }
        else if (tmp[0] == 's')
        {
            y = 0;
            GetAnalysis(x, y, z);
            Symbol.push(tape.front());
            tape.pop();
            Status.push(Changenum(tmp));
        }
        else if (tmp[0] == 'r')
        {
            y = 1;
            z = Changenum(tmp);
            GetAnalysis(x, y, z);
            length = Productions[z]->Rightpart.size();
            for (int i = 0; i < length; i++)
            {
                Symbol.pop();
                Status.pop();
            }
            Symbol.push(Productions[z]->Leftpart);
            w = GOTO[Status.top()][Symbol.top()];
            Status.push(w);
        }
        else
        {
            y = 2;
            GetAnalysis(x, y, z);
        }
        if (y == -1 || y == 2)
        {
            break;
        }
    }
}
void Compile() // Initiate the compilation process
{
    fopen_s(&f, "E:/Code Repository/C++/Code/Group/Simple Compiler/test/Test1.txt", "r");
    ReadTest();
    cout << "Lexical analysis result: " << endl;
    Scanner();
    cout << endl;
    if (!judge)
    {
        cout << "Lexical analyzer reports an error, and syntax analysis will not proceed!" << endl;
    }
    else
    {
        cout << "Sequence of lexical units: " << endl;
        queue<string> q;
        q = tape;
        while (!q.empty())
        {
            cout << q.front();
            q.pop();
        }
        tape.push("$");
        cout << endl
             << endl;
        cout << "Analysis process: " << endl;
        cout << "    " << setw(60) << setiosflags(ios::left) << "stack" << setw(40) << setiosflags(ios::left) << "symbol" << setw(70) << setiosflags(ios::left) << "input" << setw(40) << setiosflags(ios::left) << "action" << endl;
        Analysis();
    }
}
int main()
{
    ReadGrammar();
    GetFIRSTSet();
    GetFOLLOWSet();
    // PrintFIRSTSet();  // Output FIRST set
    // PrintFOLLOWSet(); // Output FOLLOW set
    GetStatusSet();
    // PrintStatusSet(); // Output itemset
    GetR0Table();
    // PrintLR0Table(); // Output LR0 analysis table
    Compile();
    return 0;
}