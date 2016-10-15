#include "StringEditor.h"
#include "TextOperation.h"
StringEditor::StringEditor(std::string initial):text(initial)
{
    //ctor
}
void StringEditor::emptyRedoStack() {
    while(!redoStack.empty()) {
        redoStack.pop();
    }
}

StringEditor& StringEditor::insert(int position, std::string newText) {
    text.insert(position, newText);
    TextOperation op(INSERT_TEXT,
                                position,
                                position + newText.length(),
                                newText);
    undoStack.push(op);
    emptyRedoStack();
    return *this;
}

StringEditor& StringEditor::erase(int position, int numChars) {
    text.erase(position, numChars);
    undoStack.push(TextOperation(DELETE_TEXT,
                                 position,
                                 position + numChars,
                                 text.substr(position, numChars)));
    emptyRedoStack();
    return *this;
}

void StringEditor::applyTextOperation(const TextOperation& op) {
    if (op.type == INSERT_TEXT) {
        text.insert(op.startPos, op.diff);
    } else {
        text.erase(op.startPos, op.endPos - op.startPos);
    }
}
StringEditor& StringEditor::undo() {
    if (undoStack.empty()) {
        return *this;
    }
    TextOperation op = undoStack.top().getInverseOperation();
    applyTextOperation(op);
    redoStack.push(undoStack.top());
    undoStack.pop();

    return *this;
}

StringEditor& StringEditor::redo() {
    if (redoStack.empty()) {
        return *this;
    }
    TextOperation op = redoStack.top();
    applyTextOperation(op);
    redoStack.pop();
    return *this;
}

std::ostream& operator<<(std::ostream& out, const StringEditor& se) {
    out << se.text;
    return out;
}
