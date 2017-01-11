#include "DeterministicAutomaton.h"
#include <iostream>
#include <set>
#include <string>
#include <assert.h>
DeterministicAutomaton::DeterministicAutomaton(int initialState, std::set<int> finalStates)
    :initialState(initialState),finalStates(finalStates) {
    // set all transitions to -1 (i.e. no transition)
    for (int stateIdx=0; stateIdx < MAX_STATES; stateIdx++) {
        for (int label = 0; label < 26; label++) {
            transitions[stateIdx][label] = -1;
        }
    }
}

void DeterministicAutomaton::addTransition(int from, int to, char label) {
    // assert there is no transition with that label
    assert(transitions[from][label] == -1);
    transitions[from][label-'a'] = to;
}

bool DeterministicAutomaton::matches(std::string str) const {
    int currentState = initialState, strIndex = 0;
    while(currentState != -1 && strIndex < str.length()) {
        currentState = transitions[currentState][str[strIndex]-'a'];
        strIndex++;
    }
    return isFinal(currentState);
}

bool DeterministicAutomaton::isFinal(int state) const {
    return finalStates.find(state) != finalStates.end();
}

void DeterministicAutomaton::printAllWords(int maxDepth) const {
    printWords(initialState, "", 0, maxDepth);
}

void DeterministicAutomaton::printWords(int state, std::string currentWord, int currentDepth, int maxDepth) const {
    if (state == -1 || (maxDepth !=0 && currentDepth > maxDepth)) {
        return;
    }

    if (isFinal(state)) {
        std::cout << currentWord << std::endl;
    }
    for (int label = 0; label < 26; label++) {
        printWords(transitions[state][label], currentWord + (char)('a' + label), currentDepth+1, maxDepth);
    }
}

DeterministicAutomaton::Iterator DeterministicAutomaton::begin() const {
    return Iterator(this);
}

DeterministicAutomaton::Iterator DeterministicAutomaton::end() const {
    return Iterator(this, true);
}

bool DeterministicAutomaton::Iterator::isComplete(const IteratorStep& step) const {
    return autref->isFinal(step.state);
}

void DeterministicAutomaton::Iterator::unwind() {
    while (!operations.empty() && !isComplete(operations.front())) {
        IteratorStep op = operations.front();
        operations.pop();
        expandState(op);
    }
}

std::string DeterministicAutomaton::Iterator::operator*() const {
    assert(!operations.empty() && isComplete(operations.front()));
    return operations.front().word;
}

bool DeterministicAutomaton::Iterator::operator !=(const Iterator& other) const {
    assert(autref == other.autref);
    if (operations.empty() && other.operations.empty()) {
        return false;
    }
    if ((operations.empty() && !other.operations.empty()) ||
        (!operations.empty() && other.operations.empty())) {
        return true;
    }
    return operations.front() != other.operations.front();
}

void DeterministicAutomaton::Iterator::expandState(const IteratorStep& step) {
    for (int label = 0; label < 26; label++) {
        int nextState = autref->transitions[step.state][label];
        if (nextState != -1) {
            operations.push(IteratorStep(nextState, step.word + (char)(label+'a')));
        }
    }
}
DeterministicAutomaton::Iterator& DeterministicAutomaton::Iterator::operator++() {
    assert(!operations.empty());
    IteratorStep currentTop = operations.front();
    operations.pop();
    expandState(currentTop);
    unwind();
    return *this;
}

DeterministicAutomaton::Iterator::Iterator(const DeterministicAutomaton* autref, bool end):autref(autref) {
    if (!end) {
        operations.push(IteratorStep(autref->initialState, ""));
        unwind();
    }
}

