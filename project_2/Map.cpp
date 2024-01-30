//
//  Map.cpp
//  project_2
//
//  Created by Leison Gao on 1/29/24.
//

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map() {
    // defining doubly linked list with dummy node
    m_head = new Node;
    m_tail = m_head;
    m_head->next = nullptr;
    m_head->previous = nullptr;
    m_size = 0;
}

Map::~Map() {
    // using two trailing pointers to delete nodes, p stores value of next and delp used to delete previous node
    Node* delp = m_head;
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        delete delp;
        delp = p;
    }
    delete delp;
}

Map::Map(const Map& ref) {
    // creating deep copy of Map by allocating new memory and nodes for all nodes in linked list
    
    // initializing dummy node
    m_size = ref.m_size;
    m_head = new Node;
    Node* m_p = m_head;
    m_head->previous = nullptr;
    
    // tracing nodes in ref Map and linking them to new dummy node
    for(Node* p = ref.m_head->next; p != nullptr; p = p->next) {
        Node* tempNode = new Node;
        m_p->next = tempNode;
        tempNode->key = p->key;
        tempNode->value = p->value;
        tempNode->previous = m_p;
        tempNode->next = nullptr;
        if (p->next == nullptr) { // at end of list to be copied
            m_tail = tempNode;
        }
        m_p = m_p->next;
    }
}

Map& Map::operator=(const Map& rhs) {
    if (this != &rhs) { // checking for aliasing
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

int Map::size() const{
    return m_size;
}


bool Map::empty() const {
    return m_size == 0;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    // checking if key is already in existing Map
    Node* p;
    for(p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key)
            return false;
        else if (p->key > key) // storing next position in ordered linked list
            break;
    }
    
    // allocating memory for new node in linked list
    Node* tempNode = new Node;
    tempNode->key = key;
    tempNode->value = value;
    
    if (p == nullptr) {
        if (m_size == 0) {   // adding first element
            tempNode->next = nullptr;
            tempNode->previous = m_head;
            m_head->next = tempNode;
            m_tail = tempNode;
        }
        else { // adding element to end of array
            tempNode->next = nullptr;
            tempNode->previous = m_tail;
            m_tail->next = tempNode;
            m_tail = tempNode;
        }
    }
    else { // adding element to the middle of the array, do not have to reassign m_head or m_tail pointers
        tempNode->next = p;
        tempNode->previous = p->previous;
        p->previous->next = tempNode;
        p->previous = tempNode;
    }
    
    m_size ++;
    return true;
}
    
bool Map::update(const KeyType& key, const ValueType& value) {
    for (Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) { // if key is found, then update value
            p->value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    // searching list for key
    Node* p;
    for(p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) { // key exists, updates value
            p->value = value;
            return true;
        }
        else if (p->key > key) // key doesn't exist, stores position in p
            break;
    }
    
    // inserting code identical to insert function
    
    // allocating memory for new Node
    Node* tempNode = new Node;
    tempNode->key = key;
    tempNode->value = value;
    
    if (p == nullptr) {
        if (m_size == 0) {   // adding first element
            tempNode->next = nullptr;
            tempNode->previous = m_head;
            m_head->next = tempNode;
            m_tail = tempNode;
        }
        else { // adding element to end of array
            tempNode->next = nullptr;
            tempNode->previous = m_tail;
            m_tail->next = tempNode;
            m_tail = tempNode;
        }
    }
    else {
        tempNode->next = p;
        tempNode->previous = p->previous;
        p->previous->next = tempNode;
        p->previous = tempNode;
    }
    
    m_size ++;
    return true;
}
        

bool Map::erase(const KeyType& key) {
    // searches for node with matching key
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            // uses temporary node to store location to free up memory
            Node* tempNode = p;
            
            if (p->next == nullptr) { // checking for end of the list, must reassign m_tail
                if (m_size == 0)
                    return false;
                p->previous->next = nullptr;
                m_tail = p->previous;
                delete tempNode;
            }
            else {
                p->previous->next = p->next;
                p->next->previous = p->previous;
                delete tempNode;
            }
            m_size --;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const {
    // searching for matching key, returns true if found
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    // searching for matching key, updates value and returns true if found
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            value = p->value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    // moving to correct position in ordered linked list, updates value when found
    if (i >= m_size || i < 0)
        return false; // list is too small to have a value greater than i elements
    
    // using pos to track position in linked list
    int pos = 0;
    Node* p = m_head->next;
    
    while (p != nullptr && pos != i) {
        p = p->next;
        pos ++;
    }
    
    if (p == nullptr)
        return false; // reached end of list
    
    // updating values
    key = p->key;
    value = p->value;
    return true;
}

void Map::swap(Map& other) {
    // swapping elements
    std::swap(this->m_head, other.m_head);
    std::swap(this->m_tail, other.m_tail);
    std::swap(this->m_size, other.m_size);
}
    
void Map::dump() {
    for(Node* p = m_head->next; p != nullptr; p = p->next)
        cerr << "Node with key: " << p->key << " and value: " << p->value << endl;
    cerr << endl;
}

bool merge(const Map& m1, const Map& m2, Map& result) {
    // erasing values in result map
    while (result.size() > 0) {
        KeyType key;
        ValueType value;
        result.get(0, key, value);
        result.erase(key);
    }
    
    // copying values from m1 into result map
    for (int i = 0; i < m1.size(); i ++) {
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        result.insert(key, value);
    }
    
    // comparing new values in m2 to values in result
    bool dupes = false;
    for(int i = 0; i < m2.size(); i ++) {
        KeyType key;
        ValueType value;
        m2.get(i, key, value);
        ValueType tempValue;
        result.get(key, tempValue);
        
        if (!result.contains(key)) { // map does not contain value
            result.insert(key, value);
        }
        else if (tempValue != value) { // map contains different value
            result.erase(key); // delete duplicate key from result
            dupes = true;
        }
        // if map contans same value, do nothing
    }
    
    if (dupes) // if different value was found, return false
        return false;
    return true;
}

void reassign(const Map& m, Map& result) {
    Map tempMap;
    KeyType key;
    ValueType value;
    ValueType prevValue;
    
    // creating trailing value
    m.get(m.size()-1, key, prevValue);
    
    // circularly reassigning vlaues to next key
    for (int i = 0; i < m.size(); i++) {
        m.get(i, key, value);
        result.insert(key, prevValue);
        prevValue = value;
    }
}
