#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include "Taxonomy.h"
using namespace std;

void generatePermutations(char characters[], bool used[], char permutation[], int idx, int size, vector<char*>& results) {
    if (idx == size) {
        permutation[idx] = 0;
        char* result = new char[size];
        strcpy(result, permutation);
        results.push_back(result);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (used[i]) { continue; }
        permutation[idx] = characters[i];
        used[i] = true;
        generatePermutations(characters, used, permutation, idx+1, size, results);
        used[i] = false;
    }
}

vector<char*> permute(char characters[]) {
    int numChars = strlen(characters);
    bool* used = new bool[numChars];
    for (int i = 0; i < numChars; i++) {
        used[i] = false;
    }
    char* permutation = new char[numChars];
    vector<char*> results;
    generatePermutations(characters, used, permutation, 0, numChars, results);
    delete [] used;
    delete [] permutation;
    return results;
}

struct PermutationStep {
    int idx;
    int arrSize;
    bool* used;
    char* permutation;
    PermutationStep(int i, int as, bool* u = nullptr, char* perm = nullptr) {
        init(i, as, u, perm);
    }
    PermutationStep(const PermutationStep& other) {
        init(other.idx, other.arrSize, other.used, other.permutation);
    }
    void init(int i, int as, bool* u, char* perm) {
        idx = i;
        arrSize = as;
        used = new bool[arrSize];
        permutation = new char[arrSize+1];
        for (int i = 0; i < arrSize; i++) {
            if (u) {
                used[i] = u[i];
            } else {
                used[i] = false;
            }
            if (perm) {
                permutation[i] = perm[i];
            } else {
                permutation[i] = 0;
            }
        }
        permutation[arrSize] = 0;
    }

    ~PermutationStep() {
        delete [] used;
        delete [] permutation;
    }
    bool isFinalStep() const {
        return idx == arrSize;
    }
    bool operator !=(const PermutationStep& other) const{
        if (idx != other.idx || arrSize != other.arrSize) {
            return true;
        }
        // check same state
        for (int i = 0; i < arrSize; i++) {
            if (used[i] != other.used[i] || permutation[i] != other.permutation[i]) {
                return true;
            }
        }

        return false;
    }
};

vector<char*> permuteStack(char characters[]) {
    int numChars = strlen(characters);
    vector<char*> results;
    stack<PermutationStep> st;
    st.push(PermutationStep(0, numChars));
    while(!st.empty()) {
        PermutationStep current = st.top();
        st.pop();
        if (current.idx == numChars) {
            current.permutation[current.idx] = 0;
            char* result = new char[numChars+1];
            strcpy(result, current.permutation);
            results.push_back(result);
        } else {
            for (int i = 0; i < numChars; i++) {
                if (current.used[i]) {
                    continue;
                }
                current.permutation[current.idx] = characters[i];
                current.used[i] = true;
                // конструкторът на PermutationStep се грижи да изкопира текущото състояние
                // така че след st.push() можем да reset-нем каквото ни трябва
                st.push(PermutationStep(current.idx+1, numChars, current.used, current.permutation));
                current.used[i] = false;
            }
        }
    }
    return results;
}

//class PermutationIterator {
//private:
//    char* characters;
//    int arrSize;
//    stack<PermutationStep> operations;
//public:
//    PermutationIterator(char chars[]) {
//        characters = new char[strlen(chars)+1];
//        arrSize = strlen(chars);
//    }
//    PermutationIterator end() const {
//        return PermutationIterator(characters);
//    }
//
//    bool operator!=(const PermutationIterator& other) {
//        if (operations.empty()) {
//            return !other.operations.empty();
//        }
//        if (other.operations.empty()) {
//            return !operations.empty();
//        }
//        return operations.top() != other.operations.top();
//    }
//
//    char* operator *() const {
//        operations.top().permutation[operations.top().idx] = 0;
//        char* result = new char[arrSize+1];
//        strcpy(result, operations.top().permutation);
//        return result;
//    }
//    PermutationIterator& operator++() {
//
//        while (!operations.empty() && !operations.top().isFinalStep()) {
//            operations.pop();
//        }
//                 else {
//                    for (int i = 0; i < numChars; i++) {
//                        if (current.used[i]) {
//                            continue;
//                        }
//                        current.permutation[current.idx] = characters[i];
//                        current.used[i] = true;
//                        // конструкторът на PermutationStep се грижи да изкопира текущото състояние
//                        // така че след st.push() можем да reset-нем каквото ни трябва
//                        st.push(PermutationStep(current.idx+1, numChars, current.used, current.permutation));
//                        current.used[i] = false;
//                    }
//                }
//        }
//        return *this;
//    }
//};

int main()
{
    char chars[10];
    cin.getline(chars, 10);
    vector<char*> permutations = permuteStack(chars);
    for(vector<char*>::iterator it = permutations.begin(); it != permutations.end(); ++it) {
        cout << '"' << *it <<"\", ";
    }
    Taxonomy t;
    string orderPrimates[] = {"Chordata", "Mammalia", "Primates"};
    string speciesHuman[] = {"Chordata", "Mammalia", "Primates", "Hominidae", "Homo", "Homo sapiens"};
    string speciesGreyWolf[] = {"Chordata", "Mammalia", "Carnivora", "Canidae", "Canis", "Canis lupus"};
    string speciesCommonChimpanzee[] = {"Chordata", "Mammalia", "Primates", "Hominidae", "Pan", "Pan troglodytes"};
    string bengalTiger[] = {"Chordata", "Mammalia", "Carnivora", "Felidae", "Panthera", "P. tigris", "P. t. tigris"};
    string siberianTiger[] = {"Chordata", "Mammalia", "Carnivora", "Felidae", "Panthera", "P. tigris", "P. t. altaica"};

    t.addEntity(vector<string>(orderPrimates, orderPrimates + 3));
    t.addEntity(vector<string>(speciesHuman, speciesHuman + 6));
    t.addEntity(vector<string>(speciesGreyWolf, speciesGreyWolf + 6));
    t.addEntity(vector<string>(speciesCommonChimpanzee, speciesCommonChimpanzee + 6));
    t.addEntity(vector<string>(bengalTiger, bengalTiger + 7));
    t.addEntity(vector<string>(siberianTiger, siberianTiger + 7));
    t.printTaxonomy();

    map<string, int> counts = t.speciesPerFamily();
    cout << "Counts recursive: " << endl;
    for(map<string, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
        cout << "Family " << it->first << " has " << it->second << "species" << endl;
    }

    map<string, int> countsStack = t.speciesPerFamilyStack();
    cout << "Counts stack: " << endl;
    for(map<string, int>::iterator it = countsStack.begin(); it != countsStack.end(); ++it) {
        cout << "Family " << it->first << " has " << it->second << "species" << endl;
    }

    cout << "----------------------" << endl;
    vector<string> allSpecies = t.listSpeciesStack();
    for(vector<string>::iterator it = allSpecies.begin(); it != allSpecies.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
