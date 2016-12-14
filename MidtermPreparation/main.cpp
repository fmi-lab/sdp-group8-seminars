#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include "Taxonomy.h"
#include "PermutationStep.h"
#include "PermutationsIterator.h"

using namespace std;

void generatePermutationsRec(char characters[], int size, vector<char*>& results,
                             bool used[], char permutation[], int idx) {
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
        generatePermutationsRec(characters, size, results, used, permutation, idx+1);
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
    generatePermutationsRec(characters, numChars, results, used, permutation, 0);
    delete [] used;
    delete [] permutation;
    return results;
}

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

int main()
{
    cout << "Permutations with stack" << endl;
    char chars[10];
    cin.getline(chars, 10);
    vector<char*> permutations = permuteStack(chars);
    for(vector<char*>::iterator it = permutations.begin(); it != permutations.end(); ++it) {
        cout << *it << endl;
    }
    cout << "--------------------------------" << endl;
    cout << "Taxonomy tests" << endl;
    cout << "--------------------------------" << endl;
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

    cout << "Listing all species: " << endl;
    vector<string> allSpecies = t.listSpeciesStack();
    for(vector<string>::iterator it = allSpecies.begin(); it != allSpecies.end(); ++it) {
        cout << *it << endl;
    }
    cout << endl << endl << "--------------------------------" << endl;
    cout << "Permutations Iterator" << endl;
    cout << "--------------------------------" << endl;
    for(PermutationsIterator pi("123"); pi.hasNext(); ++pi) {
        cout << *pi << endl;
    }
    return 0;
}
