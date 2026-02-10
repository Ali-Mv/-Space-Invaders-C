#include "defines.h"

char gameMap[MAP_HEIGHT][MAP_WIDTH];

void Map_Init() {
    Map_Clear();
}

void Map_Clear() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) {
                gameMap[y][x] = WALL_CHAR;
            }
            else {
                gameMap[y][x] = EMPTY_CHAR;
            }
        }
    }
}

void Map_SetCell(int x, int y, char symbol) {
    if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1) {
        gameMap[y][x] = symbol;
    }
}

void Map_Render() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, pos);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            putchar(gameMap[y][x]);
        }
        putchar('\n');
    }
    printf("Controls: [A] Left  [D] Right  [SPACE] Shoot  [Q] Quit\n");
}
