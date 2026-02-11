#include "defines.h"
#include <math.h>

Enemy enemies[MAX_ENEMIES];
Player playerObj;
extern User currentUser;

void Enemy_Init() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
    }
}

void Enemy_Spawner(int timer) {
    int currentLevel = currentUser.max_level;
    double prob = 0.02 + (0.0025 * currentLevel);
    if (prob > 0.4) prob = 0.4;

    if ((rand() % 10000) < (prob * 10000)) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].active = true;
                enemies[i].hp = 20 + (currentLevel * 2);
                enemies[i].x = (rand() % (MAP_WIDTH - 4)) + 2;
                enemies[i].y = 1;

                if (rand() % 2 == 0)
                    enemies[i].type = 0;
                else
                    enemies[i].type = 1;

                enemies[i].shootTimer = 0;
                break;
            }
        }
    }
}

void Enemy_Update(int timer) {
    if (timer % 3 != 0) return;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;

        if (enemies[i].type == 0) {
            int dx = abs(playerObj.x - enemies[i].x);
            int dy = abs(playerObj.y - enemies[i].y);

            if (dx + dy == 0) continue;

            int moveProb = (dx * 100) / (dx + dy);

            if ((rand() % 100) < moveProb) {
                if (enemies[i].x < playerObj.x) enemies[i].x++;
                else if (enemies[i].x > playerObj.x) enemies[i].x--;
            }
            else {
                if (enemies[i].y < playerObj.y) enemies[i].y++;
                else if (enemies[i].y > playerObj.y) enemies[i].y--;
            }

            if (enemies[i].x == playerObj.x && enemies[i].y == playerObj.y) {
                playerObj.hp -= 15;
                enemies[i].active = false;
            }
        }
        else if (enemies[i].type == 1) {
            int minH = MAP_HEIGHT / 4;
            int maxH = (MAP_HEIGHT * 2) / 3;

            if (enemies[i].y < minH) enemies[i].y++;
            else if (enemies[i].y > maxH) enemies[i].y--;
            else {
                if (rand() % 10 < 3) enemies[i].x += (rand() % 3) - 1;
                if (enemies[i].x < 1) enemies[i].x = 1;
                if (enemies[i].x > MAP_WIDTH - 2) enemies[i].x = MAP_WIDTH - 2;
            }

            enemies[i].shootTimer++;
            if (enemies[i].shootTimer > 15) {
                if (rand() % 10 < 4) {
                    Bullet_Spawn(enemies[i].x, enemies[i].y + 1, false);
                }
                enemies[i].shootTimer = 0;
            }
        }
    }
}

void Enemy_Draw() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            char skin = (enemies[i].type == 0) ? 'M' : 'S';
            Map_SetCell(enemies[i].x, enemies[i].y, skin);
        }
    }
}
