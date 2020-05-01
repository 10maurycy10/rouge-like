#include "item.c"

void genItems(Item* where) {

    printw("%d ",total_rarity);

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