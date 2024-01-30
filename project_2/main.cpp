//
//  main.cpp
//  project_2
//
//  Created by Leison Gao on 1/29/24.
//

#include <iostream>
#include <cassert>
#include "Map.hpp"
using namespace std;

bool merge(const Map& m1, const Map& m2, Map& result) {
    while (result.size() > 0) {
        KeyType key;
        ValueType value;
        result.get(0, key, value);
        result.erase(key);
    }
    
    for (int i = 0; i < m1.size(); i ++) {
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        result.insert(key, value);
    }
    
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
        else if (tempValue != value) {
            result.erase(key);
            dupes = true;
        }
        else
            result.insert(key, value);
        
    }
    
    if (dupes)
        return false;
    return true;
}

void reassign(const Map& m, Map& result) {
    Map tempMap;
    KeyType key;
    ValueType value;
    ValueType prevValue;
    m.get(m.size()-1, key, prevValue);
    
    for (int i = 0; i < m.size(); i++) {
        m.get(i, key, value);
        result.insert(key, prevValue);
        prevValue = value;
    }
}

int main() {
    Map m1;
    Map m2;
    Map m3;
    m1.insert("Ethel", 456);
    m1.insert("Fred", 123);
    m1.insert("Lucy", 789);
//    m1.insert("Ricky", 321);

//    m1.dump();

    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);
    
    m3.insert("China", 981);
    m3.insert("Japan", 89);
    m3.insert("Ian", 17);
    
    m1.erase("Fred");
    m1.erase("Lucy");
//    merge(m1, m2, m3);
    
//    m3.dump();
//    reassign(m1, m3);
//    m3.dump();
//    m1.dump();
    if (merge(m1, m2, m3))
        cout << "Successfully merged!" << endl;
    else
        cout << "Did not merge" << endl;
    
    cout << m3.size() << endl;
    m3.dump();

}
