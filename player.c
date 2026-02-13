#include "defines.h"


void Player_Init() {
    playerObj.x = MAP_WIDTH / 2;
    playerObj.y = MAP_HEIGHT - 2;
    playerObj.skin = 'A';
    playerObj.maxHp = DEFAULT_HP + currentUser.health_lvl;
    playerObj.hp = playerObj.maxHp;
    playerObj.damage = DEFAULT_DAMAGE + currentUser.damage_lvl;
}

void Player_Update(char input) {
    if ((input == 'a' || input == 'A') && playerObj.x > 1) {
        playerObj.x--;
    }
    if ((input == 'd' || input == 'D') && playerObj.x < MAP_WIDTH - 2) {
        playerObj.x++;
    }

    if ((input == 'w' || input == 'W') && playerObj.y > 1) {
        playerObj.y--;
    }
    if ((input == 's' || input == 'S') && playerObj.y < MAP_HEIGHT - 2) {
        playerObj.y++;
    }

    if (input == space) {
        Bullet_Spawn(playerObj.x, playerObj.y - 1, true);
    }
}

void Player_Draw() {
    Map_SetCell(playerObj.x, playerObj.y, playerObj.skin);
}
