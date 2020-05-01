#include <curses.h>
#include "map.c"
#include "main.h"



typedef struct Message { //message wraper
    struct Message* next;
    char* text;
} Message;

Message* nextMessage = NULL; //parts of FIFO
Message* lastMessage = NULL;

void addMessage(char* mess) { //GOTCHA: mess WILL be freed when dispalyed
  Message* self = malloc(sizeof(Message));
  self->next = NULL;
  self->text = mess;

  if (nextMessage == NULL) {
    nextMessage = self;
    lastMessage = self;
  } else {
    lastMessage->next = self;
  }
}

bool askYN(char *string) {
  attrset(COLOR_PAIR(0));
  move(0,0);
  clrtoeol();
  mvprintw(0, 0, string);
  while (1) {
    switch (getch()) {
      case 'y':
      case 'Y':
        return 1;
      case 'n':
      case 'N':
        return 0;
    }
    move(0,0);
    clrtoeol();
    mvprintw(0, 0, "Enter 'y' or 'n'.");
    getch();
    move(0,0);
    clrtoeol();
    mvprintw(0, 0, string);
  }
}

void addStaticMessage(const char* mess) {
    addMessage(strdup(mess));
}

void doMessages() {
  attrset(COLOR_PAIR(0));
  move(0,0);
  clrtoeol();
  while (nextMessage) {
    move(0,0);
    clrtoeol();
    printw(nextMessage->next?"%s __MORE__":"%s",nextMessage->text);
    free(nextMessage->text);
    refresh();
    if (nextMessage->next)
      while (getchar() != ' ') ;
    Message *next = nextMessage->next;
    free(nextMessage);
    nextMessage = next;
  }
  lastMessage = NULL;
}

int getint() {
  char in;
  int ac = 0;
  while (!((in = getch()) < '0' || in > '9')) {
    addch(in);
    ac *= 10;
    ac = in - '0';
  }
  if (in == KEY_EXIT)
    return -1;
  return ac;
}

#include "player.c"

void render() {
  doMessages();
  drawMap(playerX,playerY);
  drawPlayer(playerX,playerY);
  refresh();
}