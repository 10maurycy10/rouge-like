#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>

#define Tags TagType tags;
typedef uint64_t TagType;
#define tagGet(obj,tag) (int)(!!obj.tags & (1 << tag))
#define tagSet(obj,tag) (obj.tags = obj.tags | (1 << tag))
#define tagClear(obj,tag) (obj.tags = obj.tags & ~(1 << tag))
#define tagForce(obj,tag,val) val?tagSet(obj,tag):tagClear(obj,tag)
#define tagReset(obj) (obj.tags = 0)

void* mallocFAKE(int s) {
    void* x = malloc(s);
    if (!x) {
        printf("ERROR: out of memory!!");
        _Exit(1);
    }
    return x;
}
#define malloc mallocFAKE

#include "screen.c"
#include "keypress.c"

enum {
    TAG_TEST
};

struct Test {
  Tags
} test;

int main() {

  initscr();

  addStaticMessage("= T H E D U N G O N S O F D O O M =");

  genMap();
  render();
  while (handleIo()) {
    render();
  }


  endwin();

  return 0;
};