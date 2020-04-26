bool handleIo() {
  switch (getch()) {
    case 'Q': //quit
      return !askYN("Realy quit? [Y/N]:");
    case '.': //do nothing
      break;
    case 'R': //reset curses
      endwin();
      initscr();
      break;
    case 'N':
       printw("\07");
       break;

    case KEY_UP:    movePlayer(0,-1); break;
    case KEY_DOWN:  movePlayer(0, 1); break;
    case KEY_LEFT:  movePlayer(-1,0); break;
    case KEY_RIGHT: movePlayer(1, 0); break;

    default: //error
      addStaticMessage("Unrecognized Command.");
      break;
  }
  return 1;
}