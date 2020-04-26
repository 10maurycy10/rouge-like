#pragma once

enum {
    TEXTURE_PLAYER    = '@',
    TEXTURE_WALL_SIDE = '-',
    TEXTURE_WALL_TOP  = '|',
    TEXTURE_PASSAGE   = '#',
    TEXTURE_FLOOR     = '.',
};

#define MAP_OFSET_X 0
#define MAP_OFSET_Y 2

#define MAP_X 8
#define MAP_Y 5

char initMap[MAP_Y][MAP_X+1] = {
   "--------",
   "|......|",
   "-+------",
   " #      ",
   " ###### ",
};