#include <iostream>
#include <vector>
#include "DeterministicAutomaton.h"
using namespace std;

int main()
{
    DeterministicAutomaton aut(0, {2});
    aut.addTransition(0, 1, 'a');
    aut.addTransition(1, 2, 'b');
    aut.addTransition(2, 1, 'a');
    aut.addTransition(0, 3, 'c');
    aut.addTransition(3, 2, 'b');
    cout << "aba: " << aut.matches("aba") << endl;
    cout << "abab: " << aut.matches("abab") << endl;
    cout << "acba: " << aut.matches("acba") << endl;
    aut.printAllWords(6);
    int wordCounter = 0;
    for(auto it = aut.begin(); it != aut.end() && wordCounter < 10; ++it) {
        cout << (++wordCounter) << ". " << *it << endl;
    }
    vector<int> a = {1,2,3,4};

    return 0;
}
