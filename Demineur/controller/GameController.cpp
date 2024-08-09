#include "GameController.h"
#include <iostream>
#include <limits>

// Constructeur de GameController
GameController::GameController(Minefield& minefield, ConsoleView& view)
    : minefield(minefield), view(view) {}

// Boucle principale du jeu
void GameController::run(std::istream& input) {
    while (!minefield.isGameLost() && !minefield.isGameWon()) {
        view.display();
        char action;
        int x, y;
        std::cout << "Enter action (r=reveal, m=mark, u=unmark) and coordinates (x y): ";
        input >> action >> x >> y;

        // Validation de l'entrée utilisateur
        if (input.fail() || (action != 'r' && action != 'm' && action != 'u')) {
            input.clear(); // Réinitialiser les flags d'erreur de std::cin
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer l'entrée incorrecte
            std::cout << "Invalid input. Please enter a valid action and coordinates.\n";
            continue; // Recommencer la boucle
        }

        // Validation des coordonnées
        if (x < 0 || x >= minefield.getWidth() || y < 0 || y >= minefield.getHeight()) {
            std::cout << "Coordinates out of bounds. Please enter valid coordinates.\n";
            continue; // Recommencer la boucle
        }

        processInput(action, x, y);

        if (minefield.isGameLost()) {
            view.displayGameOver();
        } else if (minefield.isGameWon()) {
            view.displayWin();
        }
    }
}

// Gère les actions de l'utilisateur
void GameController::processInput(char action, int x, int y) {
    if (action == 'r') {
        minefield.reveal(x, y);
    } else if (action == 'm') {
        minefield.mark(x, y);
    } else if (action == 'u') {
        minefield.unmark(x, y);
    }
}
