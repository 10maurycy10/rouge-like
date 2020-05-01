#include <math.h>
#include <stdint.h>
#include "main.h"
#include "conf.h"
#include "vect.h"

#include "item.c"

Item item = NULL;

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



#include "genRoom.c"
#include "genItems.c"

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
            //attrset(tagGet(t,TYLE_VIS)?COLOR_PAIR(0):COLOR_PAIR(1));
            attrset(COLOR_PAIR(0));
            mvaddch(y + MAP_OFSET_Y, x + MAP_OFSET_X, c);
        }

    //genItems(&item);
    move(0,0);
    //printItem(item);
}