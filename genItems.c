#include "item.c"

void genItem(Item* where) {

    

    int item_x = rand() % total_rarity;

    int item_id = 0;

    int c_min = 0;
    for (int x = 0; x < Length(item_types); x++) {
        c_min += item_types[x].rarity;
        if (item_x < c_min){
            item_id = x;
            break;
        }
    }

    mkItem(where, item_id, rand() % Length(item_colors),rand() % Length(item_qalatys));
}

void placeItems() {
    for (int x = 0; x < ROOMS_X; x++)
        for (int y = 0; y < ROOMS_Y; y++) {
            int minX = roomPlacement[x][y][0].x + 1;//compute boundig box
            int minY = roomPlacement[x][y][0].y + 1;
            int maxX = roomPlacement[x][y][1].x - 1;
            int maxY = roomPlacement[x][y][1].y - 1;
            printf("placing at max+%d max+%d\n",(maxX - minX),(maxY - minY));

            int offsetx = (rand() % (maxX - minX));
            int offsety = (rand() % (maxY - minY));

            int pX = minX + offsetx;
            int pY = minY + offsety;


            genItem(&map[pX][pY].items);
        }
}