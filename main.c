#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>

#define Tags TagType tags;
typedef uint64_t TagType;
#define tagGet(obj,tag) (int)(((obj).tags & (1 << tag)) | 0)
#define tagSet(obj,tag) ((obj).tags = obj.tags | (1 << tag))
#define tagClear(obj,tag) ((obj).tags = obj.tags & ~(1 << tag))
#define tagForce(obj,tag,val) val?tagSet(obj,tag):tagClear(obj,tag)
#define tagReset(obj) ((obj).tags = 0)
#define encodeTag(tag) (1 << tag)

void* mallocFAKE(int s) {
    void* x = malloc(s);
    if (!x) {
        printf("ERROR: YOU SHASHED THE HEAP! STOP _NOW_\n");
        _Exit(1);
    }
    return x;
}
//#define malloc mallocFAKE
#include <curses.h>
#include "conf.h"

void c_init() {
  initscr();
  keypad(stdscr, TRUE);
  start_color();

  curs_set(0);

  init_pair(C_blue, COLOR_BLUE, COLOR_BLACK);
  init_pair(C_green, COLOR_GREEN, COLOR_BLACK);
  init_pair(C_PINK, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(C_RED, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(C_brown,COLOR_YELLOW, COLOR_BLACK);
  init_pair(C_gray,COLOR_BLACK, COLOR_WHITE);
}

#include "screen.c"
#include "keypress.c"

int main() {

  addStaticMessage("= T H E = D U N G O N S = O F = D O O M =");

  initItems();
  genMap();
  placeItems();
  c_init();



  InvCnt = 0;
  while (Inventory)
      rmItem(&Inventory);

  render();

  while (handleIo()) {
    render();
  }

  endwin();


  return 0;
};