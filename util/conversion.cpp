#include <iostream>
using namespace std;

int string_to_int(string item)
{
    auto convitr = item.rbegin();
    auto multiplier = 1;
    auto res = 0;
    while (convitr != item.rend())
    {
        res = res + multiplier * (*convitr - '0');
        convitr++;
        multiplier *= 10;
    }
    return res;
}

/*int main()
{
    cout << string_to_int("100") + string_to_int("50") << endl;
}
*/