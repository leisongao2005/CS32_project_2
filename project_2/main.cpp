//
//  main.cpp
//  project_2
//
//  Created by Leison Gao on 1/29/24.
//

#include <iostream>
#include <cassert>
#include "Map.h"
using namespace std;

int main() {
    // default constructor
    Map m;
      // For an empty map:
    assert(m.size() == 0);      // test size
    assert(m.empty());          // test empty
    assert(!m.erase("Ricky"));  // nothing to erase
    
    // checking insertion
    Map m1;
    assert(m1.insert("Ethel", 456));
    assert(m1.insert("Fred", 123));
    assert(m1.insert("Lucy", 789));
    assert(!m1.insert("Lucy", 123)); // inserting duplicate
    double x;
    assert(m1.get("Lucy", x) && x == 789); // checking value after duplicate insertion
    
    // checking updating;
    assert(m1.update("Lucy", 123));
    assert(m1.get("Lucy", x) && x == 123);// checking correct update
    assert(!m1.update("Ricky", 321)); // no key in list
    
    // checking insert/update
    assert(m1.insertOrUpdate("China", 981));
    assert(m1.insertOrUpdate("Lucy", 789));
    assert(m1.get("Lucy", x) && x == 789);// checking correct update
    
    // checking erase and contains
    assert(m1.contains("China")); // element in list
    assert(m1.erase("China"));
    assert(!m1.contains("China")); // element removed from list
    assert(!m1.erase("Japan")); // element not in list
    
    // checking get with integer
    string s;
    assert(m1.get(0, s, x));
    assert(s == "Ethel" && x == 456);
    assert(!m1.get(4, s, x)); // too large
    assert(s == "Ethel" && x == 456); // failed get did not change anything
    
    // checking merge
    Map m2;
    Map m3;
    m2.insert("Ricky", 321);
    
    assert(merge(m1, m2, m3));
    assert(m3.size() == 4);
    
    m2.insert("Lucy", 789);
    assert(merge(m1, m2, m3)); // merging with duplicates
    assert(m3.size() == 4);
    
    m2.update("Lucy", 123);
    assert(!merge(m1, m2, m3)); // merging with conlficting duplicates
    assert(m3.size() == 3);
    
    m3.insert("China", 981);
    m3.insert("Japan", 89);
    m3.insert("Ian", 17);
    m2.update("Lucy", 789);
    assert(merge(m1, m2, m3)); // merging with m3 filled
    assert(m3.size() == 4);

    cerr << "All tests passed" << endl;
}
