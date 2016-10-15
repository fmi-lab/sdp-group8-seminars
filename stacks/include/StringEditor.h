#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include <string>
#include <ostream>
#include <stack>
#include "TextOperation.h"
class StringEditor
{
    public:
        StringEditor(std::string);
        StringEditor& insert(int, std::string);
        StringEditor& erase(int, int);
        StringEditor& undo();
        StringEditor& redo();
        friend std::ostream& operator<<(
                    std::ostream&, const StringEditor&);
    protected:
    private:
        std::string text;
        std::stack<TextOperation> undoStack;
        std::stack<TextOperation> redoStack;
        void applyTextOperation(const TextOperation&);
        void emptyRedoStack();
};

#endif // STRINGEDITOR_H
