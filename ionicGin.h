#ifndef IONIC_GIN
#define IONIC_GIN

#include <curses.h>
#include <time.h>
#include <stdlib.h>

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

//#define BMASK_NAMEINDEX 0x3F
//#define BMASK_CHARGE 0xC0

char deck[104];
char highlight;
char selected[10];
char numSelected;
char discard;
char hand;
char played;
int height;
int width;

char ** initDeck();
char getCharge(char card);
char * getEnglish(char card);
char * getLatin(char card);
void drawDeck();
void printList(int x, int y, int height, int count, int cols, char * list, char highlight);
void drawVertLine(int x, int y, int height);
void drawHorLine(int x, int y, int length);
void printDiscard();
void printHand();
void printLines();
void drawCard();
void dumpsterDive(int deepness);

#endif