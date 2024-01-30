//
//  Map.cpp
//  project_2
//
//  Created by Leison Gao on 1/29/24.
//

#include "Map.hpp"
#include <iostream>
using namespace std;

Map::Map() {
    m_head = new Node;
    m_tail = m_head;
    m_head->next = nullptr;
    m_head->previous = nullptr;
    m_size = 0;
}

Map::~Map() {
    Node* delp = m_head;
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        delete delp;
        delp = p;
    }
    delete delp;
}

Map::Map(const Map& ref) {
    m_size = ref.m_size;
    m_head = new Node;
    Node* m_p = m_head;
    for(Node* p = ref.m_head; p != nullptr; p = p->next) {
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
    m_tail = m_p;
}

Map& Map::operator=(const Map& rhs) {
    if (this != &rhs) {
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
    Node* tempNode = new Node;
    tempNode->key = key;
    tempNode->value = value;
    
    Node* p;
    for(p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key)
            return false;
        else if (p->key > key)
            break;
    }
    
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
    
bool Map::update(const KeyType& key, const ValueType& value) {
    for (Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            p->value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    for (Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            p->value = value;
            return true;
        }
    }
    
    Node* tempNode = new Node;
    tempNode->key = key;
    tempNode->value = value;
    
    Node* p;
    for(p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key)
            return false;
        else if (p->key > key)
            break;
    }
    
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
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            Node* tempNode = p;
            
            if (p->next == nullptr){
                if (m_size == 0)
                    return false;
                p->previous->next = nullptr;
                m_tail = p->previous;
                delete tempNode;
            }
            else {
                p->previous->next = p->next;
                p->next->previous = p->previous;
//                delete tempNode->previous->next;
                delete tempNode;
            }
            m_size --;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const {
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    for(Node* p = m_head->next; p != nullptr; p = p->next) {
        if (p->key == key) {
            value = p->value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i >= m_size)
        return false;
    
    int pos = 0;
    Node* p = m_head->next;
    
    while (p != nullptr && pos != i) {
        p = p->next;
        pos ++;
    }
    
    if (p == nullptr)
        return false;
    
    key = p->key;
    value = p->value;
    return true;
}

void Map::swap(Map& other) {
    std::swap(this->m_head, other.m_head);
    std::swap(this->m_tail, other.m_tail);
    std::swap(this->m_size, other.m_size);
}
    
void Map::dump() {
    for(Node* p = m_head; p != nullptr; p = p->next)
        cerr << "Node with key: " << p->key << " and value: " << p->value << endl;
    cerr << endl;
}
