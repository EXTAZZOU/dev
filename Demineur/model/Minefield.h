#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <vector>

class Minefield {
public:
    Minefield(int width, int height, int mines);
    void reveal(int x, int y);
    void mark(int x, int y);
    void unmark(int x, int y);
    bool isRevealed(int x, int y) const;
    bool isMarked(int x, int y) const;
    bool hasMine(int x, int y) const;
    int getNeighboringMines(int x, int y) const;
    bool isGameLost() const;
    bool isGameWon() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height, mines;
    bool gameLost;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> marked;
    std::vector<std::vector<bool>> minefield;

    void generateMines(int firstX, int firstY);
    void floodFill(int x, int y);
    bool isValidCoord(int x, int y) const;
};

#endif // MINEFIELD_H
