#include "ionicGin.h"

void drawHorLine(int x, int y, int length) {
    for (int i = 0; i < length; i++) {
        mvaddch(y, x + i, ACS_HLINE);
    }
}

void drawVertLine(int x, int y, int pHeight) {
    for (int i = 0; i < pHeight; i++) {
        mvaddch(y + i, x, ACS_VLINE);
    }
}

void printDiscard() {
    int y = 1;
    int x = 10;
    int cols = 2;
    int rows = height/2 - 2;
    int pHeight = height - 3;
    int discardHighlight = (highlight >= hand ? -1 : highlight) ;
    for (int i = discard; (y < pHeight && i < hand); i++) {
        if (discardHighlight == i) {
            attrset(COLOR_PAIR(1));
            mvprintw(++y, x, getLatin(deck[i]));
            mvprintw(++y, x, getEnglish(deck[i]));
            attrset(COLOR_PAIR(0));
        } else if (discardHighlight > i) {
            attrset(COLOR_PAIR(2));
            mvprintw(++y, x, getLatin(deck[i]));
            attrset(COLOR_PAIR(0));
        } else {
            mvprintw(++y, x, getLatin(deck[i]));
        }
        if (y != pHeight) {
            drawHorLine(x, ++y, 12);
        }
        if (y == pHeight) {
            cols--;
            if (cols == 0) {
                break;
            }
            if (cols == 1 && discardHighlight > (i + rows)) {
                i = discardHighlight - rows;
            }
            x += 15;
            y = 1;
        }
    }
    mvprintw(++y, x, "            ");
}

void printHand() {
    int y = (height/2);
    int x = 40;
    int cols = (width - x - 1) / 15;
    int rows = (height/2 - height % 4)/2 - 1;
    int pHeight = height - 2 - ((height/2)%2);
    int handHighlight = (highlight >= played ? 0 : highlight) ;
    for (int i = hand; (y < pHeight && i < played); i++) {
        if (handHighlight == i) {
            attrset(COLOR_PAIR(1));
            mvprintw(++y, x, getLatin(deck[i]));
            mvprintw(++y, x, getEnglish(deck[i]));
            attrset(COLOR_PAIR(0));
        } else {
            mvprintw(++y, x, getLatin(deck[i]));
        }
        if (y != pHeight) {
            drawHorLine(x, ++y, 12);
        }
        if (y == pHeight) {
            cols--;
            if (cols == 0) {
                break;
            }
            if (cols == 1 && handHighlight > (i + rows)) {
                i = handHighlight - rows;
            }
            x += 15;
            y = (height/2);
            drawVertLine(x - 2, y + 1, height);
        }
    }
    mvprintw(++y, x, "            ");
}

void printLines() {
    mvprintw(0, 20, "Discard");
    drawHorLine(9, 1, 29);
    drawVertLine(8, 0, height);
    drawVertLine(23, 2, height - 3);
    drawVertLine(38, 0, height);
    drawVertLine(39, 0, height);
    drawHorLine(40, (height/2) - 1, width); 
    drawHorLine(40, height/2, width);
}

void drawDeck() {
    mvprintw(0, 0, "  Draw  ");
    attrset(COLOR_PAIR(highlight == discard - 1 ? 1: 0));
    mvprintw(1, 1, "      ");
    mvprintw(2, 1, "      ");
    mvprintw(3, 1, "      ");
    mvprintw(4, 1, "      ");
    mvprintw(5, 1, "      ");
    mvaddch(1, 1, ACS_BSSB);
    mvaddch(5, 1, ACS_SSBB);
    mvaddch(1, 6, ACS_BBSS);
    mvaddch(5, 6, ACS_SBBS);
    drawHorLine(2, 1, 4);
    drawHorLine(2, 5, 4);
    drawVertLine(1, 2, 3);
    drawVertLine(6, 2, 3);
    attrset(COLOR_PAIR(0));
}

/*void printList(int x, int y, int rows, int count, int cols, char * list, char highlight) {
    int pHeight = (rows * 2) + 1;
    int initialY = --y;
    for (int i = 0; (y < pHeight && i < count); i++) {
        if (highlight == i) {
            attrset(COLOR_PAIR(1));
            mvprintw(++y, x, getLatin(list[i]));
            mvprintw(++y, x, getEnglish(list[i]));
            attrset(COLOR_PAIR(0));
        } else {
            mvprintw(++y, x, getLatin(list[i]));
        }
        if (y != pHeight) {
            drawHorLine(x, ++y, 12);
        }
        if (y == pHeight) {
            cols--;
            if (cols == 0) {return;}
            if (cols == 1 && highlight > (i + rows)) {
                i = highlight - rows;
            }
            x += 15;
            y = initialY;
        }
    }
}*/
