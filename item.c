#pragma once

#define Length(a) (sizeof(a) / sizeof(a[0]))

enum {ITEM_HAS_COLOR,ITEM_HAS_QAL,};

enum {ITEM_FOOD};

struct item_type {
    const char* name;
    int tags;
    int rarity;
};

int total_rarity;
struct item_type item_types[] = {
    {"pack of food ",encodeTag(ITEM_HAS_QAL),                       20},
    {"shord ",encodeTag(ITEM_HAS_QAL),                              10},
    {"ring ",encodeTag(ITEM_HAS_QAL) | encodeTag(ITEM_HAS_COLOR),   10},
};

char* item_qalatys[] = {
    "worn ",
    "cleen ",
    "",
};

char* item_colors[] = {
    "red ",
    "blue ",
    "green ",
    "pink ",
    "purple ",
};

typedef struct Item {
    int type;
    char* color;
    char* qality;
    struct Item* next;
} *Item;

void initItems() {
    int t = 0;
    for (int x = 0; x < Length(item_types); x++) {
        t += item_types[x].rarity;
    }
    total_rarity = t;
}

void mkItem(Item* where,int type,int color,int qal) {
    Item self = malloc(sizeof(struct Item));
    self->color = item_colors[color];
    self->qality = item_qalatys[qal];
    self->type = type;
    self->next = *where;
    *where = self;
}

void printItem(Item d) {
    // {color} {qal} name
    if (tagGet(item_types[d->type],ITEM_HAS_COLOR))
        printw("%s",d->color);
    if (tagGet(item_types[d->type],ITEM_HAS_QAL))
        printw("%s",d->qality);
    printw("%s",item_types[d->type].name);
}

