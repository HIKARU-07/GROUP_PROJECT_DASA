#include "../src/services/UndoService.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    UndoService service;

    service.loadInput("C:/Users/PHAM HONG TIEN MINH/GitHub/GROUP_PROJECT_DASA/data/UndoInput.txt");

    int Q;

    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        string command;

        cin >> command;


        if (command == "UNDO")
        {
            service.undo();
        }
    }
    service.printStack();

    return 0;
}