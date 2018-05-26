#include <iostream>
#include <vector>
using namespace std;

template<class K, class V>
class bucket
{
public:
    bucket* next;
    int key;
    int value;
    bucket(int k, int v):key(k), value(v){}
};

class list
{
    bucket* newNode( int k, int v)
    {
        return new bucket(k, v);
    }
    bucket* getNode(int key)
    {
        bucket* res = NULL;
        auto c = head;
        while(c)
        {
            if(key == c->key)
            {
                res = c;
                break;
            }
            c = c->next;
        }
        return res;
    }
public:
    bucket* head;
    list():head(NULL){}
    bool push(int k, int v)
    {
        bucket* exists = getNode(k);
        if (!exists)
        {
            bucket* n = newNode(k, v);
            n->next = head;
            head = n;
        }
        else{
            exists->value = v;
        }
        return exists;
    }
    void deleteKey(int k)
    {
        auto c = head;
        bucket* p = NULL;
        while (c)
        {
            if(k == c->key)
            {
                if(c == head)
                {
                    head = c->next;
                    delete c;
                    c = NULL;
                }
                else if (c->next == NULL)
                {
                    p->next = NULL;
                    delete c;
                    c = NULL;
                }
                else
                {
                    p->next = c->next;
                    delete c;
                    c = NULL;
                }
                break;
            }
            p = c;
            c = c->next;
        }
    }
    ~list()
    {
        auto c = head;
        bucket* next = NULL;
        while (c)
        {
            next = c->next;
            delete c;
            c = next;
        }
    }
    int getVal(int k)
    {
        auto res = getNode(k);
        return res ? res->value : -1;
    }
    bucket* getHead()
    {
        return head;
    }
    void print()
    {
        bucket* c = head;
        while(c)
        {
            cout << c->key << " ";
            c = c->next;
        }
        cout << endl;
    }
};

class HashMap
{
    vector<list*>* hashMap; 
    int capacity;
    int size;
    const float LOADFACTOR = 5.0;
    int hashCode(int key)
    {
        return key % (capacity/(int)LOADFACTOR);
    }
    void rehash ()
    {
        capacity = capacity * 2; // capacity should be doubled to have constant LF
        vector<list*>* newHashMap = new vector<list*>(hashMap->size() * 2);
        for (int i = 0; i < hashMap->size(); i++)
        {
            list* existing_list = hashMap->at(i);
            auto c = existing_list->getHead();
            while(c)
            {
                list* buckets = newHashMap->at(hashCode(c->key));
                if (!buckets) (*newHashMap)[hashCode(c->key)] = new list();
                newHashMap->at(hashCode(c->key))->push(c->key, c->value);
                c = c->next;
            }
            delete existing_list;
            existing_list = NULL;
        }
        delete hashMap;
        hashMap = newHashMap;

    }
public:

    HashMap(int n) : size(0), capacity(n)
    {
        hashMap = new vector<list*>();
        hashMap->resize(n/LOADFACTOR, NULL);
    }
    void put (int k, int v)
    {
        auto idx = hashCode(k);
        auto buckets = hashMap->at(idx);
        if(!buckets) (*hashMap)[idx] = new list();
        if (!hashMap->at(idx)->push(k, v))
        {
            size++;
        }
        float checker = (float)size / (float)hashMap->size();
        
        if(checker > LOADFACTOR)
        {
            rehash();
        }
    }
    int get(int k)
    {
        auto idx = hashCode(k);
        auto buckets = hashMap->at(hashCode(k));
        if(!buckets) return -1;
        return buckets->getVal(k);
    }
    void deleteKey(int k)
    {
        hashMap->at(hashCode(k))->deleteKey(k);
        auto buckets = hashMap->at(hashCode(k));
        if(!buckets) return;
        buckets->deleteKey(k);
    }

    void print ()
    {
        for (int i = 0; i < hashMap->size(); i++)
        {
            hashMap->at(i)->print();
        }
    }

    ~HashMap()
    {
        delete hashMap;
    }
};


/*int main()
{
    HashMap h(20);

    for (int i = 0; i < 40; i++)
    {
        h.put(100+i, 1);
    }

    h.print();

    cout << h.get(119) << endl;

    cout << h.get(20) << endl;

    h.deleteKey(119);
    h.deleteKey(121);
    h.deleteKey(132);

    cout << h.get(119) << endl;

    h.print();

}*/