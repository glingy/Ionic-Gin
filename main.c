#include "ionicGin.h"

char highlight = 4;
char numSelected = 0;
char discard = 5;
char hand = 20;
char played = 30;
int height = 0;
int width = 0;

int main(int argc, const char ** argv) {
    int c = 0;
    initscr();
    width = getmaxx(stdscr);
    height = getmaxy(stdscr) - (getmaxy(stdscr) % 2);
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    bkgd(' ' | COLOR_PAIR(0));
    printLines();
    drawDeck();
    printDiscard();
    printHand();
    //char listt[] = {16, 16, 2, 3, 4, 5, 17, 14, 16, 14, 17, 19, 3, 22, 21, 0, 1};
    //int listSize = 17;
    //printList(10, 2, 6, listSize, 2, listt, 0);
    while ((c = getch()) != 'q') {
        switch (c) {
            case KEY_UP:
                highlight = (highlight == discard - 1 ? discard - 1 : highlight - 1); break;
            case KEY_DOWN:
                highlight = (++highlight == played ? played - 1 : highlight); break;
            case KEY_RESIZE:
                width = getmaxx(stdscr);
                height = getmaxy(stdscr) - (getmaxy(stdscr) % 2);
                clear();
                printLines();
                refresh();                
                break;
            case ' ':
                if (highlight == discard - 1) {
                    drawCard();
                } else if (highlight < hand) {
                    dumpsterDive(highlight + 1);
                    clear();
                    printLines();
                    refresh();
                }
                break;
            default: continue;
        }
        //mvprintw(15, 0, "%d, %d, %d", discard, highlight, hand);
        drawDeck();
        printDiscard();
        printHand();
    }
    endwin();
}