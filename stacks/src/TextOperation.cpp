#include "TextOperation.h"

TextOperation::TextOperation(OperationType type, int start, int end, std::string diff)
   :type(type), startPos(start), endPos(end), diff(diff)
{
    //ctor
}

TextOperation TextOperation::getInverseOperation() const {
    return TextOperation(
       type == INSERT_TEXT?
            DELETE_TEXT: INSERT_TEXT,
       startPos,
       endPos,
       diff);
}
