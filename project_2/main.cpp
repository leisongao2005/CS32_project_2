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

int main() {
    Map msd;  // KeyType is std::string, ValueType is double
    msd.insert("ccc", 80);
    msd.dump();
    msd.insert("aaa", 40);
    msd.dump();
    msd.insert("ddd", 60);
    msd.dump();
    msd.insert("bbb", 20);
    msd.dump();
    KeyType k = "xxx";
    ValueType v;
    assert(!msd.get(4, k, v)  &&  k == "xxx");  // k and v unchanged
    assert(msd.get(1, k, v)  &&  k == "bbb");   // "bbb" is greater than
                                                        // exactly 1 item
}
