#include "conf.h"

int playerX = 1;
int playerY = 1;

int InvCnt = 0;
Item Inventory = NULL;

void pickup(Item *d) {
    if (!*d)
        return;
    if (InvCnt > 1)
        return;
    InvCnt ++;
    Item that = unlinkI(d);
    that -> next = Inventory;
    Inventory = that;
}


void drop() {
    mvprintw(0,0,"Drop What: ");
    int what = getint();
    if (what == -1)
        return;
    Item* w = &Inventory;
    while (what) {
        w = &(*w)->next;
        if ((*w) == NULL) {
            addStaticMessage("That is not in your pack (i to view).");
            return;
        }
        what--;
    }
    if ((*w) == NULL) {
        addStaticMessage("That is not in your pack (i to view).");
        return;
    }
    InvCnt --;
    Item rest = map[playerX][playerY].items;
    map[playerX][playerY].items = unlinkI(w);
    map[playerX][playerY].items->next = rest;
}

void printInv() {
    Item Inv = Inventory;
    int i = 0;
    move(0,0);
    printw("You Have:\n");
    while (Inv) {
        printw("    %d : ",i);
        printItem(Inv);
        printw("\n");
        Inv = Inv->next;
        i++;
    }
    getch();
    clear();
}

void movePlayerABS(int nx, int ny) {
    struct Tyle t = map[nx][ny];

    if (!tagGet(t, TYLE_IMPASABLE)) {
        pickup(&map[nx][ny].items);
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