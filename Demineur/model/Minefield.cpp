#include "Minefield.h"
#include <random>
#include <algorithm>
#include <iostream>

Minefield::Minefield(int width, int height, int mines)
    : width(width), height(height), mines(mines), gameLost(false),
      revealed(width, std::vector<bool>(height, false)),
      marked(width, std::vector<bool>(height, false)),
      minefield(width, std::vector<bool>(height, false)) {
}

void Minefield::reveal(int x, int y) {
    if (!isValidCoord(x, y) || revealed[x][y] || marked[x][y]) return;
    if (!std::any_of(minefield.begin(), minefield.end(), [](const std::vector<bool>& row) { return std::any_of(row.begin(), row.end(), [](bool mine) { return mine; }); })) {
        generateMines(x, y);
    }
    if (minefield[x][y]) {
        gameLost = true;
    } else {
        floodFill(x, y);
    }
}

void Minefield::mark(int x, int y) {
    if (isValidCoord(x, y) && !revealed[x][y]) {
        marked[x][y] = true;
    }
}

void Minefield::unmark(int x, int y) {
    if (isValidCoord(x, y)) {
        marked[x][y] = false;
    }
}

bool Minefield::isRevealed(int x, int y) const {
    return isValidCoord(x, y) && revealed[x][y];
}

bool Minefield::isMarked(int x, int y) const {
    return isValidCoord(x, y) && marked[x][y];
}

bool Minefield::hasMine(int x, int y) const {
    return isValidCoord(x, y) && minefield[x][y];
}

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

bool Minefield::isGameLost() const {
    return gameLost;
}

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
            std::cout << " coordonées de la bombe x: " << x << " et y: " << y << "\n";
        }
    }
}

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

bool Minefield::isValidCoord(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}
