#ifndef PERMUTATIONSTEP_H
#define PERMUTATIONSTEP_H

class PermutationStep {
public:
    int idx;
    int arrSize;
    bool* used;
    char* permutation;
    PermutationStep(int, int, bool* = nullptr, char* = nullptr);
    PermutationStep(const PermutationStep&);
    ~PermutationStep();
    bool isFinalStep() const;
    bool operator !=(const PermutationStep&) const;

private:
    void init(int, int, bool*, char*);
};


#endif // PERMUTATIONSTEP_H
