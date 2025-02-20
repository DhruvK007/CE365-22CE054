#include <bits/stdc++.h>
using namespace std;

void computeFirst(unordered_map<char, set<string>> &first, unordered_map<char, vector<string>> grammar, char nonTerminal)
{
    for (auto production : grammar[nonTerminal])
    {
        if (production == "^")
        {
            first[nonTerminal].insert("^");
        }
        else
        {
            for (char symbol : production)
            {
                if (isupper(symbol))
                { // Non-terminal
                    computeFirst(first, grammar, symbol);
                    for (auto f : first[symbol])
                    {
                        if (f != "^")
                        {
                            first[nonTerminal].insert(f);
                        }
                    }
                    if (first[symbol].find("^") == first[symbol].end())
                    {
                        break;
                    }
                }
                else
                { // Terminal
                    first[nonTerminal].insert(string(1, symbol));
                    break;
                }
            }
        }
    }
}

void computeFollow(unordered_map<char, set<string>> &follow, unordered_map<char, set<string>> &first, unordered_map<char, vector<string>> grammar, char nonTerminal)
{
    for (auto rule : grammar)
    {
        for (auto production : rule.second)
        {
            int pos = production.find(nonTerminal);
            if (pos != -1)
            {
                if (pos + 1 < production.length())
                {
                    char nextSymbol = production[pos + 1];
                    if (isupper(nextSymbol))
                    { // Non-terminal
                        for (auto f : first[nextSymbol])
                        {
                            if (f != "^")
                            {
                                follow[nonTerminal].insert(f);
                            }
                        }
                        if (first[nextSymbol].find("^") != first[nextSymbol].end())
                        {
                            for (auto f : follow[rule.first])
                            {
                                follow[nonTerminal].insert(f);
                            }
                        }
                    }
                    else
                    { // Terminal
                        follow[nonTerminal].insert(string(1, nextSymbol));
                    }
                }
                else
                {
                    for (auto f : follow[rule.first])
                    {
                        follow[nonTerminal].insert(f);
                    }
                }
            }
        }
    }
}

int main()
{
    unordered_map<char, vector<string>> grammar = {
        {'S', {"ABC", "D"}},
        {'A', {"a", "^"}},
        {'B', {"b", "^"}},
        {'C', {"(S)", "c"}},
        {'D', {"AC"}}};

    unordered_map<char, set<string>> first, follow;

    for (auto rule : grammar)
    {
        computeFirst(first, grammar, rule.first);
    }

    follow['S'].insert("$"); // $ is the end marker
    for (auto rule : grammar)
    {
        computeFollow(follow, first, grammar, rule.first);
    }

    cout << "First sets:\n";
    for (auto f : first)
    {
        cout << f.first << ": ";
        for (auto s : f.second)
        {
            cout << s << " ";
        }
        cout << endl;
    }

    cout << "\nFollow sets:\n";
    for (auto f : follow)
    {
        cout << f.first << ": ";
        for (auto s : f.second)
        {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}