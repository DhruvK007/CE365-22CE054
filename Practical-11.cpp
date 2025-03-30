#include <bits/stdc++.h>
using namespace std;

struct Quadruple
{
    string op;
    string arg1;
    string arg2;
    string result;
};

class QuadrupleGenerator
{
private:
    string expression;
    vector<Quadruple> quadruples;
    int tempCount;
    int currentPos;
    char currentChar;

    void nextChar()
    {
        if (currentPos < expression.length())
        {
            currentChar = expression[currentPos++];
        }
        else
        {
            currentChar = '\0';
        }
    }

    void skipWhitespace()
    {
        while (currentChar == ' ' || currentChar == '\t')
            nextChar();
    }

    string newTemp()
    {
        return "t" + to_string(++tempCount);
    }

    string addQuadruple(const string &op, const string &arg1, const string &arg2)
    {
        string result = newTemp();
        quadruples.push_back({op, arg1, arg2, result});
        return result;
    }

    // Parse the expression according to the grammar
    // E -> E + T | E - T | T
    string parseE()
    {
        string term1 = parseT();

        while (currentChar == '+' || currentChar == '-')
        {
            char op = currentChar;
            nextChar();
            skipWhitespace();

            string term2 = parseT();
            term1 = addQuadruple(string(1, op), term1, term2);
        }

        return term1;
    }

    // T -> T * F | T / F | F
    string parseT()
    {
        string factor1 = parseF();

        while (currentChar == '*' || currentChar == '/' || currentChar == '^')
        {
            char op = currentChar;
            nextChar();
            skipWhitespace();

            string factor2 = parseF();
            factor1 = addQuadruple(string(1, op), factor1, factor2);
        }

        return factor1;
    }

    // F -> (E) | digit
    string parseF()
    {
        skipWhitespace();

        if (currentChar == '(')
        {
            nextChar(); // Skip '('
            skipWhitespace();

            string result = parseE();

            if (currentChar == ')')
            {
                nextChar(); // Skip ')'
                skipWhitespace();
            }
            else
            {
                cout << "Error: Missing closing parenthesis" << endl;
            }

            return result;
        }
        else if (isdigit(currentChar) || currentChar == '.')
        {
            // Parse a number (integer or decimal)
            string number;

            // Parse the integer part
            while (isdigit(currentChar))
            {
                number += currentChar;
                nextChar();
            }

            // Parse the decimal part if present
            if (currentChar == '.')
            {
                number += currentChar;
                nextChar();

                while (isdigit(currentChar))
                {
                    number += currentChar;
                    nextChar();
                }
            }

            skipWhitespace();
            return number;
        }
        else
        {
            cout << "Error: Unexpected character '" << currentChar << "'" << endl;
            return "";
        }
    }

public:
    QuadrupleGenerator() : tempCount(0), currentPos(0) {}

    // Generate quadruples for the given expression
    vector<Quadruple> generate(const string &expr)
    {
        quadruples.clear();
        tempCount = 0;
        expression = expr;
        currentPos = 0;
        nextChar();

        parseE();

        return quadruples;
    }

    // Display the quadruple table with proper formatting
    void displayQuadruples()
    {
        cout << "\nQuadruple Table:\n";
        cout << "+----------+----------+----------+----------+" << endl;
        cout << "| Operator | Operand 1| Operand 2|   Result |" << endl;
        cout << "+----------+----------+----------+----------+" << endl;

        for (const auto &q : quadruples)
        {
            cout << "| " << setw(8) << left << q.op << " | "
                 << setw(8) << left << q.arg1 << " | "
                 << setw(8) << left << q.arg2 << " | "
                 << setw(8) << left << q.result << " |" << endl;
        }

        cout << "+----------+----------+----------+----------+" << endl;
    }
};

int main()
{
    QuadrupleGenerator generator;
    string expression;

    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    cout << "Input: " << expression << endl;

    vector<Quadruple> quadruples = generator.generate(expression);
    generator.displayQuadruples();

    return 0;
}