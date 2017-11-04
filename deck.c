#include "ionicGin.h"

static const char * NAMES[46] = {
    "Hydrogen    ", "            ", //Begin I (0)
    "Lithium     ", "            ", 
    "Sodium      ", "            ", 
    "Potassium   ", "            ", 
    "Silver      ", "            ", 
    "Calcium     ", "            ", //Begin II (5)
    "Magnesium   ", "            ", 
    "Strontium   ", "            ", 
    "Manganese   ", "            ", 
    "Mercurous   ", "Mercury (I) ", 
    "Mercuric    ", "Mercury (II)", 
    "Ferrous     ", "Iron (II)   ", 
    "Cobaltous   ", "Cobalt (II) ", 
    "Cuprous     ", "Copper (II) ", 
    "Stannous    ", "Tin (II)    ",
    "Zinc        ", "            ",
    "Ferric      ", "Iron (III)  ", //Begin III (16)
    "Cobaltic    ", "Cobalt (III)", 
    "Cupric      ", "Copper (III)", 
    "Plumbous    ", "Lead (III)  ",
    "Aluminum    ", "            ",
    "Stannic     ", "Tin (IV)    ", //Begin IV (21)
    "Plumbic     ", "Lead (IV)   "
};



char deck[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12, 1, 2, 3, 4, 5, 6, 7, 9, 0, 4, 7, 7, 3, 6, 3, 6, 7, 9, 4, 8, 15, 16, 17, 18, 19, 20, 21, 22
};

char ** initDeck() {
    return NAMES;
}

char getCharge(char card) {
    if (card < 5) {
        return 1;
    } else if (card < 16) {
        return 2;
    } else if (card < 21) {
        return 3;
    } else if (card < 23) {
        return 4;
    } else {
        return 0;
    }
}

char * getLatin(char card) {
    return NAMES[card * 2];
}

char * getEnglish(char card) {
    return NAMES[(card * 2) + 1];
}

void drawCard() {
    if (discard > 0) {
        char temp = deck[0];
        for (int i = 0; i < hand - 1; i++) {
            deck[i] = deck[i+1];
        }
        deck[hand - 1] = temp;
        discard--;
        hand--;
        highlight--;
    }
}

void dumpsterDive(int deepness) {
    char * cards = malloc(sizeof(char) * (deepness - discard));
    for (int i = discard; i < deepness; i++) {
        cards[i - discard] = deck[i];
    }
    for (int i = 0; i < (hand - deepness); i++) {
        deck[discard + i] = deck[deepness + i];
    }
    hand -= (deepness - discard);
    for (int i = 0; i < (deepness - discard); i++) {
        deck[hand + i] = cards[i];
    }
    highlight = highlight - discard + hand;
}




/*
char getCharge(char card) {
    return (card & BMASK_CHARGE) >> 6;
}

char * getName(char card) {
    return NAMES[(card & BMASK_NAMEINDEX)];
}*/