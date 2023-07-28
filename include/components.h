#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "genlib.h"
#include "graphics.h"
#include "extgraph.h"

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#define savefile "savefile.txt"
#define rankfile "rankfile.txt"
#define MAX_RANK_NUM 5

void initColor();

void drawRectangle(double x, double y, double width, double height);
void drawRoundRectangle(double x, double y, double width, double height);
void drawFilledRect(double x, double y, double width, double height);

void clearScreen();


#define MAX_TEXT_LENGTH 80

typedef void (*zifuchuan)(void);

typedef struct
{
    double x, y, width, height;
    char text[MAX_TEXT_LENGTH + 1];
    zifuchuan callback;
    bool disabled;
} button;

button *createButton(double x, double y, double width, double height, char text[], zifuchuan cb);
void drawButton(button *b);
void enableButton(button *b);
void disableButton(button *b);

typedef struct link
{
    void *data;
    struct link *pre, *next;
} linkNode;

typedef linkNode *linkHead;

linkHead insNode(linkHead head, void *data);
linkHead delNode(linkHead head, linkNode *node);
linkNode *newNode();
void buttonCallBack(int x, int y, int button, int event);
void insButton(button *b);

void initrank();
void ranking(int score);

#endif
