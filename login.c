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
int isValidEmail(const char* email) {
    int len = strlen(email);
    if (len < 6) return 0;

    int atCount = 0;
    int atPos = -1;
    int dotPosAfterAt = -1;

    if (!isalnum(email[0])) return 0;

    for (int i = 0; i < len; i++) {
        char c = email[i];

        if (!isalnum(c) && c != '.' && c != '_' && c != '-' && c != '@') {
            return 0;
        }

        if (c == ' ') return 0;

        if (c == '@') {
            atCount++;
            atPos = i;
            if (i == 0 || i == len - 1) return 0;
        }

        if (atCount == 1 && c == '.' && i > atPos + 1) {
            dotPosAfterAt = i;
        }
    }
    if (atCount != 1) return 0;
    if (dotPosAfterAt == -1) return 0;
    if (len - dotPosAfterAt <= 2) return 0;
    if (atPos < 1) return 0;
    if (dotPosAfterAt - atPos <= 1) return 0;

    return true;
}
void ForgotPassword() {
    char inputUser[MAX_USERNAME_LEN];
    char inputEmail[50];
    User tempUser;
    FILE* file;
    int found = 0;
    char newPass[MAX_PASSWORD_LEN];
    char confirmPass[MAX_PASSWORD_LEN];

    system("cls");
    printf("================ Forgot Password ================\n");

    printf("Enter your Username: ");
    scanf("%s", inputUser);

    printf("Enter your registered Email: ");
    scanf("%s", inputEmail);

    file = fopen(USER_FILE, "rb+");

    if (file == NULL) {
        printf("\nError: Could not open user database or no users exist.\n");
        printf("Press any key to return...");
        _getch();
        return;
    }

    while (fread(&tempUser, sizeof(User), 1, file)) {
        if (strcmp(tempUser.username, inputUser) == 0 &&
            strcmp(tempUser.email, inputEmail) == 0) {

            found = 1;
            printf("\nUser verified!\n");

            while (1) {
                printf("\nEnter New Password (min 8,max 20 chars): ");
                getPasswordMasked(newPass);

                if (strlen(newPass) < 8) {
                    printf("Error: Password must be at least 8 characters long!\n");
                    continue;
                }

                printf("Confirm New Password: ");
                getPasswordMasked(confirmPass);

                if (strcmp(newPass, confirmPass) != 0) {
                    printf("Error: Passwords do not match! Try again.\n");
                }
                else {
                    strcpy(tempUser.password, newPass);
                    break;
                }
            }

            fseek(file, -((long)sizeof(User)), SEEK_CUR);
            fwrite(&tempUser, sizeof(User), 1, file);

            printf("\nPassword successfully reset!\n");
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nError: Username and Email combination not found.\n");
    }

    printf("Press any key to return to menu...");
    _getch();
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
    printf("3) Forgot Password\n");
    printf("4) Exit\n");
    printf("\nChoose option (1-4): ");

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
        while (1) {
            system("cls");
            printf("Enter Email: ");
            scanf("%49s", newUser.email);
            if (!isValidEmail(newUser.email)) {
                printf("\nError: Invalid email format! (example: user@example.com)\n");
                printf("Press any key to try again...");
                _getch();
                continue;
            }
            break;
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
