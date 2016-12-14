#include "Taxonomy.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

using ChildIterator = std::vector<Taxonomy::TNode*>::iterator;

Taxonomy::Taxonomy() {
    // always start with the Animal Kingdom
    root = new TNode("Animalia");
}

void Taxonomy::deleteNode(TNode* node) {
    for(ChildIterator it = node->children.begin(); it != node->children.end(); ++it) {
        deleteNode(*it);
    }
    delete node;
}
Taxonomy::~Taxonomy()
{
    deleteNode(root);
}

void Taxonomy::printTaxonomy() const {
    std::vector<std::string> currentPath;
    printTaxonomyRec(root, currentPath);
}

void Taxonomy::printTaxonomyRec(TNode* node, std::vector<std::string>& path) const {
    path.push_back(node->name);
    if (node->children.size() == 0) {
            // leaf node - print it
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i] << "->";
        }
        std::cout << " (Level " << node->level << ")" << std::endl;
    }
    for (ChildIterator it = node->children.begin(); it != node->children.end(); ++it) {
        printTaxonomyRec(*it, path);
    }
    path.pop_back();
}

// taxonomy contains e.g. <"Chordata", "Mammalia", "Primates", "Hominidae", "Homo", "Homo sapiens">
void Taxonomy::addEntity(std::vector<std::string> taxonomy) {
    TNode* current = root;
    for (std::vector<std::string>::iterator it = taxonomy.begin(); it != taxonomy.end(); ++it) {
        TNode* existing = current->findChild(*it);
        if (!existing) {
            existing = current->addChild(*it);
        }
        current = existing;
    }
}

int Taxonomy::countSpeciesInFamily(std::string family) const {
    // species are always at level 6; families are at level 4
    return 0;
}

void Taxonomy::speciesPerFamily(TNode* node, std::string familyName, std::map<std::string, int>& result) const {
    if (node->level == 4) {
        // only set the family name if the node is at the proper level
        familyName = node->name;
    }

    if (node->level >= 6 && node->children.size() == 0) {
        // add it to the current family name's count only if it is a leaf node
        // accessing result[familyName] before it is initialized will default-init it
        result[familyName] = result[familyName] + 1;
    }
    // recurse deeper
    for(ChildIterator it = node->children.begin(); it != node->children.end(); ++it) {
        speciesPerFamily(*it, familyName, result);
    }

}

std::map<std::string, int> Taxonomy::speciesPerFamily() const {
    std::map<std::string, int> result;
    speciesPerFamily(root, "", result);
    return result;
}

struct CounterState {
    Taxonomy::TNode* node;
    std::string familyName;
    CounterState(Taxonomy::TNode* node, std::string name): node(node), familyName(name) {};
};
std::map<std::string, int> Taxonomy::speciesPerFamilyStack() const {
    std::map<std::string, int> result;
    std::stack<CounterState> st;
    st.push(CounterState(root, ""));
    while(!st.empty()) {
        CounterState current = st.top();
        st.pop();
        if (current.node->level >= 6 && current.node->children.size() == 0) {
            // count it towards the current family name
            result[current.familyName] = result[current.familyName] + 1;
        }

        std::string nextFamilyName = current.familyName;
        if (current.node->level == 4) {
            // add new steps for children with that family's name
            nextFamilyName = current.node->name;
        }
        for (ChildIterator it = current.node->children.begin(); it != current.node->children.end(); ++it) {
            st.push(CounterState(*it, nextFamilyName));
        }
    }
    return result;
}

bool isSpeciesLeaf(Taxonomy::TNode* node) {
    return node->children.empty() && node->level >= 6;
}
void Taxonomy::listSpeciesRec(TNode* node, std::vector<std::string>& res) const {
    if (isSpeciesLeaf(node)) {
        res.push_back(node->name);
    } else {
        for (ChildIterator it = node->children.begin(); it != node->children.end(); ++it) {
            listSpeciesRec(*it, res);
        }
    }
}

std::vector<std::string> Taxonomy::listSpecies() const {
    std::vector<std::string> result;
    listSpeciesRec(root, result);
    return result;
}

std::vector<std::string> Taxonomy::listSpeciesStack() const {
    std::vector<std::string> result;
    // Всеки елемент на стека се състои от параметрите, с които се вика рекурсивният еквивалент
    std::stack<TNode*> operations;
    operations.push(root);
    while(!operations.empty()) {
        TNode* top = operations.top();
        operations.pop();
        // top операцията е еквивалентна на едно рекурсивно извикване със съответните параметри
        // но вместо рекурсивните извиквания, имаме push в стека
        if (isSpeciesLeaf(top)) {
            result.push_back(top->name);
        } else {
            for (ChildIterator it = top->children.begin(); it != top->children.end(); ++it) {
                operations.push(*it);
            }
        }
    }
    return result;
}
