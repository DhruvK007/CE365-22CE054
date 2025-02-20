#include <bits/stdc++.h>
using namespace std;

bool S();
bool L();
bool Ldash();

string str;
int i = 0;

bool S()
{
    // a
    if (i < str.length() && str[i] == 'a')
    {
        i++;
        return true;
    }

    // (L)
    if (i < str.length() && str[i] == '(')
    {
        i++;
        if (L())
        {
            if (i < str.length() && str[i] == ')')
            {
                i++;
                return true;
            }
        }
    }
    return false;
}

bool L()
{
    // SL'
    if (S())
    {
        return Ldash();
    }
    return false;
}

bool Ldash()
{
    // ,S L'
    if (i < str.length() && str[i] == ',')
    {
        i++;
        if (S())
        {
            return Ldash();
        }
        return false;
    }

    // epsilon
    return true;
}

int main()
{
    cout << "Enter the string: ";
    cin >> str;

    i = 0;
    if (S() && i == str.length())
    {
        cout << "String is valid\n";
    }
    else
    {
        cout << "String is invalid\n";
    }

    return 0;
}
