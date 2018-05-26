#include "../queue/QueueWithDoubleLinkedList.cpp"
#include <unordered_map>
using namespace std;

class CacheItem
{
public:
    int id;
    string name;
    CacheItem(int i, string n) : id(i), name(n){}
    bool operator== (const CacheItem& r)
    {
        return id == r.id;
    }
    CacheItem& operator= (const CacheItem& r)
    {
        id = r.id;
        name = r.name;
        return *this;
    }
    CacheItem(const CacheItem& r)
    {
        id = r.id;
        name = r.name;
    }
    CacheItem():id(-1), name(""){}
};

ostream& operator<< (ostream& os, const CacheItem& v)
{
    cout << v.id << " --> " << v.name << endl;
    return os;
}

class LRUCache
{
    unordered_map<int, dl_node<CacheItem>*> LookUp;
    DoublyLinkedList<CacheItem>* queue;
    int size;
    int capacity;

    bool GetCacheItem(int key, CacheItem& c)
    {
        bool bPresent = false;
        unordered_map<int, dl_node<CacheItem>*>::iterator dllnode_itr = LookUp.find(key);

        bPresent = dllnode_itr != LookUp.end();

        if(bPresent)
        {
            dl_node<CacheItem>* dll_node = dllnode_itr->second;
            c = dll_node->data;

            queue->deleteNode(dll_node);
            LookUp.erase(dllnode_itr);

            dl_node<CacheItem>* dlnode = queue->push_front(c);
            LookUp.insert(make_pair(c.id, dlnode));

        }
        return bPresent;
    }

public:
    LRUCache(int s): size(0), capacity(s)
    {
        queue = new DoublyLinkedList<CacheItem>();
    }

    bool Get(int key, string& v)
    {
        CacheItem c;
        bool ret = GetCacheItem(key, c);
        v.clear();
        v = c.name;
        return ret;
    }

    string Get(int key)
    {
        string sVal;
        Get(key, sVal);
        cout << "Get "<<key << " --> " << sVal << endl;
        return sVal;
    }

    void Put(int key, string val)
    {
        unordered_map<int, dl_node<CacheItem>* >::iterator itr_key_queuepos = LookUp.find(key);
        
        if (itr_key_queuepos != LookUp.end())
        {
            dl_node<CacheItem>* dllnode = itr_key_queuepos->second;
            dllnode->data.name = val;
        }
        else
        {
            if(queue->getSize() == capacity)
            {
                dl_node<CacheItem>* item = queue->back();
                LookUp.erase(item->data.id);
                queue->deleteNode(item);
                size--;
            }
            CacheItem item(key, val);
            dl_node<CacheItem>* dlnode = queue->push_back(item);
            LookUp.insert(make_pair(key, dlnode));
            size++;
        }
    }
    void printQueue()
    {
        queue->printForward();
    }
};

int main ()
{
    LRUCache cache(5);

    vector<pair<int, string>> items({make_pair(1, "lion"), make_pair(2, "king"), make_pair(3, "is"), make_pair(4, "fine"), make_pair(5, "."), make_pair(6, "should"), make_pair(7, "do"), make_pair(8, "it"), make_pair(9, "better")});

    vector<pair<int, string>>::iterator itr = items.begin();

    while(itr != items.end())
    {
        cache.Put(itr->first, itr->second);
        itr++;
    }

    cache.printQueue();
    cache.Get(8);
    cache.printQueue();
    cache.Get(9);
    cache.printQueue();
    cache.Get(4);
    cache.printQueue();
    cache.Get(9);
    cache.printQueue();

    return 0;
}