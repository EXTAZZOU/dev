#include "ConsoleView.h"
#include <iostream>

ConsoleView::ConsoleView(Minefield& minefield) : minefield(minefield) {}

void ConsoleView::display() {
    for (int y = 0; y < minefield.getHeight(); ++y) {
        for (int x = 0; x < minefield.getWidth(); ++x) {
            if (minefield.isRevealed(x, y)) {
                if (minefield.hasMine(x, y)) {
                    std::cout << "* ";
                } else {
                    int mines = minefield.getNeighboringMines(x, y);
                    if (mines > 0) {
                        std::cout << mines << " ";
                    } else {
                        std::cout << ". ";
                    }
                }
            } else if (minefield.isMarked(x, y)) {
                std::cout << "M ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << "\n";
    }
}

void ConsoleView::displayGameOver() {
    std::cout << "Game Over! You hit a mine.\n";
    display();
}

void ConsoleView::displayWin() {
    std::cout << "Congratulations! You won.\n";
    display();
}
