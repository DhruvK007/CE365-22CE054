#include <bits/stdc++.h>
using namespace std;

// Function to check if a string is a valid identifier
bool isIdentifier(const string &str)
{
    // Check if empty or doesn't start with letter/underscore
    if (str.empty() || (!isalpha(str[0]) && str[0] != '_'))
    {
        return false;
    }

    // Check if str is a keyword
    static const unordered_set<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"};

    if (keywords.find(str) != keywords.end())
    {
        return false;
    }

    // Check remaining characters with simple for loop
    for (size_t i = 1; i < str.length(); i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
        {
            return false;
        }
    }
    return true;
}

// Function to check if a string is a numeric constant
bool isConstant(const string &str)
{
    if (str.empty())
        return false;

    int i = 0;
    bool hasDecimal = false;

    // Check sign
    if (str[0] == '+' || str[0] == '-')
    {
        if (str.length() == 1)
            return false;
        i = 1;
    }

    // Check digits and decimal point
    for (; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            if (hasDecimal)
                return false;
            hasDecimal = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to check if a string is a valid string literal
bool isStringLiteral(const string &str)
{
    if (str.length() < 2)
        return false;

    char first = str[0];
    char last = str[str.length() - 1];

    if ((first == '"' && last == '"') || (first == '\'' && last == '\''))
    {
        return str.length() > 2;
    }
    return false;
}

// Simple tokenizer function
vector<string> tokenizeLine(const string &line)
{
    vector<string> tokens;
    string current;

    for (int i = 0; i < line.length(); i++)
    {
        char c = line[i];

        // Handle strings
        if (c == '"' || c == '\'')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current = "";
            }

            string str = string(1, c);
            i++;
            while (i < line.length() && line[i] != c)
            {
                str += line[i];
                i++;
            }
            if (i < line.length())
                str += line[i];
            tokens.push_back(str);
            continue;
        }

        // Handle operators and punctuation
        if (ispunct(c) && c != '_')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current = "";
            }

            // Two-character operators
            if (i + 1 < line.length())
            {
                string op = string(1, c) + line[i + 1];
                if (op == "++" || op == "--" || op == "==" || op == "!=" ||
                    op == ">=" || op == "<=" || op == "&&" || op == "||" ||
                    op == "+=" || op == "-=" || op == "*=" || op == "/=" ||
                    op == "%=" || op == "<<" || op == ">>")
                {
                    tokens.push_back(op);
                    i++;
                    continue;
                }
            }
            // Handle Negative Numbers (e.g. -5)
            if (c == '-' && isdigit(line[i + 1]))
            {
                current += c;
                continue;
            }
            tokens.push_back(string(1, c));
        }
        else if (isspace(c))
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current = "";
            }
        }
        else
        {
            current += c;
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }

    return tokens;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file)
    {
        cout << "Unable to open file: " << argv[1] << endl;
        return 1;
    }

    unordered_set<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"};

    unordered_set<string> operators = {
        "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=",
        "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=", "%="};

    unordered_set<string> punctuations = {
        ";", ",", "(", ")", "{", "}", "[", "]", ".", ":", "?", "#"};

    unordered_set<string> symbolTable;
    vector<pair<int, string>> errors;
    string line;
    int lineNumber = 0;
    bool inComment = false;

    while (getline(file, line))
    {
        lineNumber++;
        string cleanLine;

        // Handle multi-line comments
        if (inComment)
        {
            int end = line.find("*/");
            if (end != -1)
            {
                line = line.substr(end + 2);
                inComment = false;
            }
            else
            {
                continue;
            }
        }

        // Process line
        for (int i = 0; i < line.length(); i++)
        {
            // Skip single-line comments
            if (i + 1 < line.length() && line[i] == '/' && line[i + 1] == '/')
            {
                break;
            }

            // Handle multi-line comments
            if (i + 1 < line.length() && line[i] == '/' && line[i + 1] == '*')
            {
                inComment = true;
                i += 2;
                while (i + 1 < line.length())
                {
                    if (line[i] == '*' && line[i + 1] == '/')
                    {
                        inComment = false;
                        i++;
                        break;
                    }
                    i++;
                }
                continue;
            }

            if (!inComment)
            {
                cleanLine += line[i];
            }
        }

        // Process tokens
        vector<string> tokens = tokenizeLine(cleanLine);
        for (const string &token : tokens)
        {
            if (token.empty())
                continue;

            if (keywords.find(token) != keywords.end())
            {
                cout << "Keyword: " << token << endl;
            }
            else if (operators.find(token) != operators.end())
            {
                cout << "Operator: " << token << endl;
            }
            else if (punctuations.find(token) != punctuations.end())
            {
                cout << "Punctuation: " << token << endl;
            }
            else if (isStringLiteral(token))
            {
                cout << "String: " << token << endl;
            }
            else if (isConstant(token))
            {
                cout << "Constant: " << token << endl;
            }
            else if (isIdentifier(token))
            {
                cout << "Identifier: " << token << endl;
                symbolTable.insert(token);
            }
            else
            {
                errors.push_back({lineNumber, token});
            }
        }
    }

    // Show errors
    if (!errors.empty())
    {
        cout << "\nLEXICAL ERRORS" << endl;
        for (const auto &error : errors)
        {
            cout << error.second << " invalid lexeme at line " << error.first << endl;
        }
    }

    // Show symbol table
    cout << "\nSYMBOL TABLE ENTRIES" << endl;
    vector<string> sorted(symbolTable.begin(), symbolTable.end());
    sort(sorted.begin(), sorted.end());
    for (int i = 0; i < sorted.size(); i++)
    {
        cout << (i + 1) << ") " << sorted[i] << endl;
    }

    return 0;
}