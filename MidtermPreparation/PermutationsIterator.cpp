#include "PermutationsIterator.h"
#include "PermutationStep.h"
#include <cstring>
#include <string>
#include <assert.h>

PermutationsIterator::PermutationsIterator(char chars[])
{
    len = strlen(chars);
    characters = new char[len+1];
    strcpy(characters, chars);
    // automatically initiate it
    operations.push(PermutationStep(0, len));
    // make sure the top of the stack is the first available permutation
    unwind();
}

PermutationsIterator::~PermutationsIterator() {
    delete [] characters;
}

bool PermutationsIterator::hasNext() const {
    return !operations.empty();
}

void PermutationsIterator::unwind() {
    // Стремим се винаги на върха на стека да е такова състояние, което съдържа пълна (готова) пермутация
    // т.е. докато на върха на стека е незавършена пермутация, махаме я от стека и я "разпъваме",
    // т.е. запълваме следващата ѝ позиция и вкарваме в стека нови състояния с "по-запълнени" пермутации
    while(!operations.empty() && !operations.top().isFinalStep()) {
        PermutationStep top = operations.top();
        operations.pop();
        // apply step
        for (int i = 0; i < len; i++) {
            if (top.used[i]) {
                continue;
            }
            top.permutation[top.idx] = characters[i];
            top.used[i] = true;
            // конструкторът на PermutationStep се грижи да изкопира текущото състояние
            // така че след st.push() можем да reset-нем каквото ни трябва
            operations.push(PermutationStep(top.idx+1, len, top.used, top.permutation));
            top.used[i] = false;
        }
    }
}

std::string PermutationsIterator::operator*() const {
    assert(!operations.empty());
    // с unwind сме си осигурили, че на върха на стека винаги се съдържа завършена пермутация
    // така че можем спокойно директно да си я връщаме
    return std::string(operations.top().permutation);
}

PermutationsIterator& PermutationsIterator::operator++() {
    assert(!operations.empty());
    // на върха на стека досега е имало завършена пермутация
    // махаме я и след това пускаме unwind, което ще намери следващата завършена пермутация
    // или ще доизпразни стека, ако текущата пермутация е била последната възможна
    operations.pop();
    unwind();
    return *this;
}
