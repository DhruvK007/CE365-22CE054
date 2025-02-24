#include <bits/stdc++.h>
using namespace std;

class State
{
public:
    int state;
    vector<pair<char, int>> transitions;
    State(int state, vector<pair<char, int>> transitions)
    {
        this->state = state;
        this->transitions = transitions;
    }
};

int main()
{
    int nSymbols, testCaseNo;
    cout << "Enter the test case number : ";
    cin >> testCaseNo;
    cin.ignore(); // To clear buffer after integer input

    if (testCaseNo == 3)
    {
        vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                          'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
                          '4', '5', '6', '7', '8', '9'};
        int initialState = 1, nStates = 3;
        vector<int> acceptStates = {2};

        vector<State> DFA;

        for (int i = 0; i < nStates; i++)
        {
            vector<pair<char, int>> temp;
            for (int j = 0; j < v.size(); j++)
            {
                if (i == 0)
                {
                    if (v[j] >= 'a' && v[j] <= 'z')
                        temp.push_back(make_pair(v[j], 2));
                    else
                        temp.push_back(make_pair(v[j], 3));
                }
                else
                {
                    temp.push_back(make_pair(v[j], i + 1));
                }
            }
            DFA.push_back(State(i + 1, temp));
        }

        string str;
        while (true)
        {
            cout << "\nInput String (type 'exit' to quit): ";
            getline(cin, str);

            if (str.empty())
            {
                cout << "Null String not allowed\n";
                continue;
            }
            if (str == "exit")
                break;

            int state = initialState;
            bool flag = false;
            for (char c : str)
            {
                bool found = false;
                for (auto trans : DFA[state - 1].transitions)
                {
                    if (trans.first == c)
                    {
                        state = trans.second;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    flag = true;
                    break;
                }
            }

            if (flag)
            {
                cout << "Invalid Character found in the input string\n";
                continue;
            }

            bool isValid = (find(acceptStates.begin(), acceptStates.end(), state) != acceptStates.end());

            if (isValid)
                cout << "Valid String\n";
            else
                cout << "Invalid String\n";
        }
    }
    else
    {
        cout << "Number of input symbols : ";
        cin >> nSymbols;

        vector<char> v;
        cout << "Input Symbols : ";
        for (int i = 0; i < nSymbols; i++)
        {
            char temp;
            cin >> temp;
            v.push_back(temp);
        }

        int nStates;
        cout << "Enter number of states : ";
        cin >> nStates;

        int initialState;
        cout << "Enter initial state : ";
        cin >> initialState;
        while (!(initialState <= nStates && initialState >= 1))
        {
            cout << "Invalid Initial State, Enter a valid One\n";
            cin >> initialState;
        }

        int nAcceptStates;
        cout << "Number of Accepting States : ";
        cin >> nAcceptStates;
        while (!(nAcceptStates <= nStates && nAcceptStates >= 1))
        {
            cout << "Invalid Number of Accepting States, Enter a valid One\n";
            cin >> nAcceptStates;
        }

        vector<int> acceptStates;
        cout << "Accepting States : ";
        for (int i = 0; i < nAcceptStates; i++)
        {
            int temp;
            cin >> temp;
            while (temp > nStates || temp < 1)
            {
                cout << "Invalid State, Enter a valid One\n";
                cin >> temp;
            }
            acceptStates.push_back(temp);
        }

        vector<State> DFA;
        cout << "Transition Table\n";
        for (int i = 1; i <= nStates; i++)
        {
            vector<pair<char, int>> temp;
            for (int j = 0; j < nSymbols; j++)
            {
                int transition;
                cout << i << " to " << v[j] << " -> ";
                cin >> transition;
                while (transition > nStates || transition < 1)
                {
                    cout << "Invalid Transition, Enter a valid One\n";
                    cout << i << " to " << v[j] << " -> ";
                    cin >> transition;
                }
                temp.push_back(make_pair(v[j], transition));
            }
            DFA.push_back(State(i, temp));
        }

        cin.ignore();

        string str;
        while (true)
        {
            cout << "\nInput String (type 'exit' to quit): ";
            getline(cin, str);

            if (str.empty())
            {
                cout << "Null String not allowed\n";
                continue;
            }
            if (str == "exit")
                break;

            int state = initialState;
            bool flag = false;
            for (char c : str)
            {
                bool found = false;
                for (auto trans : DFA[state - 1].transitions)
                {
                    if (trans.first == c)
                    {
                        state = trans.second;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    flag = true;
                    break;
                }
            }

            if (flag)
            {
                cout << "Invalid Character found in the input string\n";
                continue;
            }

            bool isValid = (find(acceptStates.begin(), acceptStates.end(), state) != acceptStates.end());

            if (isValid)
                cout << "Valid String\n";
            else
                cout << "Invalid String\n";
        }
    }
    return 0;
}
