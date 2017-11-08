#include "ionicGin.h"
//TODO: Asterisks to denote selections
char highlight = 94;
char numSelected = 0;
char discard = 93;
char hand = 94;
char played = 104;
int height = 0;
int width = 0;
bool drawing = true;
int roundNum = 0;
bool incorrect = false;

void mvLeft();
void mvRight();

int main(int argc, const char ** argv) {
    int c = 0;
    time_t t;
    srand((unsigned) time(&t));
    initscr();
    width = getmaxx(stdscr);
    height = getmaxy(stdscr) - (getmaxy(stdscr) % 2);
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    /*start_color();
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    bkgd(' ' | COLOR_PAIR(4));*/
    initDeck();
    printLines();
    drawDeck();
    printDiscard();
    printHand();
    printIons();
    //char listt[] = {16, 16, 2, 3, 4, 5, 17, 14, 16, 14, 17, 19, 3, 22, 21, 0, 1};
    //int listSize = 17;
    //printList(10, 2, 6, listSize, 2, listt, 0);
    while ((c = getch()) != 'q') {
        switch (c) {
            case KEY_UP:
                highlight = (highlight == discard - 1 ? discard - 1 : highlight - 1); break;
            case KEY_DOWN:
                highlight = (++highlight == played ? played - 1 : highlight); break;
            case KEY_LEFT:
                mvLeft(); break;
            case KEY_RIGHT:
                mvRight(); break;
            
            case KEY_RESIZE:
                width = getmaxx(stdscr);
                height = getmaxy(stdscr) - (getmaxy(stdscr) % 2);
                erase();
                printLines();
                refresh();                
                break;
            case ' ':
                if (highlight == discard - 1) {
                    if (drawing) {
                        drawCard();
                        drawing = false;
                    }
                } else if (highlight < hand) {
                    if (drawing) {
                        dumpsterDive(highlight + 1);
                        erase();
                        printLines();
                        refresh();
                        drawing = false;
                    }
                } else if (highlight < played) {
                    if (!drawing) {
                        selectFromHand();
                    }
                }
                break;
            case 'c':
                if (!drawing) {
                    combineSelected();
                    erase();
                    printLines();
                    refresh();
                }
                break;
            case 'd':
                discardSel();
                break;
            default: continue;
        }
        //mvprintw(15, 0, "%d, %d, %d", discard, highlight, hand);
        drawDeck();
        printDiscard();
        printHand();
        printIons();
    }
    endwin();
}

void mvLeft() {
    if (highlight < hand) {
        if (highlight < (discard + ((height/2) - 2))) {
            highlight = discard - 1;
        } else {
            highlight -= ((height/2) - 2);
        }
    } else if (highlight < hand + ((height/2 - height % 4)/2)) {
        highlight = hand - 1;
    } else {
        highlight -= ((height/2 - height % 4)/2);
    }
}

void mvRight() {
    if (highlight == discard - 1) {
        highlight = discard;
    } else if (highlight < (discard + ((height/2) - 2)) && (discard + ((height/2) - 2)) < hand) {
        mvprintw(17, 0, "%d, %d, %d", hand, played, highlight);
        if (highlight + ((height/2) - 2) >= hand) {
            highlight = hand - 1;
        } else {
            highlight += ((height/2) - 2);
        }
    } else if (highlight < hand && hand < played) {
        //mvprintw(18, 0, "THREE");
        highlight = hand;
    } else if (highlight >= hand) {
        //mvprintw(18, 0, "FOUR");        
        highlight = (highlight + ((height/2 - height % 4)/2) < played ? highlight + ((height/2 - height % 4)/2) : played - 1);
    }
}