#include "main.h"

bool handleIo() {
  switch (getch()) {
    case 'Q': //quit
      return !askYN("Realy quit? [Y/N]:");
    case '.': //do nothing
      break;
    case 0x12: //reset curses
      endwin();
      c_init();
      initscr();
      break;
    case '1':
      genItem(&map[playerX][playerY].items);
      break;
    case '2':
      addStaticMessage("0");
      addStaticMessage("1");
      addStaticMessage("2");
      addStaticMessage("3");
    break;

    case KEY_UP:    movePlayer(0,-1); break;
    case KEY_DOWN:  movePlayer(0, 1); break;
    case KEY_LEFT:  movePlayer(-1,0); break;
    case KEY_RIGHT: movePlayer(1, 0); break;

    case 'i':
      printInv();
      break;

    case 'd':
      drop();
      break;

    default: //error
      addStaticMessage("Unrecognized Command.");
      break;
  }
  return 1;
}