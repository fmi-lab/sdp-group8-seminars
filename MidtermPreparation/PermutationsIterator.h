#ifndef PERMUTATIONSITERATOR_H
#define PERMUTATIONSITERATOR_H

#include <stack>
#include <string>
#include "PermutationStep.h"

class PermutationsIterator
{
    public:
        PermutationsIterator(char[]);
        ~PermutationsIterator();
        bool hasNext() const;
        PermutationsIterator& operator++();
        std::string operator*() const;
    protected:
    private:
        char* characters;
        int len;
        std::stack<PermutationStep> operations;
        void unwind();
};

#endif // PERMUTATIONSITERATOR_H
