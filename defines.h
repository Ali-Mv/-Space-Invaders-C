#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include "defines.h"
#include "gamecore.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <stdlib.h>
#include <string.h>
#include "login.h"
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_USERS 100
#define USER_FILE "users.txt"
#define TICK_RATE 50
#define MAP_WIDTH 60
#define MAP_HEIGHT 25
#define WALL_CHAR '#'
#define EMPTY_CHAR ' '
#define MAX_ENEMIES 20
#define MAX_BULLETS 50
enum {
    user_exists_not = 1,
    user_exists ,
    want_exit ,
};
enum {
    start_game = 1,
    show_leaderbord,
    shop,
    edit_user_info,
    logout
};
typedef struct {
    char username[20];
    char password[20];
    int score;
    int gold;
    int max_level;
    int health_lvl;
    int damage_lvl;
    int ammo_lvl;
} User;
extern User currentUser;

typedef struct {
    int x, y;
    int hp;
    int maxHp;
    int damage;
    char skin;
} Player;
extern Player playerObj;

typedef struct {
    int x, y;
    int hp;
    int active;
    int type;
    int shootTimer;
} Enemy;
extern Enemy enemies[MAX_ENEMIES];

typedef struct {
    int x, y;
    int active;
    int isPlayerBullet;
} Bullet;


