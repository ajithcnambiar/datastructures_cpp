#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class T>
class node
{
public:
    node<T>* next;
    T item;
    node():next(NULL){}
};

// enqueue O(1)
// dequeue O(1)
template<class T>
class Queue_LinkedList
{
    node<T>* last;
    node<T>* first;
    node<T>* newNode()
    {
        return new node<T>();
    }
public:
    Queue_LinkedList() : first(NULL), last(NULL){}

    void enqueue(T item)
    {
        auto oldLast = last;
        last = newNode();
        last->item = item;
        last->next = NULL;
        
        if(!isEmpty()) oldLast->next = last;
        else first = last;
    }

    void dequeue()
    {
        if(isEmpty()) return;
        auto newFirst = first->next;
        delete first;
        first = newFirst;
        if(isEmpty()) last = NULL;
    }

    bool isEmpty()
    {
        return first == NULL;
    }

    T front()
    {
        return first->item;
    }

    T back()
    {
        return last->item;
    }

};

int main()
{
    
    vector<string> sample = {"hello", "world", "!"};

    Queue_LinkedList<string> queue;

    for(int i = 0; i < sample.size(); i++)
    {
        queue.enqueue(sample[i]);
        cout << "front = " << queue.front() << " back = " << queue.back() << endl;
    }


    while(!queue.isEmpty())
    {
        cout << "front = " << queue.front() << " back = " << queue.back() << endl;
        queue.dequeue();
    }

}
