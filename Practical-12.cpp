#include <bits/stdc++.h>
using namespace std;

bool isOperator(char c) { return string("+-*/^").find(c) != -1; }
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else
        return 0;
}

double applyOp(double a, double b, char op)
{

    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}
bool isNumber(const string s) { return regex_match(s, regex("\\d+(\\.\\d+)?")); }
bool isVariable(const string s) { return regex_match(s, regex("[a-zA-Z][a-zA-Z0-9]*")); }

vector<string> tokenize(const string &expr)
{
    vector<string> tokens;
    string cur;
    for (char c : expr)
    {
        if (isspace(c) || isOperator(c) || c == '(' || c == ')')
        {
            if (!cur.empty())
                tokens.push_back(cur), cur.clear();
            if (!isspace(c))
                tokens.push_back(string(1, c));
        }
        else
            cur += c;
    }
    if (!cur.empty())
        tokens.push_back(cur);
    return tokens;
}

vector<string> infixToPostfix(const vector<string> &tokens)
{
    vector<string> postfix;
    stack<string> s;
    for (const string &t : tokens)
    {
        if (isNumber(t) || isVariable(t))
            postfix.push_back(t);
        else if (t == "(")
            s.push(t);
        else if (t == ")")
        {
            while (!s.empty() && s.top() != "(")
                postfix.push_back(s.top()), s.pop();
            s.pop();
        }
        else
        {
            while (!s.empty() && precedence(s.top()[0]) >= precedence(t[0]))
                postfix.push_back(s.top()), s.pop();
            s.push(t);
        }
    }
    while (!s.empty())
        postfix.push_back(s.top()), s.pop();
    return postfix;
}

vector<string> evaluateConstants(const vector<string> &postfix)
{
    stack<string> s;
    for (const string &t : postfix)
    {
        if (isNumber(t) || isVariable(t))
            s.push(t);
        else
        {
            string b = s.top();
            s.pop();
            string a = s.top();
            s.pop();
            if (isNumber(a) && isNumber(b))
            {
                ostringstream ss;
                ss << applyOp(stod(a), stod(b), t[0]);
                s.push(ss.str());
            }
            else
                s.push(a), s.push(b), s.push(t);
        }
    }
    vector<string> result;
    while (!s.empty())
        result.insert(result.begin(), s.top()), s.pop();
    return result;
}

string postfixToInfix(vector<string> &postfix)
{
    stack<string> s;
    for (string &t : postfix)
    {
        if (isNumber(t) || isVariable(t))
            s.push(t);
        else
        {
            string b = s.top();
            s.pop();
            string a = s.top();
            s.pop();
            s.push(a + " " + t + " " + b);
        }
    }
    return s.top();
}

int main()
{
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);
    vector<string> tokens = tokenize(expr);
    vector<string> optimized = evaluateConstants(infixToPostfix(tokens));
    cout << "Optimized expression: " << postfixToInfix(optimized) << endl;
    return 0;
}
