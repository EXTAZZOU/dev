#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../model/Minefield.h"

class ConsoleView {
public:
    ConsoleView(Minefield& minefield);
    void display();
    void displayGameOver();
    void displayWin();

private:
    Minefield& minefield;
};

#endif // CONSOLEVIEW_H
