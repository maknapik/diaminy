#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAX_ATTEMPTS = 120;
bool solved = false;

class Game {

private:
    int width;
    int height;
    int maxSteps;
    int playerX;
    int playerY;
    int points;
    int currentPoints = 0;
    string mapa;

public:
    static const int DIRECTION_COUNT = 7;

    void setWidth(int width) {
        Game::width = width;
    }

    void setHeight(int height) {
        Game::height = height;
    }

    void setMaxSteps(int maxSteps) {
        Game::maxSteps = maxSteps;
    }

    int getMaxSteps() {
        return maxSteps;
    }

    int getPoints() const {
        return points;
    }

    int getCurrentPoints() const {
        return currentPoints;
    }

    char getFromMap(int x, int y) {
        return mapa[y * width + x];
    }

    void setInMap(int x, int y, char c) {
        mapa[y * width + x] = c;
    }

    void createMap(string input) {
        mapa = input;
    }

    void printMap() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << getFromMap(j, i);
            }
            cout << endl;
        }
    }

    void printPlayerPosition() {
        cout << playerX << " " << playerY << endl;
    }

    void countPoints() {
        points = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (getFromMap(j, i) == '+') {
                    points++;
                }
            }
        }
    }

    void getPlayerPosition() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (getFromMap(j, i) == '.') {
                    playerY = i;
                    playerX = j;
                    setInMap(j, i, 'O');
                }
            }
        }
    }

private:
    bool canMoveAtPosition(int x, int y) {
        return getFromMap(x, y) != '*';
    }

    bool isWall(int x, int y) {
        return getFromMap(x, y) == '#';
    }

    void collectGem(int x, int y) {
        if (isGem(x, y)) {
            currentPoints++;
            setInMap(x, y, ' ');
        }
    }

    bool isGem(int x, int y) {
        return getFromMap(x, y) == '+';
    }

    bool isHole(int x, int y) {
        return getFromMap(x, y) == 'O';
    }

    double countDistance(int x, int y) {
        return sqrt((playerX - x) * (playerX - x) + (playerY - y) * (playerY - y));
    }

    // zwraca kierunek obliczany na podstawie aktualnej pozycji gracza i podanych wspolrzednych
    int getDirection(int x, int y) {
        if (playerX == x) {
            if (playerY < y) {
                return 4;
            } else {
                return 0;
            }
        } else if (playerY == y) {
            if (playerX < x) {
                return 2;
            } else {
                return 6;
            }
        } else if (playerX < x) {
            if (playerY < y) {
                return 3;
            } else {
                return 1;
            }
        } else if (playerX > x) {
            if (playerY < y) {
                return 5;
            } else {
                return 7;
            }
        }
    }

public:
    // zwraca true, jesli gracz moze przemiescic sie w danym kierunku i nie napotka miny
    bool canMove(int direction) {
        bool canMove = true;

        int x = playerX, y = playerY;

        switch (direction) {
            case 0:
                if (isWall(x, y - 1)) {
                    return false;
                }
                while (y > 0) {
                    y--;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 1:
                if (isWall(x + 1, y - 1)) {
                    return false;
                }
                while (y > 0 && x < width) {
                    y--;
                    x++;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 2:
                if (isWall(x + 1, y)) {
                    return false;
                }
                while (x < width) {
                    x++;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 3:
                if (isWall(x + 1, y + 1)) {
                    return false;
                }
                while (y < height && x < width) {
                    y++;
                    x++;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 4:
                if (isWall(x, y + 1)) {
                    return false;
                }
                while (y < height) {
                    y++;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 5:
                if (isWall(x - 1, y + 1)) {
                    return false;
                }
                while (y < height && x > 0) {
                    y++;
                    x--;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 6:
                if (isWall(x - 1, y)) {
                    return false;
                }
                while (x > 0) {
                    x--;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            case 7:
                if (isWall(x - 1, y - 1)) {
                    return false;
                }
                while (y > 0 && x > 0) {
                    y--;
                    x--;
                    if (!canMoveAtPosition(x, y)) {
                        return false;
                    } else if (isWall(x, y) || isHole(x, y)) {
                        return true;
                    }
                }
                break;
            default:
                break;
        }

    }

    // odtwarza ruch gracza w podanym kierunku
    void move(int direction, bool collect) {
        switch (direction) {
            case 0:
                while (playerY > 0 && !isWall(playerX, playerY)) {
                    playerY--;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerY--;
                        break;
                    }
                }
                playerY++;
                break;
            case 1:
                while (playerY > 0 && playerX < width && !isWall(playerX, playerY)) {
                    playerX++;
                    playerY--;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX++;
                        playerY--;
                        break;
                    }
                }
                playerX--;
                playerY++;
                break;
            case 2:
                while (playerX < width && !isWall(playerX, playerY)) {
                    playerX++;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX++;
                        break;
                    }
                }
                playerX--;
                break;
            case 3:
                while (playerY < height && playerX < width && !isWall(playerX, playerY)) {
                    playerX++;
                    playerY++;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX++;
                        playerY++;
                        break;
                    }
                }
                playerX--;
                playerY--;
                break;
            case 4:
                while (playerY < height && !isWall(playerX, playerY)) {
                    playerY++;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerY++;
                        break;
                    }
                }
                playerY--;
                break;
            case 5:
                while (playerY < height && playerX > 0 && !isWall(playerX, playerY)) {
                    playerX--;
                    playerY++;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX--;
                        playerY++;
                        break;
                    }
                }
                playerX++;
                playerY--;
                break;
            case 6:
                while (playerX > 0 && !isWall(playerX, playerY)) {
                    playerX--;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX--;
                        break;
                    }
                }
                playerX++;
                break;
            case 7:
                while (playerY > 0 && playerX > 0 && !isWall(playerX, playerY)) {
                    playerX--;
                    playerY--;
                    if (collect) { collectGem(playerX, playerY); }

                    if (isHole(playerX, playerY)) {
                        playerX--;
                        playerY--;
                        break;
                    }
                }
                playerX++;
                playerY++;
                break;
            default:
                break;
        }
    }

    void closestGem(int &x, int &y, int skipX, int skipY) {
        double currentDistance = 9999;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (getFromMap(j, i) == '+') {
                    if (countDistance(j, i) < currentDistance && j != skipX && i != skipY) {
                        currentDistance = countDistance(j, i);
                        x = j;
                        y = i;
                    }
                }
            }
        }
    }

    // sprawdza czy w danym kierunku znajduje sie diament (nie uwzgledniajac zadnych ograniczen)
    bool isGem(int direction) {
        bool isGem = false;

        switch (direction) {
            case 0:
                for (int i = 0; i <= playerY; i++) {
                    for (int j = 0; j < width; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 1:
                for (int i = 0; i <= playerY; i++) {
                    for (int j = playerX; j < width; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 2:
                for (int i = 0; i < height; i++) {
                    for (int j = playerX; j < width; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 3:
                for (int i = playerY; i < height; i++) {
                    for (int j = playerX; j < width; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 4:
                for (int i = playerY; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 5:
                for (int i = playerY; i < height; i++) {
                    for (int j = 0; j <= playerX; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 6:
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j <= playerX; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
            case 7:
                for (int i = 0; i <= playerY; i++) {
                    for (int j = 0; j <= playerX; j++) {
                        if (getFromMap(j, i) == '+') {
                            isGem = true;
                        }
                    }
                }
                return isGem;
        }
    }

    // sprawdza czy w danym kierunku znajduje sie diament, uwzgledniajac dziury i sciany
    bool isGemDirectly(int direction) {
        bool isGem = false;

        switch (direction) {
            case 0:
                for (int i = playerY - 1; i > 0; i--) {
                    if (getFromMap(playerX, i) == '+') {
                        isGem = true;
                    } else if (isHole(playerX, i) || isWall(playerX, i)) {
                        break;
                    }
                }
                return isGem;
            case 1:
                for (int i = playerY - 1, j = playerX + 1; i > 0, j < width; i--, j++) {
                    if (getFromMap(j, i) == '+') {
                        isGem = true;
                    } else if (isHole(j, i) || isWall(j, i)) {
                        break;
                    }
                }
                return isGem;
            case 2:
                for (int j = playerX + 1; j < width; j++) {
                    if (getFromMap(j, playerY) == '+') {
                        isGem = true;
                    } else if (isHole(j, playerY) || isWall(j, playerY)) {
                        break;
                    }
                }
                return isGem;
            case 3:
                for (int i = playerY + 1, j = playerX + 1; i < height, j < width; i++, j++) {
                    if (getFromMap(j, i) == '+') {
                        isGem = true;
                    } else if (isHole(j, i) || isWall(j, i)) {
                        break;
                    }
                }
                return isGem;
            case 4:
                for (int i = playerY + 1; i < height; i++) {
                    if (getFromMap(playerX, i) == '+') {
                        isGem = true;
                    } else if (isHole(playerX, i) || isWall(playerX, i)) {
                        break;
                    }
                }
                return isGem;
            case 5:
                for (int i = playerY + 1, j = playerX - 1; i < height, j > 0; i++, j--) {
                    if (getFromMap(j, i) == '+') {
                        isGem = true;
                    } else if (isHole(j, i) || isWall(j, i)) {
                        break;
                    }
                }
                return isGem;
            case 6:
                for (int j = playerX - 1; j > 0; j--) {
                    if (getFromMap(j, playerY) == '+') {
                        isGem = true;
                    } else if (isHole(j, playerY) || isWall(j, playerY)) {
                        break;
                    }
                }
                return isGem;
            case 7:
                for (int i = playerY - 1, j = playerX - 1; i > 0, j > 0; i--, j--) {
                    if (getFromMap(j, i) == '+') {
                        isGem = true;
                    } else if (isHole(j, i) || isWall(j, i)) {
                        break;
                    }
                }
                return isGem;
        }
    }

    // sprawdza rekurencyjnie czy istnieje sciezka do diamentu o zadanej dlugosci i kierunku poczatkowym
    bool leadToGem(int direction, int depth) {
        int x = playerX, y = playerY;
        move(direction, false);

        bool result = false;
        int nextDirections[] = {0, 1, 2, 3, 4, 5, 6, 7};
        random_shuffle(&nextDirections[0], &nextDirections[8]);

        for (int i = 0; i < DIRECTION_COUNT; i++) {
            if (canMove(nextDirections[i]) && isGemDirectly(nextDirections[i])) {
                result = true;
            }
        }

        if (!result && depth > 0) {
            for (int i = 0; i < DIRECTION_COUNT; i++) {
                if ((direction >= 4 ? direction - 4 : direction + 4) != nextDirections[i] && canMove(nextDirections[i]) && leadToGem(nextDirections[i], --depth)) {
                    result = true;
                    break;
                }
            }
        }

        playerX = x;
        playerY = y;

        return result;
    }

};

class Exception {
};

// glowna petla algorytmu
bool solve(Game game, string path, int attempt) {
//    cout << "Path: " << path << ", points: " << game.getCurrentPoints() << "/" << game.getPoints() << endl;

    if (attempt == MAX_ATTEMPTS) {
        throw -1;
    }

    if (path.length() >= game.getMaxSteps() && game.getPoints() != game.getCurrentPoints()) {
        cout << "err: " << path << endl;
        return false;
    }

    if (game.getPoints() == game.getCurrentPoints()) {
        cout << path;
        solved = true;
        return true;
    }

    bool takeGem = false;

    // FAZA I
    int nextDirections[] = {0, 1, 2, 3, 4, 5, 6, 7};
    shuffle(&nextDirections[0], &nextDirections[8], std::mt19937(static_cast<uint32_t>(time(0))));

    for (int i = 0; i <= Game::DIRECTION_COUNT; i++) {
        if (game.canMove(nextDirections[i]) && game.isGemDirectly(nextDirections[i])) {
            game.move(nextDirections[i], true);
            path += to_string(nextDirections[i]);

            takeGem = true;
            if (solve(game, path, attempt)) {
                return true;
            };
        }
    }

    // FAZA II
    if (!takeGem) {
        for (int j = 0; j <= Game::DIRECTION_COUNT; j++) {
            if (game.canMove(j) && game.leadToGem(j, 3)) {
                game.move(j, true);
                path += to_string(j);

                takeGem = true;
                if (solve(game, path, attempt)) {
                    return true;
                };
            }
        }
    }

    // FAZA III
    if (!takeGem) {
        for (int j = 0; j <= Game::DIRECTION_COUNT; j++) {
            if (game.canMove(j) && game.isGem(j)) {
                game.move(j, true);
                path += to_string(j);

                if (solve(game, path, attempt)) {
                    return true;
                };
            }
        }
    }
}

int main(int argc, char **argv) {
    Game game;
    string line, map;

    int width, height, maxSteps;
    cin >> height >> width >> maxSteps;

    for (int i = 0; i <= height; i++) {
        getline(cin, line);
        map += line;
    }

    game.setHeight(height);
    game.setWidth(width);
    game.setMaxSteps(maxSteps);

    game.createMap(map);

    game.countPoints();
    game.getPlayerPosition();

    int attempt = 0;
    try {
        while (!solve(game, "", attempt++)) {
        }
    } catch (int exception) {
        cout << "BRAK";
        return 0;
    }


    if (!solved) {
        cout << "BRAK";
    }

    return 0;
}