#include "defines.h"

User currentUser;

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
        scanf("%s", newName);

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