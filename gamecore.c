#include "defines.h"

int enemiesToSpawn; 
int spawnedCount = 0;
int killedCount = 0;

Player playerObj;
Enemy enemies[MAX_ENEMIES];

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GoGameLoop() {
    int gameOver = 1;
    char input = 0;
    int timer = 0;
    int currentLvl = currentUser.max_level;
    enemiesToSpawn = (int)(3 * sqrt(currentLvl)) + 2;
    spawnedCount = 0;
    killedCount = 0;

    system("cls");
    HideCursor();
    Map_Clear();
    Player_Init();
    Enemy_Init();
    Bullet_Init();

    while (gameOver == 1) {
        if (_kbhit()) {
            input = _getch();
            if (input == 'q' || input == 'Q') break;
        }
        else {
            input = 0;
        }

        Player_Update(input);
        Bullet_Update();

        if (spawnedCount < enemiesToSpawn) {
            int oldActiveCount = 0;
            for (int i = 0; i < MAX_ENEMIES; i++)
                if (enemies[i].active) oldActiveCount++;

            Enemy_Spawner(timer);

            int newActiveCount = 0;
            for (int i = 0; i < MAX_ENEMIES; i++)
                if (enemies[i].active) newActiveCount++;

            if (newActiveCount > oldActiveCount)
                spawnedCount++;
        }

        Enemy_Update(timer);

        int currentlyActive = 0;
        for (int i = 0; i < MAX_ENEMIES; i++)
            if (enemies[i].active) currentlyActive++;

        killedCount = spawnedCount - currentlyActive;

        if (spawnedCount >= enemiesToSpawn && currentlyActive == 0 && spawnedCount > 0) {
            gameOver = 2;
        }

        if (playerObj.hp <= 0) {
            gameOver = 0;
        }

        Map_Clear();
        Player_Draw();
        Enemy_Draw();
        Bullet_Draw();
        Gotoxy(0, 0);
        Map_Render();

        printf("\n LEVEL: %d | HP: %d/%d | Progress: %d/%d",
            currentLvl, playerObj.hp, playerObj.maxHp, killedCount, enemiesToSpawn);
        printf("\n Score: %d | Gold: %d", currentUser.score, currentUser.gold);

        Sleep(TICK_RATE);
        timer++;
    }

    SaveChangesToFile();
    system("cls");

    if (gameOver == 0) {
        printf("GAME OVER! Final Score: %d\n", currentUser.score);
        printf("Press any key to return to menu...");
        _getch();
    }
    else if (gameOver == 2) {
        printf("LEVEL COMPLETE!\n");
        currentUser.max_level++;
        printf("Press any key to return to menu...");
        _getch();
    }
}
