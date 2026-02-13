#include "defines.h"

void getPassMaskedMenu(char* password) {
    int i = 0;
    char ch;
    while (1) {
        ch = _getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            if (i < MAX_PASSWORD_LEN - 1) {
                password[i] = ch;
                i++;
                printf("*");
            }
        }
    }
    printf("\n");
}

void SaveChangesToFile() {
    FILE* fp = fopen(USER_FILE, "rb");
    if (!fp) return;

    User users[MAX_USERS];
    int count = 0;

    while (fread(&users[count], sizeof(User), 1, fp)) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, currentUser.username) == 0) {
            users[i] = currentUser;
            break;
        }
    }

    fp = fopen(USER_FILE, "wb");
    for (int i = 0; i < count; i++) {
        fwrite(&users[i], sizeof(User), 1, fp);
    }
    fclose(fp);
}

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

void ShowLeaderBord() {
    system("cls");
    FILE* fp = fopen(USER_FILE, "rb");
    if (!fp) {
        printf("No data available.\n");
        _getch();
        return;
    }

    User users[MAX_USERS];
    int count = 0;
    while (fread(&users[count], sizeof(User), 1, fp)) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (users[j].max_level < users[j + 1].max_level) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    printf("\n========= LEADERBOARD =========\n");
    printf("%-5s %-15s %-10s\n", "Rank", "Username", "Max Stage");
    printf("-------------------------------\n");

    int limit = (count < 10) ? count : 10;
    for (int i = 0; i < limit; i++) {
        printf("%-5d %-15s %-10d\n", i + 1, users[i].username, users[i].max_level);
    }

    int myRank = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, currentUser.username) == 0) {
            myRank = i + 1;
            break;
        }
    }

    printf("\n-------------------------------\n");
    if (myRank != -1) {
        printf("Your Rank: %d\n", myRank);
        printf("Your Max Stage: %d\n", currentUser.max_level);
    }

    printf("\nPress any key to return...");
    _getch();
}

void GoShop() {
    int choice;
    while (1) {
        system("cls");
        printf("\n========== SHOP ==========\n");
        printf("Gold: %d\n", currentUser.gold);
        printf("--------------------------\n");
        printf("1. Extra Heart (+1 Health)      - 25 Gold\n");
        printf("2. Damage Up (+1 Damage)        - 40 Gold\n");
        printf("3. Max Ammo Up (+1 Max Ammo)    - 80 Gold\n");
        printf("4. Back to Menu\n");
        printf("--------------------------\n");
        printf("Choose item: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch (choice) {
        case 1:
            if (currentUser.gold >= 25) {
                currentUser.gold -= 25;
                currentUser.health_lvl++;
                SaveChangesToFile();
                printf("\nPurchased Extra Heart!\n");
            }
            else {
                printf("\nNot enough gold!\n");
            }
            break;
        case 2:
            if (currentUser.gold >= 40) {
                currentUser.gold -= 40;
                currentUser.damage_lvl++;
                SaveChangesToFile();
                printf("\nPurchased Damage Up!\n");
            }
            else {
                printf("\nNot enough gold!\n");
            }
            break;
        case 3:
            if (currentUser.gold >= 80) {
                currentUser.gold -= 80;
                currentUser.ammo_lvl++;
                SaveChangesToFile();
                printf("\nPurchased Max Ammo Up!\n");
            }
            else {
                printf("\nNot enough gold!\n");
            }
            break;
        default:
            printf("\nInvalid option.\n");
        }
        Sleep(1000);
    }
}

void EditInfo() {
    int choice;
    system("cls");
    printf("\n=== EDIT PROFILE ===\n");
    printf("1. Change Username\n");
    printf("2. Change Password\n");
    printf("3. Back\n");
    printf("Select option: ");
    scanf("%d", &choice);

    if (choice == 3) return;

    if (choice == 1) {
        char newName[MAX_USERNAME_LEN];
        printf("Enter new username: ");
        scanf("%20s", newName);

        FILE* fp = fopen(USER_FILE, "rb");
        User temp;
        int exists = 0;
        if (fp) {
            while (fread(&temp, sizeof(User), 1, fp)) {
                if (strcmp(temp.username, newName) == 0) {
                    exists = 1;
                    break;
                }
            }
            fclose(fp);
        }

        if (exists) {
            printf("\nError: Username already taken!\n");
            _getch();
            return;
        }

        User users[MAX_USERS];
        int count = 0;
        fp = fopen(USER_FILE, "rb");
        if (fp) {
            while (fread(&users[count], sizeof(User), 1, fp)) {
                count++;
            }
            fclose(fp);
        }

        for (int i = 0; i < count; i++) {
            if (strcmp(users[i].username, currentUser.username) == 0) {
                strcpy(users[i].username, newName);
                break;
            }
        }

        fp = fopen(USER_FILE, "wb");
        for (int i = 0; i < count; i++) {
            fwrite(&users[i], sizeof(User), 1, fp);
        }
        fclose(fp);

        strcpy(currentUser.username, newName);
        printf("\nUsername updated successfully!\n");
        Sleep(1000);
    }
    else if (choice == 2) {
        char newPass[MAX_PASSWORD_LEN];
        char confirmPass[MAX_PASSWORD_LEN];

        while (1) {
            printf("Enter new password (min 8 chars): ");
            getPassMaskedMenu(newPass);

            if (strlen(newPass) < 8) {
                printf("Error: Too short!\n");
                continue;
            }

            printf("Confirm new password: ");
            getPassMaskedMenu(confirmPass);

            if (strcmp(newPass, confirmPass) != 0) {
                printf("Error: Passwords do not match!\n");
            }
            else {
                break;
            }
        }

        strcpy(currentUser.password, newPass);
        SaveChangesToFile();
        printf("\nPassword changed successfully!\n");
        Sleep(1000);
    }
}