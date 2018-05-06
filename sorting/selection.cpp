#include <vector>
#include <iostream>
#include "../util/show.cpp"
using namespace std;

template<class T>
class SelectionSort
{
    bool less(vector<T> bag, int j, int lowest)
    {
        return bag[j] < bag[lowest];
    }
    void exch (vector<T>& bag, int i, int j)
    {
        auto t = bag[i];
        bag[i] = bag[j];
        bag[j] = t;
    }
public:
    SelectionSort(vector<T> bag)
    {
        for (int i = 0; i < bag.size(); i++)
        {
            auto lowest = i;
            for (int j = i; j < bag.size(); j++)
            {
                if(less(bag, j, lowest)) lowest = j;
            }
            exch(bag, i, lowest);
        }
        showVector(bag);
    }
};

int main()
{
    SelectionSort<int> ss({5, 4, 2, 9, 1, 0});
}