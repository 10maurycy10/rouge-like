#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>

#define Tags TagType tags;
typedef uint64_t TagType;
#define tagGet(obj,tag) (int)((obj.tags & (1 << tag)) | 0)
#define tagSet(obj,tag) (obj.tags = obj.tags | (1 << tag))
#define tagClear(obj,tag) (obj.tags = obj.tags & ~(1 << tag))
#define tagForce(obj,tag,val) val?tagSet(obj,tag):tagClear(obj,tag)
#define tagReset(obj) (obj.tags = 0)
#define encodeTag(tag) (1 << tag)

void* mallocFAKE(int s) {
    void* x = malloc(s);
    if (!x) {
        printf("ERROR: out of memory!!");
        _Exit(1);
    }
    return x;
}
#define malloc mallocFAKE
#include <curses.h>

void c_init() {
  initscr();
  keypad(stdscr, TRUE);
  start_color();

  curs_set(0);

  init_pair(1,COLOR_WHITE,COLOR_BLUE);
}

#include "screen.c"
#include "keypress.c"

int main() {

  addStaticMessage("= T H E = D U N G O N S = O F = D O O M =");

  c_init();

  initItems();
  genMap();

  render();

  while (handleIo()) {
    render();
  }

  endwin();


  return 0;
};