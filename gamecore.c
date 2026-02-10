#include "defines.h"

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorPosition(consoleHandle, (COORD) { 0, 0 });
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

    system("cls");
    HideCursor();

    Map_Init(1);
    Player_Init();

    while (gameOver == 1) {

        input = 0;
        if (_kbhit()) {
            input = _getch();
            if (input == 'q') break;
        }

        Player_Update(input);
        Bullet_Update();
        Enemy_Spawner(timer);
        Enemy_Update(timer);

        if (playerObj.hp <= 0)
            gameOver = 0 ;
        else

        Gotoxy(0, 0);
        Map_Render();

        printf(
            "\nScore: %d  |  Gold: %d  |  Health: %d  ",
            currentUser.score,
            currentUser.gold,
            100
        );

        Sleep(TICK_RATE);
        timer++;
    }

    system("cls");

    if (gameOver == 0) {
        printf("\n\n   GAME OVER! \n\n");
    }
    else if (gameOver == 2) {
        printf("\n\n   VICTORY! \n\n");
    }

    printf("Press any key to return to menu...");
    _getch();
    system("cls");
}