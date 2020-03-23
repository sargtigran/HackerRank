#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
private:
    void push_front(Node* n) {
        assert(n);
        if (mp.empty()) {
            tail = n;
        } else {
            n->next = head;
            head->prev = n;
        }
        head = n;
        mp.insert({n->key, n});  
    }

    void remove_node(int key) {
        auto it = mp.find(key);
        if (it != mp.end()) { 
            Node* n = it->second;
            if (head != tail) {
                if (n == head) {
                    head = head->next;
                    head->prev = nullptr;
                } else if (n == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                } else {
                    n->prev->next = n->next;
                    n->next->prev = n->prev;
                }
                n->next = n->prev = nullptr;
            }
            mp.erase(key);
            delete n;
        }
    }

public:
    LRUCache(int l) {
        cp = l;
        tail = nullptr;
        head = nullptr;
    } 

    void set(int key, int val) override {
        auto it = mp.find(key);
        if (it != mp.end()) {
            if (it->second == head) {
                it->second->value = val; 
                return;
            }
            remove_node(key);
        } else {
            if (mp.size() == cp) {
                remove_node(tail->key);
            }
        }
        auto n = new Node(key, val);
        push_front(n);
    }

    int get(int key) override {
        auto it = mp.find(key);
        if (it != mp.end()) {
            return it->second->value;
        }
        return -1;
    }
}

int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    
    for(i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
    }
    return 0;
}
