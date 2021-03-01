#ifndef QUASH_H
#define QUASH_H

#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include <cmath>

struct BigInt {
    BigInt(int i) {
        value = i;
        count = 1;
    }
    BigInt(int i, int j) {
        value = i;
        count = j;

        count = 1;
    }

    int value;
    int count;
};

struct BigIntComparator {
    bool operator() (const BigInt* a, const BigInt* b) {
        return (a->value > b->value);
    }
};

class quash {
    public:
        std::string insert(int i);
        std::string lookup(int i);
        int betterLookup(int i);
        BigInt* superLookup(int i);
        std::string deleteMin();
        std::string Delete(int i);
        void print();
        

    private:
        static const int CAP = 43;
        std::list<BigInt*> hashTable[CAP];
        std::priority_queue<BigInt*, std::vector<BigInt*>, BigIntComparator> minHeap;
        int hashFunction(int i) { return abs(i % 43); }


};




#endif