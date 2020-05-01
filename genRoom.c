#pragma once
#include "vect.h"
#include "conf.h"
#include <math.h>
#include <time.h>

IntVect2 start_pos;
IntVect2 roomPlacement[ROOMS_X][ROOMS_Y][2];
bool     roomDark[ROOMS_X][ROOMS_Y];
bool     hasPassage[ROOMS_X][ROOMS_Y][4];
bool     isInAcseable[ROOMS_X][ROOMS_Y];

void setUpRooms() { //generate room placement data
    int tRoomSpacingX = MAP_X/ROOMS_X;
    int tRoomSpacingY = MAP_Y/ROOMS_Y;

    for (int x = 0; x < ROOMS_X; x ++)
        for (int y = 0; y < ROOMS_Y; y ++) {
            roomPlacement[x][y][0].x = x * tRoomSpacingX;
            roomPlacement[x][y][0].y = y * tRoomSpacingY;
            roomPlacement[x][y][1].x = x * tRoomSpacingX + tRoomSpacingX*2 / 3;
            roomPlacement[x][y][1].y = y * tRoomSpacingY + tRoomSpacingY*2 / 3;

            isInAcseable[x][y] = false;
            roomDark[x][y] = false;
        }



    isInAcseable[rand() % ROOMS_X][rand() % ROOMS_Y] = true; //make 1-2 inacsesable rooms
    isInAcseable[rand() % ROOMS_X][rand() % ROOMS_Y] = true;

    int startRoomX = rand() % 3;
    int startRoomY = rand() % 3;

    isInAcseable[startRoomX][startRoomY] = false;

    start_pos.x = roomPlacement[startRoomX][startRoomY][0].x + 2;
    start_pos.y = roomPlacement[startRoomX][startRoomY][0].y + 2;
}

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
    printf("x: %d y:%d",x,y);
    map[x][y].Texture = '#';
    tagSet(map[x][y],TYLE_DARK);
}

void linkRoomH(int roomSX, int roomSY, int roomEX, int roomEY) { //passage generaton

    if (roomEX > ROOMS_X - 1 || roomEY > ROOMS_Y - 1) return; //if out of bounds do nothing

    if (isInAcseable[roomSX][roomSY]) return;
    if (isInAcseable[roomEX][roomEY]) return;

    int sx = roomPlacement[roomSX][roomSY][1].x + 1;
    int ex = roomPlacement[roomEX][roomEY][0].x - 1;

    int sy = roomPlacement[roomSX][roomSY][0].y + 1 + (rand() % (roomPlacement[roomSX][roomSY][1].y - roomPlacement[roomSX][roomSY][0].y - 1));

    for (int x = sx; x < (ex + 1); x++)
        addPassage(x,sy);

    addDoor(sx - 1,sy);
    addDoor(ex + 1,sy);
}
void linkRoomV(int roomSX, int roomSY, int roomEX, int roomEY) {

    if (roomEX > ROOMS_X - 1 || roomEY > ROOMS_Y - 1) return; //if out of bounds do nothing

    if (isInAcseable[roomSX][roomSY]) return;
    if (isInAcseable[roomEX][roomEY]) return;

    int sy = roomPlacement[roomSX][roomSY][1].y + 1;
    int ey = roomPlacement[roomEX][roomEY][0].y - 1;

    int sx = roomPlacement[roomSX][roomSY][0].x + 1 + (rand() % (roomPlacement[roomSX][roomSY][1].x - roomPlacement[roomSX][roomSY][0].x - 1));

    for (int y = sy; y < (ey + 1); y++)
        addPassage(sx,y);

    addDoor(sx, sy - 1);
    addDoor(sx, ey + 1);
}

void fillRooms() {
    for (int x = 0; x < 3 ; x++)
        for (int y = 0; y < 3 ; y++) {
            fillRoom(roomPlacement[x][y][0].x,roomPlacement[x][y][0].y,roomPlacement[x][y][1].x,roomPlacement[x][y][1].y,roomDark[x][y]);
            //linkRoom(x,y,x,y + 1);
        }
    for (int x = 0; x < 3 ; x++)
        for (int y = 0; y < 3 ; y++) {
            linkRoomH(x,y,x + 1,y);
            linkRoomV(x,y,x,y + 1);
        }
}

void genMap() {
    time_t x;
    time(&x);
    srand(x);
    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            tagReset(map[x][y]);
            #ifdef CONF_UNCOVER_ALL
            tagSet(map[x][y],TYLE_UNCOVERED);
            #endif
            map[x][y].Texture = ' ';
        }

    setUpRooms();
    fillRooms();

    for (int x = 0; x < MAP_X; x++)
        for (int y = 0; y < MAP_Y; y++) {
            if (map[x][y].Texture == ' ') {
                tagSet(map[x][y], TYLE_IMPASABLE);
                tagSet(map[x][y], TYLE_DARK);
            }
        }
    movePlayerABS(start_pos.x,start_pos.y);

    
}