#ifndef TAXONOMY_H
#define TAXONOMY_H

#include <string>
#include <vector>
#include <map>
class Taxonomy
{
    public:
        struct TNode {
            std::string name;
            int level;
            std::vector<TNode*> children;
            TNode(std::string name, int level = 0):name(name), level(level) { }
            TNode* findChild(std::string childName) {
                for (std::vector<TNode*>::iterator it = children.begin(); it != children.end(); ++it) {
                    if ((*it)->name == childName) {
                        return *it;
                    }
                }
                return NULL;
            }
            TNode* addChild(std::string childName) {
                TNode* child = new TNode(childName, level+1);
                children.push_back(child);
                return child;
            }
        };
        Taxonomy();
        ~Taxonomy();
        void addEntity(std::vector<std::string> taxonomy);
        int countSpeciesInFamily(std::string family) const;
        std::map<std::string, int> speciesPerFamily() const;
        std::map<std::string, int> speciesPerFamilyStack() const;
        std::vector<std::string> listSpecies() const;
        std::vector<std::string> listSpeciesStack() const;
        void printTaxonomy() const;
    protected:
    private:
        TNode* root;
        void deleteNode(TNode* node);
        void printTaxonomyRec(TNode*, std::vector<std::string>&) const;
        void speciesPerFamily(TNode*, std::string, std::map<std::string, int>&) const;
        void listSpeciesRec(TNode*, std::vector<std::string>&) const;
};

#endif // TAXONOMY_H
