#include <math.h>
#include <stdint.h>
#include "conf.h"

enum {TYLE_UNCOVERED, TYLE_DARK, TYLE_IMPASABLE, TYLE_FLOOR, TYLE_VIS,};

//TYLE_UNCOVERED whether is will be rendered at all
//TYLE_DARK       agasent uncover alny
//TYLE_IMPASSABLE block movemernt
//TYLE_FLOOR      not rendered when outside vis
//TYLE_VIS  curenty visable

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
        if ((!tagGet(map[x][y],TYLE_DARK)) && r && (!tagGet(map[x][y],TYLE_IMPASABLE))) {
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

void genMap() {
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            tagReset(map[x][y]);
            int t = initMap[y][x];
            map[x][y].Texture = t;
            if (t == ' ' || t == '-' || t == '|')
                tagSet(map[x][y],TYLE_IMPASABLE);
            if (t == '#' || t == '+')
                tagSet(map[x][y],TYLE_DARK);
            if (t == '.')
                tagSet(map[x][y],TYLE_FLOOR);
        }
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
            mvaddch(y + MAP_OFSET_Y, x + MAP_OFSET_X, c);
        }
}