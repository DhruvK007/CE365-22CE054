#include <bits/stdc++.h>
using namespace std;

set<string> computeFirst(const vector<string> &sequence, const map<string, set<string>> &FIRST)
{
    set<string> result;
    bool allHaveEpsilon = true;

    for (const string symbol : sequence)
    {
        if (FIRST.find(symbol) == FIRST.end())
        {
            result.insert(symbol);
            allHaveEpsilon = false;
            break;
        }
        else
        {
            bool hasEpsilon = false;
            for (string s : FIRST.at(symbol))
            {
                if (s == "^")
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
        result.insert("^");

    return result;
}

int main()
{
    vector<pair<string, vector<string>>> grammar = {
        {"S", {"A", "B", "C"}},
        {"A", {"a"}},
        {"A", {"^"}},
        {"B", {"b"}},
        {"B", {"^"}},
        {"C", {"(", "S", ")"}},
        {"C", {"c"}}};

    map<string, set<string>> FIRST = {
        {"S", {"a", "b", "(", "c"}},
        {"A", {"a", "^"}},
        {"B", {"b", "^"}},
        {"C", {"(", "c"}}};

    map<string, set<string>> FOLLOW = {
        {"S", {")", "$"}},
        {"A", {"b", "(", ")", "$"}},
        {"B", {"c", ")", "$"}},
        {"C", {")", "$"}}};

    vector<string> terminals = {"a", "b", "(", ")", "c", "$"};
    vector<string> nonterminals = {"S", "A", "B", "C"};

    map<string, map<string, vector<string>>> table;
    bool isLL1 = true;

    for (auto prod : grammar)
    {
        string X = prod.first;
        vector<string> alpha = prod.second;
        set<string> firstAlpha = computeFirst(alpha, FIRST);

        // For each terminal in FIRST(alpha)
        for (auto a : firstAlpha)
        {
            if (a != "^")
            {
                if (table[X].count(a))
                {
                    isLL1 = false;
                }
                else
                {
                    table[X][a] = alpha;
                }
            }
        }

        if (firstAlpha.count("^"))
        {
            for (auto b : FOLLOW[X])
            {
                if (table[X].count(b))
                {
                    isLL1 = false;
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
    for (auto &t : terminals)
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
                string prodStr = nt + " -> ";
                for (auto s : table[nt][t])
                    prodStr += s + " ";
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

    vector<string> tokens;
    for (char c : input)
        tokens.push_back(string(1, c));
    tokens.push_back("$");

    stack<string> parseStack;
    parseStack.push("$");
    parseStack.push("S");
    int pos = 0;

    while (!parseStack.empty())
    {
        string top = parseStack.top();
        string current = (pos < tokens.size()) ? tokens[pos] : "$";

        if (top == "$")
        {
            if (current == "$")
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
                vector<string> prod = table[top][current];
                parseStack.pop();
                if (prod[0] != "^")
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