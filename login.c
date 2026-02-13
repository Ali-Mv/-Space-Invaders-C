#include "defines.h"

void getPasswordMasked(char* password) {
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

void WelcomeUser() {
    system("cls");
    printf("                   SPACE INVADERS                     \n\n");

    printf("Start in...");
    Sleep(500);
    printf(" 3");
    Sleep(500);

    for (int i = 2; i > 0; i--) {
        printf(", %d", i);
        Sleep(500);
    }
    system("cls");
}

int AskPlayerLogin() {
    int choice = 0;

    system("cls");
    printf("================ Login Page ================\n");
    printf("1) Sign Up\n");
    printf("2) Login\n");
    printf("3) Exit\n");
    printf("\nChoose option (1-3): ");

    while (scanf("%d", &choice) != 1 || (choice < 1 || choice > 3)) {
        printf("Invalid input. Try again: ");
    }

    return choice;
}

void SignUp() {

    while (1) {
        system("cls");
        User newUser;
        User tempUser;
        FILE* file;
        int exists = 0;
        char confirmPass[MAX_PASSWORD_LEN];
        memset(&newUser, 0, sizeof(User));

        printf("================ Sign Up ================\n");

        printf("Enter Username(max 20): ");
        scanf("%20s", newUser.username);

        file = fopen(USER_FILE, "rb");
        if (file != NULL) {
            while (fread(&tempUser, sizeof(User), 1, file)) {
                if (strcmp(tempUser.username, newUser.username) == 0) {
                    exists = 1;
                    break;
                }
            }
            fclose(file);
        }

        if (exists) {
            printf("\nError: Username already exists!\n");
            printf("Press any key to try again");
            _getch();
            continue;
        }

        while (1) {
            system("cls");
            printf("Enter Password (min 8 , max 20): ");
            getPasswordMasked(newUser.password);

            if (strlen(newUser.password) < 8) {
                printf("Error: Password must be at least 8 characters long!\n");
                printf("Press any key to try again");
                _getch();
                continue;
            }

            printf("Confirm Password: ");
            getPasswordMasked(confirmPass);

            if (strcmp(newUser.password, confirmPass) != 0) {
                printf("Error: Passwords do not match! Try again.\n");
                printf("Press any key to try again");
                _getch();
            }
            else {
                break;
            }
        }

        newUser.score = 0;
        newUser.gold = 0;
        newUser.max_level = 1;
        newUser.health_lvl = 0;
        newUser.damage_lvl = 0; 
        newUser.ammo_lvl = 0;


        file = fopen(USER_FILE, "ab");
        if (file == NULL) {
            printf("\nError saving data!\n");
            printf("Press any key to try again");
            _getch();
            continue;
        }

        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);

        printf("\nSign Up Successful! Please Login now.\n");
        printf("Press any key to continue...");
        _getch();
        break;
    }
}

void Login() {
    while (1) {

        system("cls");

        char inputUser[MAX_USERNAME_LEN];
        char inputPass[MAX_PASSWORD_LEN];
        User tempUser;
        FILE* file;
        int found = 0;

        printf("================ Login ================\n");
        printf("Enter Username: ");
        scanf("%s", inputUser);

        printf("Enter Password: ");
        getPasswordMasked(inputPass);

        file = fopen(USER_FILE, "rb");
        if (file == NULL) {
            printf("\nNo users registered yet!\n");
            printf("Press any key to return...");
            _getch();
            continue;
        }

        while (fread(&tempUser, sizeof(User), 1, file)) {
            if (strcmp(tempUser.username, inputUser) == 0 &&
                strcmp(tempUser.password, inputPass) == 0) {
                found = 1;
                break;
            }
        }
        fclose(file);

        if (found) {
            currentUser = tempUser;
            printf("\nLogin Successful! Welcome %s\n", tempUser.username);
            Sleep(1000);
        }
        else {
            printf("\nError: Invalid Username or Password.\n");
            printf("Press any key to try again...");
            _getch();
        }
        break;
    }
    
}
