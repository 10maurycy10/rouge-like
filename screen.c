#include <curses.h>

typedef struct Message {
    struct Message* next;
    char* text
} Message;

Message* nextMessage = NULL;
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

void doMessages() {
  while (nextMessage) {
    move(0,1);
    printw(nextMessage->next?"%s __MORE__":"%s",nextMessage->text);
    refresh();
    free(nextMessage->text);
    if (nextMessage->next)
      while (getchar() != ' ') ;
    Message *next = nextMessage->next;
    free(nextMessage);
    nextMessage = next;
  }
  lastMessage = NULL;
}

void render() {
  doMessages();
  refresh();
}