#include <iostream>
#include <string>
using namespace std;

// push O(1)
// pop O(1)
template<class T>
class node
{
public:
    node<T>* next;
    T item;
    node() : next(NULL){}
};

template<class T>
class Stack_linkedlist
{
    node<T>* first;
    node<T>* newNode()
    {
        return new node<T>();
    }
public:
    Stack_linkedlist() : first(NULL){}
    void push (T item)
    {
        auto oldFirst = first;
        first = newNode();
        first->item = item;
        first->next = oldFirst;
    }
    void pop()
    {
        if(isEmpty()) return;
        auto curFirst = first;
        first = first->next;
        delete curFirst;
        curFirst = NULL;
    }
    T top()
    {
        return first->item;
    }
    bool isEmpty()
    {
        return first == NULL;
    }
    ~Stack_linkedlist()
    {
        while(!isEmpty()) pop();

        //cout << "successfully cleaned stack" << endl;
    }
};


/*
test client
int main()
{
    Stack_linkedlist<string> stack;
    stack.push("hello");
    stack.push("world");
    stack.push("!");

    while(!stack.isEmpty())
    {
        cout << stack.top() << endl;
        stack.pop();
    }
    stack.push("last");
    stack.push("elements");
}
*/