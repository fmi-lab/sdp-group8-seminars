#ifndef DETERMINISTICAUTOMATON_H
#define DETERMINISTICAUTOMATON_H

#include <set>
#include <string>
#include <stack>
#include <queue>
#include <assert.h>

const int MAX_STATES = 1000;
class DeterministicAutomaton
{
    class Iterator {
        struct IteratorStep {
            int state;
            std::string word;
            IteratorStep(int state, std::string word): state(state), word(word) {}

            bool operator !=(const IteratorStep& other) const {
                return state != other.state || word != other.word;
            }
        };

        public:
            Iterator(const DeterministicAutomaton*, bool=false);
            Iterator& operator++();
            bool operator !=(const Iterator&) const;
            std::string operator*() const;

        private:
            const DeterministicAutomaton* autref;
            std::queue<IteratorStep> operations;
            bool isComplete(const IteratorStep&) const;
            void unwind();
            void expandState(const IteratorStep&);
    };

    public:
        DeterministicAutomaton(int initialState=0, std::set<int> finalStates={});
        void addTransition(int from, int to, char label);
        bool matches(std::string) const;
        void printAllWords(int maxDepth=0) const;
        Iterator begin() const;
        Iterator end() const;
    protected:
    private:
        int initialState;
        std::set<int> finalStates;
        int transitions[MAX_STATES][26];
        bool isFinal(int) const;
        void printWords(int, std::string, int, int) const;
};

#endif // DETERMINISTICAUTOMATON_H
