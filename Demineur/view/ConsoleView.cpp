#include "ConsoleView.h"
#include <iostream>

// Constructeur de ConsoleView
ConsoleView::ConsoleView(Minefield& minefield) : minefield(minefield) {}

// Affiche l'état actuel du champ de mines
void ConsoleView::display() {
    for (int y = 0; y < minefield.getHeight(); ++y) {
        for (int x = 0; x < minefield.getWidth(); ++x) {
            if (minefield.isRevealed(x, y)) {
                if (minefield.hasMine(x, y)) {
                    std::cout << "* ";  // Affiche une mine
                } else {
                    int mines = minefield.getNeighboringMines(x, y);
                    if (mines > 0) {
                        std::cout << mines << " ";  // Affiche le nombre de mines adjacentes
                    } else {
                        std::cout << ". ";  // Affiche une case vide
                    }
                }
            } else if (minefield.isMarked(x, y)) {
                std::cout << "M ";  // Affiche un marqueur
            } else {
                std::cout << "# ";  // Affiche une case non révélée
            }
        }
        std::cout << "\n";  // Nouvelle ligne après chaque rangée
    }
}

// Affiche le message de défaite et l'état du champ de mines
void ConsoleView::displayGameOver() {
    std::cout << "Game Over! Vous avez perdu.\n";
    display();
}

// Affiche le message de victoire et l'état du champ de mines
void ConsoleView::displayWin() {
    std::cout << "Bravo! Vous avez gagné.\n";
    display();
}
