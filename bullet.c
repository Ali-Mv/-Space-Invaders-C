#include "defines.h"

Bullet bullets[MAX_BULLETS];

void Bullet_Init() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
}

void Bullet_Spawn(int x, int y, bool isPlayer) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].active = true;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].isPlayerBullet = isPlayer;
            break;
        }
    }
}

void Bullet_Update() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            if (bullets[i].isPlayerBullet) {
                bullets[i].y--;
            }
            else {
                bullets[i].y++;
            }

            if (bullets[i].y <= 0 || bullets[i].y >= MAP_HEIGHT - 1) {
                bullets[i].active = false;
                continue;
            }

            if (bullets[i].isPlayerBullet) {
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active) {
                        if (bullets[i].x == enemies[j].x && bullets[i].y == enemies[j].y) {
                            bullets[i].active = false;
                            enemies[j].hp -= playerObj.damage;

                            if (enemies[j].hp <= 0) {
                                enemies[j].active = false;
                                currentUser.score += 10;
                                currentUser.gold += 5;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Bullet_Draw() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            char symbol = bullets[i].isPlayerBullet ? '^' : '|';
            Map_SetCell(bullets[i].x, bullets[i].y, symbol);
        }
    }
}
