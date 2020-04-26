#include "conf.h"

int playerX = 1;
int playerY = 1;

void movePlayerABS(int nx, int ny) {
    struct Tyle t = map[nx][ny];

    if (!tagGet(t, TYLE_IMPASABLE)) {
        hideTyles();
        playerX = nx;
        playerY = ny;

        revealTyle(nx, ny , 0);
    }
}

void movePlayer(int xd,int yd) { //move player by xd yd
    int nx = playerX + xd;
    int ny = playerY + yd;

    movePlayerABS(nx,ny);
}

void drawPlayer() { //just draw the player
    attrset(COLOR_PAIR(0));
    mvaddch(playerY + MAP_OFSET_Y,playerX + MAP_OFSET_X, TEXTURE_PLAYER);
}