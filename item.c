#pragma once

#include <string.h>

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
    {"shord ",encodeTag(ITEM_HAS_QAL),                              4},
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

Item unlinkI(Item* d) {
    Item self = *d;
    *d = (*d)->next;
    self -> next = NULL;
    return self;
}

void rmItem(Item* d) { //unlink a item
    free(unlinkI(d));
}

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

char* getName(Item d) {
    char* self = malloc(strlen(d->color) + strlen(d->qality) + strlen(item_types[d->type].name) + 1);
    if (tagGet(item_types[d->type],ITEM_HAS_COLOR))
        if(tagGet(item_types[d->type],ITEM_HAS_QAL))
            sprintf(self,"%s%s%s",d->color,d->qality,item_types[d->type].name);
        else
            sprintf(self,"%s%s",d->color,item_types[d->type].name);
    else
        if (tagGet(item_types[d->type],ITEM_HAS_QAL))
            sprintf(self,"%s%s",d->qality,item_types[d->type].name);
        else
            sprintf(self,"%s",item_types[d->type].name);
    return self;
}

void drawItem(Item what) {
    if (what)  //if exists draw
        addch(TEXTURE_ITEM);
}

