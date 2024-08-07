#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../model/Minefield.h"
#include "../view/ConsoleView.h"
#include <istream>

class GameController {
public:
    GameController(Minefield& minefield, ConsoleView& view);
    void run(std::istream& input); // Modification ici

private:
    Minefield& minefield;
    ConsoleView& view;
    void processInput(char action, int x, int y);
};

#endif // GAMECONTROLLER_H
