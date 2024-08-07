#include "GameController.h"
#include <iostream>
#include <limits>

GameController::GameController(Minefield& minefield, ConsoleView& view)
    : minefield(minefield), view(view) {}

void GameController::run(std::istream& input) {
    while (!minefield.isGameLost() && !minefield.isGameWon()) {
        view.display();
        char action;
        int x, y;
        std::cout << "Enter action (r=reveal, m=mark, u=unmark) and coordinates (x y): ";
        input >> action >> x >> y;

        // Vérifiez si l'entrée est valide
        if (input.fail() || (action != 'r' && action != 'm' && action != 'u')) {
            input.clear(); // réinitialiser les flags d'erreur de std::cin
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vider la ligne de l'entrée invalide
            std::cout << "Invalid input. Please enter a valid action and coordinates.\n";
            continue; // recommence la boucle
        }

        // Vérifiez si les coordonnées sont dans la plage valide
        if (x < 0 || x >= minefield.getWidth() || y < 0 || y >= minefield.getHeight()) {
            std::cout << "Coordinates out of bounds. Please enter valid coordinates.\n";
            continue;
        }

        processInput(action, x, y);

        if (minefield.isGameLost()) {
            view.displayGameOver();
        } else if (minefield.isGameWon()) {
            view.displayWin();
        }
    }
}

void GameController::processInput(char action, int x, int y) {
    if (action == 'r') {
        minefield.reveal(x, y);
    } else if (action == 'm') {
        minefield.mark(x, y);
    } else if (action == 'u') {
        minefield.unmark(x, y);
    }
}
