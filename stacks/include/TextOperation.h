#ifndef TEXTOPERATION_H
#define TEXTOPERATION_H
#include <string>
enum OperationType {
    INSERT_TEXT,
    DELETE_TEXT
};

struct TextOperation
{
public:
    OperationType type;
    int startPos;
    int endPos;
    std::string diff;
    TextOperation(OperationType, int, int, std::string);
    TextOperation getInverseOperation() const;
};

#endif // TEXTOPERATION_H
