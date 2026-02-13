#include "defines.h"

Bullet bullets[MAX_BULLETS];

int playerBulletIndex = 0;
int enemyBulletIndex = MAX_PLAYER_BULLETS;

void Bullet_Init() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
    playerBulletIndex = 0;
    enemyBulletIndex = MAX_PLAYER_BULLETS;
}

void Bullet_Spawn(int x, int y, bool isPlayer) {
    if (isPlayer) {
        int idx = playerBulletIndex;

        bullets[idx].active = true;
        bullets[idx].x = x;
        bullets[idx].y = y;
        bullets[idx].isPlayerBullet = true;

        playerBulletIndex = (playerBulletIndex + 1) % MAX_PLAYER_BULLETS;
    }
    else {
        int maxEnemyBulletsAllowed = (int)(2 * log2(currentUser.max_level + 2));

        int idx = enemyBulletIndex;

        bullets[idx].active = true;
        bullets[idx].x = x;
        bullets[idx].y = y;
        bullets[idx].isPlayerBullet = false;

        enemyBulletIndex++;
        if (enemyBulletIndex >= MAX_BULLETS) {
            enemyBulletIndex = MAX_PLAYER_BULLETS;
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

                                if (enemies[j].type == 0) currentUser.score += 3;
                                else currentUser.score += 5;

                                currentUser.gold += (enemies[j].type == 0) ? 3 : 5;
                            }
                            break;
                        }
                    }
                }
            }
            else {
                if (bullets[i].x == playerObj.x && bullets[i].y == playerObj.y) {
                    bullets[i].active = false;
                    playerObj.hp -= 1;
                }
            }
        }
    }
}

void Bullet_Draw() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            char symbol = bullets[i].isPlayerBullet ? '^' : 'o';
            Map_SetCell(bullets[i].x, bullets[i].y, symbol);
        }
    }
}
