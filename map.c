#include <stdint.h>

#define MAP_X 80
#define MAP_Y 80

enum {TYLE_UNCOVERED, TYLE_DARK};

struct Tyle {
  char    Texture;
  uint8_t tags;
};

struct Tyle map[MAP_X][MAP_Y];


void genMap() {
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            tagReset(map[x][y]);
            map[x][y].Texture = '#';
        }
}

void drawMap() {

}