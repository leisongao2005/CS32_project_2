//
//  Map.hpp
//  project_2
//
//  Created by Leison Gao on 1/29/24.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <string>
using KeyType = std::string;
using ValueType = int;

class Map
{
    public:
        Map();
        Map(const Map& ref);
        ~Map();
        Map& operator=(const Map& rhs);
        bool empty() const;
        int size() const;
        bool insert(const KeyType& key, const ValueType& value);
        bool update(const KeyType& key, const ValueType& value);
        bool insertOrUpdate(const KeyType& key, const ValueType& value);
        bool erase(const KeyType& key);
        bool contains(const KeyType& key) const;
        bool get(const KeyType& key, ValueType& value) const;
        bool get(int i, KeyType& key, ValueType& value) const;
        void swap(Map& other);
        void dump();
    private:
        struct Node
        {
            KeyType key;
            ValueType value;
            Node* next;
            Node* previous;
        };
        Node* m_head;
        Node* m_tail;
        int m_size;
    
};
#endif /* Map_hpp */
