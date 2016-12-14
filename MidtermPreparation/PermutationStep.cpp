#include "PermutationStep.h"

PermutationStep::PermutationStep(int i, int as, bool* u, char* perm) {
    init(i, as, u, perm);
}

PermutationStep::PermutationStep(const PermutationStep& other) {
    init(other.idx, other.arrSize, other.used, other.permutation);
}

void PermutationStep::init(int i, int as, bool* u, char* perm) {
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

PermutationStep::~PermutationStep() {
    delete [] used;
    delete [] permutation;
}

bool PermutationStep::isFinalStep() const {
    return idx == arrSize;
}

bool PermutationStep::operator!=(const PermutationStep& other) const {
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
