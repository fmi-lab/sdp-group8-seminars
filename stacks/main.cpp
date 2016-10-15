#include <iostream>
#include "StringEditor.h"
using namespace std;

int main()
{
    StringEditor se("");
    se.insert(0, "I am in FHF.");
    cout << se << endl;
    se.erase(8, 3);
    se.insert(8, "F")
      .insert(9, "M")
      .insert(10, "I");
    cout << se << endl;
    se.undo().undo().undo().undo();
    cout << se << endl;
    se.redo().redo();
    cout << se << endl;
    return 0;
}
