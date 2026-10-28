
#include <iostream>
#include <string>
using namespace std;

#define SIZE 100

char stack[SIZE];
int top = -1;

void push(char ch)
{
    if (top < SIZE - 1)
    {
        stack[++top] = ch;
    }
}

char pop()
{
    if (top == -1)
    {
        return '\0';
    }

    return stack[top--];
}

int main()
{
    string exp;
    bool balanced = true;

    cout << "Enter an expression: ";
    getline(cin, exp);

    for (int i = 0; i < exp.length(); i++)
    {
        char ch = exp[i];

        if (ch == '(' || ch == '{' || ch == '[')
        {
            push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (top == -1)
            {
                balanced = false;
                break;
            }

            char opening = pop();

            if ((ch == ')' && opening != '(') ||
                (ch == '}' && opening != '{') ||
                (ch == ']' && opening != '['))
            {
                balanced = false;
                break;
            }
        }
    }

    if (top != -1)
    {
        balanced = false;
    }

    if (balanced)
    {
        cout << "Parentheses are balanced.\n";
    }
    else
    {
        cout << "Parentheses are not balanced.\n";
    }

    return 0;
}

