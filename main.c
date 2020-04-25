#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>

#include "screen.c"
#include "keypress.c"

#define Tags TagType tags;
typedef uint64_t TagType;
#define tagGet(obj,tag) (int)(!!obj.tags & (1 << tag))
#define tagSet(obj,tag) (obj.tags = obj.tags | (1 << tag))
#define tagClear(obj,tag) (obj.tags = obj.tags & ~(1 << tag))
#define tagForce(obj,tag,val) val?tagSet(obj,tag):tagClear(obj,tag)

enum {
    TAG_TEST
};

struct Test {
  Tags
} test;

int main() {

  initscr();

  addMessage(strdup("Test 1"));
  addMessage(strdup("Test 2"));

  render();

  getch();

  endwin();

  return 0;
};