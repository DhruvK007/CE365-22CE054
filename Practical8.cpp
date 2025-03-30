#include <bits/stdc++.h>
using namespace std;

set<char> computeFirst(const vector<char> &sequence, const map<char, set<char>> &FIRST)
{
    set<char> result;
    bool allHaveEpsilon = true;

    for (const char symbol : sequence)
    {
        // If terminal, add it to result and break
        if (FIRST.find(symbol) == FIRST.end())
        {
            result.insert(symbol);
            allHaveEpsilon = false;
            break;
        }
        else
        {
            bool hasEpsilon = false;
            for (char s : FIRST.at(symbol))
            {
                if (s == '^')
                    hasEpsilon = true;
                else
                    result.insert(s);
            }

            if (!hasEpsilon)
            {
                allHaveEpsilon = false;
                break;
            }
        }
    }

    if (allHaveEpsilon)
        result.insert('^');

    return result;
}

int main()
{

    vector<pair<char, vector<char>>> grammar = {
        {'S', {'A', 'X'}},
        {'X', {'Y', 'C'}},
        {'Y', {'B'}},
        {'Y', {'^'}},
        {'A', {'a'}},
        {'A', {'^'}},
        {'B', {'b'}},
        {'C', {'(', 'S', ')'}},
        {'C', {'c'}}};

    map<char, set<char>> FIRST = {
        {'S', {'a', 'b', '(', 'c'}},
        {'A', {'a', '^'}},
        {'B', {'b'}},
        {'C', {'(', 'c'}},
        {'Y', {'b', '^'}},
        {'X', {'b', '(', 'c'}}};

    map<char, set<char>> FOLLOW = {
        {'S', {')', '$'}},
        {'A', {'b', '(', 'c'}},
        {'X', {')', '$'}},
        {'Y', {'(', 'c'}},
        {'C', {')', '$'}}};
        
    vector<char> terminals = {'a', 'b', '(', ')', 'c', '$'};
    vector<char> nonterminals = {'S', 'A', 'B', 'C', 'X', 'Y'};

    map<char, map<char, vector<char>>> table;
    bool isLL1 = true;

    for (auto prod : grammar)
    {
        char X = prod.first;
        vector<char> alpha = prod.second;
        set<char> firstAlpha = computeFirst(alpha, FIRST);

        // For each terminal in FIRST(alpha)
        for (auto a : firstAlpha)
        {
            if (a != '^')
            {
                if (table[X].count(a))
                {
                    isLL1 = false;
                    cout << "Conflict detected for " << X << " with input " << a << endl;
                }
                else
                {
                    table[X][a] = alpha;
                }
            }
        }

        // If α can derive ε, for each terminal b in FOLLOW(X)
        if (firstAlpha.count('^'))
        {
            for (auto b : FOLLOW[X])
            {
                if (table[X].count(b))
                {
                    isLL1 = false;
                    cout << "Conflict detected for " << X << " with input " << b << endl;
                }
                else
                {
                    table[X][b] = alpha;
                }
            }
        }
    }

    cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(16) << "Non-terminal";
    for (auto t : terminals)
        cout << "| " << left << setw(13) << t << " ";
    cout << "|" << endl;

    cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

    for (auto nt : nonterminals)
    {
        cout << "| " << left << setw(15) << nt << " ";
        for (auto t : terminals)
        {
            cout << "| ";
            if (table[nt].count(t))
            {
                string prodStr = string(1, nt) + " -> ";
                for (auto s : table[nt][t])
                    prodStr += s;
                cout << left << setw(13) << prodStr;
            }
            else
            {
                cout << left << setw(13) << "";
            }
            cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

    if (!isLL1)
    {
        cout << "Grammar is NOT LL(1)" << endl;
        return 0;
    }
    else
    {
        cout << "Grammar is LL(1)" << endl;
    }

    cout << "Enter an input string: ";
    string input;
    getline(cin, input);

    // Changed to use vector<char>
    vector<char> tokens;
    for (char c : input)
        tokens.push_back(c);
    tokens.push_back('$');

    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('S');
    int pos = 0;

    while (!parseStack.empty())
    {
        char top = parseStack.top();
        char current = (pos < tokens.size()) ? tokens[pos] : '$';

        if (top == '$')
        {
            if (current == '$')
            {
                cout << "Valid string" << endl;
                break;
            }
            else
            {
                cout << "Invalid string" << endl;
                break;
            }
        }

        if (find(nonterminals.begin(), nonterminals.end(), top) != nonterminals.end())
        {
            if (table[top].count(current))
            {
                vector<char> prod = table[top][current];
                parseStack.pop();
                if (prod[0] != '^')
                {
                    for (auto it = prod.rbegin(); it != prod.rend(); ++it)
                    {
                        parseStack.push(*it);
                    }
                }
            }
            else
            {
                cout << "Invalid string" << endl;
                break;
            }
        }
        else
        {
            if (top == current)
            {
                parseStack.pop();
                pos++;
            }
            else
            {
                cout << "Invalid string" << endl;
                break;
            }
        }
    }

    return 0;
}