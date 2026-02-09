#include "defines.h"

int ShowMenu() {
    int choice;
    system("cls");
    printf("\n=================================\n");
    printf("          MAIN MENU              \n");
    printf("=================================\n");
    printf("1. Start Game\n");
    printf("2. Leaderboard\n");
    printf("3. Shop\n");
    printf("4. Edit Profile\n");
    printf("5. Logout\n\n");
    printf("Enter choice: ");

    while (scanf("%d", &choice) != 1)
        continue;

    return choice;
}