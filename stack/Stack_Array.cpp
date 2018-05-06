#include <iostream>
using namespace std;


// push O(N)
// pop O(N)
template <class T>
class StackOfStrings_Array
{
    T* p;
    int capacity;
    int size;
    void resize(int length)
    {
        auto new_p = new T[length];
        for(auto i = 0; i < size; i++)
        {
            new_p[i] = p[i];
        }
        delete []p;
        p = new_p;
        capacity = length;
    }
public: 
    StackOfStrings_Array(int N) : capacity(N), size(0)
    {
        p = new T[capacity];
    }
    void push (T item)
    {
        if(size == capacity) 
        {
            resize(2*capacity);
        }
        p[size++] = item;
        cout << top () << endl;
    }
    void pop()
    {
        if (size == 0)return;
        p[size-1] = "nullptr";
        size--;
        // halve the array when one quarter full
        if(size == capacity/4) resize(capacity/2);
    }
    T top()
    {
        return p[size-1];
    }
    ~StackOfStrings_Array()
    {
        delete []p;
        p = nullptr;
        size = 0;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    int length()
    {
        return size;
    }
};

int main ()
{
    StackOfStrings_Array<string> stack(2);
    stack.push("hello");
    stack.push("world");
    stack.push("!");
    stack.push("here");
    stack.push("iam.");
    stack.push("this");
    stack.push("is");
    stack.push("me");
    
    while(!stack.isEmpty())
    {
        cout << stack.top() << endl;
        stack.pop();
    }
    stack.push("last");
    stack.push("elements");
    return 0;
}