#pragma once
#include <stdint.h>

enum {
    TEXTURE_PLAYER    = '@',
    TEXTURE_WALL_SIDE = '-',
    TEXTURE_WALL_TOP  = '|',
    TEXTURE_PASSAGE   = '#',
    TEXTURE_FLOOR     = '.',
    TEXTURE_DOOR      = '+',
    TEXTURE_ITEM      = '^',
    TEXTURE_EMPTY     = ' ',
};

#define MAP_OFSET_X 0
#define MAP_OFSET_Y 2

#define MAP_X 40
#define MAP_Y 20

#define ROOMS_X 3
#define ROOMS_Y 3

#ifndef INV_LIM
#define INV_LIM 8
#endif

enum COLORS {C_RED = 1, C_PINK, C_blue, C_green, C_brown, C_gray};

enum {TYLE_UNCOVERED, TYLE_DARK, TYLE_IMPASABLE, TYLE_FLOOR, TYLE_VIS,};
//TYLE_UNCOVERED whether is will be rendered at all
//TYLE_DARK       agasent uncover alny
//TYLE_IMPASSABLE block movemernt
//TYLE_FLOOR      not rendered when outside vis
//TYLE_VIS  curenty visable (recomputer 1e p frame)
//walls need to be       TYLE_DARK and TYLE_IMPASSABLE
//passages and doors are TYLE_DARK
//floors are             TYLE_FLOOR
//passage lining is      TYLE_IMPASABLE and TYLE_DARK

struct item_color {
    char* name;
    int   render;
};

typedef struct Item {
    int type;
    struct item_color color;
    char* qality;
    struct Item* next;
    int x;
    int y;
} *Item;

struct Tyle {
  char    Texture;
  uint8_t tags;
  Item items;
};

struct Tyle map[MAP_X][MAP_Y];


#ifndef bool
#define bool uint8_t
#define true 0xff
#define false 0
#endif
