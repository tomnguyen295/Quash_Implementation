#include "quash.h"
#include <bits/stdc++.h>

using namespace std;

BigInt* quash::superLookup(int i) {
    int index = 0;
    for (list<BigInt*>::iterator j = hashTable[hashFunction(i)].begin(); j != hashTable[hashFunction(i)].end(); j++) {
        int check = (*j)->value;
        if (check == i) {
            return *j;
        }
        index++;
    }
    return nullptr;
}


string quash::lookup(int i) {
    string success = "item found, count = ";
    string fail = "item not found";
    if (hashTable[hashFunction(i)].size() == 0) {
        return fail;
    }
    for (list<BigInt*>::const_iterator j = hashTable[hashFunction(i)].begin(); j != hashTable[hashFunction(i)].end(); j++) {
        int check = (*j)->value;
        if (check == i) {
            return success + to_string((*j)->count);
        }
    }
    return fail;
}

string quash::insert(int i) {
    string success = "item successfully inserted, count = ";
    string fail = "item already present, count = ";


    BigInt* myInt = new BigInt(i);
    BigInt* heapInt = myInt;
    
    if (!superLookup(i)) {
        hashTable[hashFunction(i)].push_front(myInt);
        minHeap.push(heapInt);

        return success + to_string(myInt->count);
    }

    else {
        superLookup(i)->count += 1;
        return success + to_string(superLookup(i)->count);
    }
    return "";



}

string quash::deleteMin() {
    string prompt1 = "min item ";
    string prompt1_1 = " successfully deleted";
    string prompt2 = "min item = ";
    string prompt2_1 = ", count decremented, new count = ";
    string fail = "min item not present since table is empty";

    if (minHeap.empty()) {
        return fail;
    }
        

    while ((minHeap.top())->count == 0) {
        minHeap.pop();
    }



    int value = (minHeap.top())->value;
    BigInt* myIndex = superLookup(value);
    if (myIndex->count == 1) {
        hashTable[hashFunction(value)].remove(myIndex);
        minHeap.pop();
        return prompt1 + to_string(value) + prompt1_1;
    } else {
        myIndex->count -= 1;
        return prompt2 + to_string(value) + prompt2_1 + to_string(myIndex->count);
    }
}

string quash::Delete(int i) {
    string prompt1 = "item";
    string prompt1_1 = " successfully deleted";
    string prompt2 = "item";
    string prompt2_1 = " count decremented, new count = ";
    string fail = "item not present in the table";

    if (!superLookup(i)) {
        return fail;
    }


    int value = i;
    BigInt* myIndex = superLookup(value);
    if (myIndex->count == 1) {
        hashTable[hashFunction(value)].remove(myIndex);
        myIndex->count -= 1;
        return prompt1 + prompt1_1;
    } else {
        myIndex->count -= 1;
        return prompt2 + prompt2_1 + to_string(myIndex->count);
    }

}

void quash::print() {
    for (int i = 0; i < CAP; i++) {
        for (list<BigInt*>::const_iterator j = hashTable[i].begin(); j != hashTable[i].end(); j++) {
            cout << (*j) -> value <<  " ";
        }
    }
    cout << endl;

}

int main(int argc, char* argv[]) {
    quash myQuash;
    vector<string> listOfCommands;
    string arg(argv[1]);
    stringstream check1(arg);
    string intermediate;
    int counter = 0;
    while (getline(check1, intermediate, ',')) {
        if (counter != 0) {
            intermediate = intermediate.erase(0,1);
        }
        listOfCommands.push_back(intermediate);
        counter++;
    }
    for (int i = 0; i < listOfCommands.size(); i++) {
        if (listOfCommands[i] == "print") {
            myQuash.print();
        } else if (listOfCommands[i] == "deleteMin") {
            cout << myQuash.deleteMin() << endl;
        } else {
            vector<string> thisCommand;
            stringstream check2(listOfCommands[i]);
            string intermediate2;
            while (getline(check2, intermediate2, ' ')) {
                thisCommand.push_back(intermediate2);
            }
            if (thisCommand[0] == "insert") {
                cout << myQuash.insert(stoi(thisCommand[1])) << endl;
            } else if (thisCommand[0] == "lookup") {
                cout << myQuash.lookup(stoi(thisCommand[1])) << endl;
            } else {
                cout << myQuash.Delete(stoi(thisCommand[1])) << endl;
            }
        }
    }

} 





