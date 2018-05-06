#include <iostream>
#include <string>
#include "Stack_linkedlist.cpp"
#include "../util/conversion.cpp"
using namespace std;


//Two Stack Algorithm - E. W. Dijkstra
// infix or post fix expression

int main()
{

    // Evaluate expression:
    // ( 1 + ( ( 2 + 3 ) * ( 4 * 5) ) )
    Stack_linkedlist<char> op_stack;
    Stack_linkedlist<int> val_stack;

    //string expression = "( 10 + ( ( 20 + 30 ) * ( 40 * 50 ) ) )";
    string expression = "( 1 ( ( 2 3 + ) ( 4 5 * ) * ) + )";

    auto itr = expression.begin();
    while (itr != expression.end())
    {
        if (*itr == ' ')
        {
            itr++;
            continue;
        }
        else if(*itr == '(')
        {
            // do nothing
        }
        else if (*itr == ')')
        {
            auto val1 = val_stack.top(); val_stack.pop();
            auto val2 = val_stack.top(); val_stack.pop();
            auto op = op_stack.top(); op_stack.pop();

            if (op == '+') val_stack.push(val1 + val2);
            else if (op == '-') val_stack.push(val2 - val1);
            else if (op == '*') val_stack.push(val1 * val2);
            else val_stack.push(val2 / val1);
        }
        else if (*itr == '+' || *itr == '-' || *itr == '*' || *itr == '/')
        {
            op_stack.push(*itr);
        }
        else // number
        {
            string item;       
            while(*itr != ' ')
            {
                item += *itr;
                itr++;
            }
            val_stack.push(string_to_int(item));
        }
        itr++;
    }
    auto res = val_stack.top(); val_stack.pop();
    if (!op_stack.isEmpty() || !val_stack.isEmpty())
    {
        cout << "terminated with error" << endl;
        return 0;
    }
    
    cout << "evaluated result = " << res << endl;
}