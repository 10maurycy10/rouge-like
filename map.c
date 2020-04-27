#include <math.h>
#include <stdint.h>
#include "main.h"
#include "conf.h"

enum {TYLE_UNCOVERED, TYLE_DARK, TYLE_IMPASABLE, TYLE_FLOOR, TYLE_VIS,};

//TYLE_UNCOVERED whether is will be rendered at all
//TYLE_DARK       agasent uncover alny
//TYLE_IMPASSABLE block movemernt
//TYLE_FLOOR      not rendered when outside vis
//TYLE_VIS  curenty visable (recomputer 1 p frame)

//walls need to be       TYLE_DARK and TYLE_IMPASSABLE
//passages and doors are TYLE_DARK
//floors are             TYLE_FLOOR
//passage lining is      TYLE_IMPASABLE and TYLE_DARK


struct Tyle {
  char    Texture;
  uint8_t tags;
};

struct Tyle map[MAP_X][MAP_Y];

void revealTyle(int x,int y, bool r) { //reval 1 tyile if dark recurcive if not
    if (x > -1 && x < MAP_X && y > -1 && y < MAP_Y) {
        if (tagGet(map[x][y],TYLE_UNCOVERED) && tagGet(map[x][y],TYLE_VIS)) return;
        tagSet(map[x][y], TYLE_UNCOVERED);
        tagSet(map[x][y], TYLE_VIS);
        if (((!tagGet(map[x][y],TYLE_DARK)) && r) || !r) {
            revealTyle(x,y + 1,1);
            revealTyle(x,y - 1,1);
            revealTyle(x + 1,y,1);
            revealTyle(x - 1,y,1);
            revealTyle(x + 1,y + 1,1);
            revealTyle(x - 1,y + 1,1);
            revealTyle(x + 1,y - 1,1);
            revealTyle(x - 1,y - 1,1);
        }
    }
}

void hideTyles() {
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            tagClear(map[x][y],TYLE_VIS);
        }
}
/*
MAP LAYOUT

1 2 3
4 5 6
7 8 9

4 = passages

*/

void addWall(int x, int y, char ch) {
    tagSet(map[x][y],TYLE_IMPASABLE);
    tagSet(map[x][y],TYLE_DARK);
    map[x][y].Texture = ch;
}

void fillRoom(int sx, int sy, int ex, int ey, bool dark) {
    addWall(sx,sy,'-');
    addWall(sx,ey,'-');
    addWall(ex,sy,'-');
    addWall(ex,ey,'-');

    for (int i = sy; i < (ey + 1); i ++)
        addWall(sx, i, '|');
    for (int i = sy; i < (ey + 1); i ++)
        addWall(ex, i, '|');
    for (int i = sx; i < (ex + 1); i ++)
        addWall(i, sy, '-');
    for (int i = sx; i < (ex + 1); i ++)
        addWall(i, ey, '-');

    for (int x = sx + 1; x < ex; x ++)
        for (int y = sy + 1; y < ey; y ++) {
            map[x][y].Texture = '.';
            tagSet(map[x][y],TYLE_FLOOR);
            if (dark) tagSet(map[x][y],TYLE_DARK);
        }
}

void addDoor(int x, int y) {
    map[x][y].Texture = '+';
    tagClear(map[x][y],TYLE_IMPASABLE);
}

void addPassage(int x, int y) {
    map[x][y].Texture = '#';
    tagSet(map[x][y],TYLE_DARK);
}

void genMap() {
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            tagReset(map[x][y]);
            map[x][y].Texture = ' ';
            //int t = initMap[y][x];
            //map[x][y].Texture = t;
            //if (t == ' ' || t == '-' || t == '|')
            //    tagSet(map[x][y],TYLE_IMPASABLE);
            //if (t == '#' || t == '+' || t == ',')
            //    tagSet(map[x][y],TYLE_DARK);
            //if (t == '.' || t == ',')
            //    tagSet(map[x][y],TYLE_FLOOR);
            //if (t == ',')
            //    map[x][y].Texture = '.';
        }

    fillRoom(1,1,5,5,0);
    fillRoom(9,1,14,5,1);

    addDoor(5,3);
    addDoor(9,3);
    addPassage(6,3);
    addPassage(7,3);
    addPassage(8,3);

    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            if (map[x][y].Texture == ' ') { //fix passages
                tagSet(map[x][y], TYLE_IMPASABLE);
                tagSet(map[x][y], TYLE_DARK);
            }
        }

    movePlayerABS(2,2);
}

void drawMap(int px,int py) {
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            char c = ' ';
            struct Tyle t = map[x][y];
            if (tagGet(t,TYLE_UNCOVERED)) {
                c = map[x][y].Texture;
                if (tagGet(t,TYLE_FLOOR) && !tagGet(t,TYLE_VIS)) //if not vis and is floor hide tyle
                    c = ' ';
            }
            attrset(tagGet(t,TYLE_VIS)?COLOR_PAIR(0):COLOR_PAIR(1));
            //attrset(COLOR_PAIR(0));
            mvaddch(y + MAP_OFSET_Y, x + MAP_OFSET_X, c);
        }
}