#include "Minefield.h"
#include <random>
#include <algorithm>
#include <iostream>

// Constructeur de Minefield
Minefield::Minefield(int width, int height, int mines)
    : width(width), height(height), mines(mines), gameLost(false),
    revealed(width, std::vector<bool>(height, false)),
    marked(width, std::vector<bool>(height, false)),
    minefield(width, std::vector<bool>(height, false)) {
}

// Révèle une case
void Minefield::reveal(int x, int y) {
    if (!isValidCoord(x, y) || revealed[x][y] || marked[x][y]) return;

    // Génère les mines si ce n'est pas déjà fait
    if (!std::any_of(minefield.begin(), minefield.end(), [](const std::vector<bool>& row) { return std::any_of(row.begin(), row.end(), [](bool mine) { return mine; }); })) {
        generateMines(x, y);
    }
    if (minefield[x][y]) {
        gameLost = true;
    } else {
        floodFill(x, y);
    }
}

// Marque une case
void Minefield::mark(int x, int y) {
    if (isValidCoord(x, y) && !revealed[x][y]) {
        marked[x][y] = true;
    }
}

// Démarque une case
void Minefield::unmark(int x, int y) {
    if (isValidCoord(x, y)) {
        marked[x][y] = false;
    }
}

// Vérifie si une case est révélée
bool Minefield::isRevealed(int x, int y) const {
    return isValidCoord(x, y) && revealed[x][y];
}

// Vérifie si une case est marquée
bool Minefield::isMarked(int x, int y) const {
    return isValidCoord(x, y) && marked[x][y];
}

// Vérifie si une case contient une mine
bool Minefield::hasMine(int x, int y) const {
    return isValidCoord(x, y) && minefield[x][y];
}

// Compte le nombre de mines voisines d'une case
int Minefield::getNeighboringMines(int x, int y) const {
    if (!isValidCoord(x, y)) return -1;
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (isValidCoord(x + i, y + j) && minefield[x + i][y + j]) {
                ++count;
            }
        }
    }
    return count;
}

// Vérifie si le jeu est perdu
bool Minefield::isGameLost() const {
    return gameLost;
}

// Vérifie si le jeu est gagné
bool Minefield::isGameWon() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!minefield[x][y] && !revealed[x][y]) {
                return false;
            }
        }
    }
    return true;
}

// Génère les mines en évitant la première case révélée
void Minefield::generateMines(int firstX, int firstY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, width - 1);
    std::uniform_int_distribution<> disY(0, height - 1);

    int placedMines = 0;
    while (placedMines < mines) {
        int x = disX(gen);
        int y = disY(gen);
        if ((x != firstX || y != firstY) && !minefield[x][y]) {
            minefield[x][y] = true;
            ++placedMines;
        }
    }
}

// Révèle les cases voisines tant qu'elles n'ont pas de mines voisines
void Minefield::floodFill(int x, int y) {
    if (!isValidCoord(x, y) || revealed[x][y]) return;
    revealed[x][y] = true;
    if (getNeighboringMines(x, y) == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0) {
                    floodFill(x + i, y + j);
                }
            }
        }
    }
}

// Vérifie si les coordonnées sont valides
bool Minefield::isValidCoord(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}
