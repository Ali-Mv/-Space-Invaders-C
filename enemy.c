#include "defines.h"




void Enemy_Init() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
    }
}

void Enemy_Spawner(int timer) {
    int Level = currentUser.max_level;

    double spawnProb = 0.02 + (0.0025 * Level);
    if (spawnProb > 0.4) spawnProb = 0.4;

    if (((double)rand() / RAND_MAX) < spawnProb) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].active = true;
                enemies[i].x = (rand() % (MAP_WIDTH - 4)) + 2;
                enemies[i].y = 1;
                enemies[i].shootTimer = 0;

                double shooterProb = 0.01 * Level;
                if (shooterProb > 0.5) shooterProb = 0.5;

                if (((double)rand() / RAND_MAX) < shooterProb) {
                    enemies[i].type = 1;
                    enemies[i].hp = 1 + (Level / 15);
                }
                else {
                    enemies[i].type = 0;
                    enemies[i].hp = 2 + (Level / 10);
                }

                enemies[i].damage = 1 + (Level / 20);

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
            if (enemies[i].x < playerObj.x) enemies[i].x++;
            else if (enemies[i].x > playerObj.x) enemies[i].x--;

            if (enemies[i].y < playerObj.y) enemies[i].y++;
            else if (enemies[i].y > playerObj.y) enemies[i].y--;

            if (abs(enemies[i].x - playerObj.x) <= 1 &&
                abs(enemies[i].y - playerObj.y) <= 1) {
                playerObj.hp -= enemies[i].damage;
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
            if (enemies[i].shootTimer > 20) {
                Bullet_Spawn(enemies[i].x, enemies[i].y + 1, false);
                enemies[i].shootTimer = 0;
            }
        }
    }
}
void Enemy_Draw() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            char symbol = (enemies[i].type == 0) ? 'M' : 'S';
            Map_SetCell(enemies[i].x, enemies[i].y, symbol);
        }
    }
}
