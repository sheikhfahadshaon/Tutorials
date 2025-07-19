/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

/*
operator     in stack precendence     out stack precendence
+, -              1                          2
*, /              3                          4
(                 5                          0
)                 0                          ?
*/

class calculator
{
private:
    vector<string> token;
    vector<string> postFixToken;

    int Operation(int b, int a, string op)
    {
        if (op == "+")
            return a + b;
        else if (op == "-")
            return a - b;
        else if (op == "*")
            return a * b;

        return a / b; // if op == "/";
    }

    int getOutPrecedence(string op)
    {
        if (op == "+" or op == "-")
            return 1;
        else if (op == "(")
            return 5;
        else if (op == ")")
            return 0;
        return 3;
    }

    int getInPrecedence(string op)
    {
        if (op == "+" or op == "-")
            return 2;
        else if (op == "(")
            return 0;
        return 4;
    }
    bool isOperator(string op)
    {
        return op == "+" or op == "-" or op == "*" or op == "/" or op == "(" or op == ")";
    }
    void infixToPostfix()
    {
        stack<string> opStack; // keeps track of the operators

        for (string s : token)
        {
            if (isOperator(s))
            {
                if (s == ")")
                {
                    while (!opStack.empty() and getInPrecedence(opStack.top()) > getOutPrecedence(s))
                    {
                        postFixToken.push_back(opStack.top());
                        opStack.pop();
                    }
                    opStack.pop();
                }
                else
                {
                    while (!opStack.empty() and getInPrecedence(opStack.top()) >= getOutPrecedence(s))
                    {
                        postFixToken.push_back(opStack.top());
                        opStack.pop();
                    }
                    opStack.push(s);
                }
            }
            else
                postFixToken.push_back(s);
        }

        while (!opStack.empty())
        {
            postFixToken.push_back(opStack.top());
            opStack.pop();
        }
    }
    int evaluate()
    {
        stack<int> opStack;
        for (string s : postFixToken)
        {
            if (isOperator(s))
            {
                int a = opStack.top();
                opStack.pop();
                int b = opStack.top();
                opStack.pop();

                opStack.push(Operation(a, b, s));
            }
            else
            {
                opStack.push(stoi(s));
            }
        }

        return opStack.top();
    }

public:
    calculator(string eqn)
    {
        // This Constructor is going to tokenize the equation
        for (int i = 0; i < eqn.length(); i++)
        {
            while (i < eqn.length() and eqn[i] == ' ')
                i++;

            string newToken = "";
            if (i < eqn.length() and isOperator(string(1, eqn[i])))
            {
                newToken += eqn[i];
            }
            else
            {
                while (i < eqn.length() and eqn[i] != ' ' and !isOperator(string(1, eqn[i])))
                    newToken += eqn[i++];

                i--;
            }

            if (newToken != "")
                token.push_back(newToken);
        }

        infixToPostfix();
    }

    void printToken()
    {
        for (string s : token)
            cout << s << ' ';
        cout << endl;
    }

    int Calculate()
    {
        return evaluate();
    }
};

int32_t main()
{
    calculator c = calculator("2-1 + 2 * (2 + 3)");

    cout << c.Calculate();
}