#include <bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> grammar = {
    {'S', {"ABC", "D"}},
    {'A', {"a", "^"}},
    {'B', {"b", "^"}},
    {'C', {"(S)", "c"}},
    {'D', {"AC"}}};

unordered_map<char, set<char>> FIRST;
unordered_map<char, set<char>> FOLLOW;

// Compute FIRST sets iteratively.
void computeFirst()
{
    for (auto p : grammar)
    {
        FIRST[p.first] = {};
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto p : grammar)
        {
            char A = p.first;
            for (auto prod : p.second)
            {
                bool allEps = true;
                for (char symbol : prod)
                {
                    if (!isupper(symbol))
                    {
                        if (FIRST[A].insert(symbol).second)
                        {
                            changed = true;
                        }
                        allEps = false;
                        break;
                    }
                    else
                    {
                        for (char f : FIRST[symbol])
                        {
                            if (f != '^' && FIRST[A].find(f) == FIRST[A].end())
                            {
                                FIRST[A].insert(f);
                                changed = true;
                            }
                        }
                        if (FIRST[symbol].find('^') == FIRST[symbol].end())
                        {
                            allEps = false;
                            break;
                        }
                    }
                }
                if (allEps)
                {
                    if (FIRST[A].insert('^').second)
                        changed = true;
                }
            }
        }
    }
}

void computeFollow()
{
    for (auto p : grammar)
    {
        FOLLOW[p.first] = {};
    }
    FOLLOW['S'].insert('$');

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto p : grammar)
        {
            char A = p.first;
            for (auto prod : p.second)
            {
                for (int i = 0; i < prod.size(); i++)
                {
                    char symbol = prod[i];
                    if (isupper(symbol))
                    { // Nonterminal
                        bool eps = true;
                        for (int j = i + 1; j < prod.size() && eps; j++)
                        {
                            eps = false;
                            char nextSym = prod[j];
                            if (!isupper(nextSym))
                            {
                                if (FOLLOW[symbol].insert(nextSym).second)
                                    changed = true;
                            }
                            else
                            {
                                for (char f : FIRST[nextSym])
                                {
                                    if (f != '^' && FOLLOW[symbol].find(f) == FOLLOW[symbol].end())
                                    {
                                        FOLLOW[symbol].insert(f);
                                        changed = true;
                                    }
                                }
                                if (FIRST[nextSym].find('^') != FIRST[nextSym].end())
                                    eps = true;
                            }
                        }
                        if (eps)
                        {
                            for (char f : FOLLOW[A])
                            {
                                if (FOLLOW[symbol].insert(f).second)
                                    changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    computeFirst();

    cout << "FIRST sets:\n";
    for (auto p : FIRST)
    {
        cout << p.first << " : { ";
        for (char c : p.second)
            cout << c << " ";
        cout << "}\n";
    }

    computeFollow();

    cout << "\nFOLLOW sets:\n";
    for (auto p : FOLLOW)
    {
        cout << p.first << " : { ";
        for (char c : p.second)
            cout << c << " ";
        cout << "}\n";
    }

    return 0;
}