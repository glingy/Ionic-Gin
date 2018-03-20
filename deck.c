#include "ionicGin.h"

static char * NAMES[106] = {
    "Hydrogen    ", "            ", //Begin I (0)
    "Ammonium    ", "            ",
    "Cuprous     ", "Copper (I)  ", 
    "Lithium     ", "            ", 
    "Potassium   ", "            ", 
    "Silver      ", "            ", 
    "Sodium      ", "            ", 
    "Calcium     ", "            ", //Begin II (7)
    "Cobaltous   ", "Cobalt (II) ", 
    "Cupric      ", "Copper (II) ",
    "Ferrous     ", "Iron (II)   ", 
    "Mercuric    ", "Mercury (II)", 
    "Mercurous   ", "Mercury (I) ", 
    "Magnesium   ", "            ", 
    "Plumbous    ", "Lead (II)   ",
    "Stannous    ", "Tin (II)    ",
    "Strontium   ", "            ", 
    "Zinc        ", "            ",
    "Auric       ", "Gold (III)  ", //Begin III (18)
    "Aluminum    ", "            ",
    "Chromic     ", "Chromium III",
    "Cobaltic    ", "Cobalt (III)", 
    "Ferric      ", "Iron (III)  ", 
    "Plumbic     ", "Lead (IV)   ", //Begin IV (23)
    "Stannic     ", "Tin (IV)    ", 
    "Acetate     ", "            ", //Begin -1 (25)
    "Bicarbonate ", "            ",
    "Bromide     ", "            ",
    "Chlorate    ", "            ",
    "Chloride    ", "            ",
    "Cyanide     ", "            ",
    "Fluoride    ", "            ",
    "Hydride     ", "            ", 
    "Hydroxide   ", "            ",
    "Permanganate", "            ",
    "Iodate      ", "            ",
    "Iodide      ", "            ",
    "Nitrate     ", "            ",
    "Nitrite     ", "            ",
    "Perchlorate ", "            ",
    "Carbonate   ", "            ", // -2 (40)
    "Chromate    ", "            ",
    "Dichromate  ", "            ",
    "Oxide       ", "            ",
    "Peroxide    ", "            ",
    "Sulfide     ", "            ",
    "Sulfite     ", "            ",
    "Sulfate     ", "            ",
    "Thiosulfate ", "            ",
    "Arsenate    ", "            ", // -3 (49)
    "Nitride     ", "            ",
    "Phosphate   ", "            ",
    "Phosphide   ", "            "
};

int score = 0;
char numIons = 0;

int32_t ions[50];

char deck[] = {
    1, 1, 1, 2, 2, 2, 0, 0, 0, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6,
    7, 7, 7, 8, 9, 9, 9, 10, 10, 10, 11, 11, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17,
    18, 19, 19, 20, 21, 22, 22,
    23, 24,
    25, 26, 27, 27, 27, 28, 28, 29, 29, 29, 30, 31, 31, 31, 32, 33, 33, 33, 34, 34, 35, 36, 36, 36, 37, 37, 37, 38, 39,
    40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 45, 46, 46, 47, 47, 47, 48, 48,
    49, 49, 50, 51, 51, 52
};

void initDeck() {
    char temp = 0;
    char rand1 = 0;
    char rand2 = 0;
    for (int i = 0; i < 1000; i++) {
        rand1 = rand() % 104;
        rand2 = rand() % 104;
        temp = deck[rand1];
        deck[rand1] = deck[rand2];
        deck[rand2] = temp;
    }
}

int getCharge(char card) {
    if (card < 7) {
        return 1;
    } else if (card < 18) {
        return 2;
    } else if (card < 23) {
        return 3;
    } else if (card < 25) {
        return 4;
    } else if (card < 40) {
        return -1;
    } else if (card < 49) {
        return -2;
    } else {
        return -3;
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

void selectFromHand() {
    if (isSelected(highlight)) {
        deselect(highlight);
    } else {
        selected[numSelected++] = highlight;
    }
}

bool isSelected(char index) {
    for (int i = 0; i < numSelected; i++) {
        if (index == selected[i]) {
            return true;
        }
    }
    return false;
}

void deselect(char index) {
    for (int i = 0; i < numSelected; i++) {
        if (index == selected[i]) {
            numSelected--;
            for (int j = i; j < numSelected; j++) {
                selected[j] = selected[j + 1];
            }
        }
    }
}

void combineSelected() {
    mvprintw(16, 0, "COMBINING!");
    mvprintw(17, 0, "         ");
    int cation = 255;
    int anion = 255;
    int catMult = 1;
    int anMult = 1;
    char hydrogen = 0;
    char hMult = 0;
    int charge = 0;
    int tempScore = 0;

    for (int i = 0; i < numSelected; i++) {
        if (deck[selected[i]] == 0) {
            hydrogen++;
            tempScore++;
            hMult++;
            charge++;
        } else if (getCharge(deck[selected[i]]) > 0 && (cation == 255 || cation == deck[selected[i]])) {
            if (cation == deck[selected[i]]) {
                catMult++;
            }
            cation = deck[selected[i]];
            charge += getCharge(cation);
            tempScore += getCharge(cation);
        } else if ((anion == 255 || anion == deck[selected[i]])){
            if (anion == deck[selected[i]]) {
                anMult++;
            }
            anion = deck[selected[i]];
            charge += getCharge(anion);
            tempScore -= getCharge(anion);
        } else {
            penalize();
            return;
        }
    }

    if (cation == 255 && hydrogen == 1) {
        cation = 0;
        hydrogen = 0;
        catMult = hMult;
    }

    if (!((catMult == 1 || anMult == 1) || (!((catMult / anMult) % 1 == 0) && !((anMult / catMult) % 1 == 0)))) {
        penalize();
        return;
    }

    if (charge == 0 && cation != 255 && anion != 255 && !(cation == 0 && anion == 32)) {
        numIons++;
        if (numIons > 50) {
            mvprintw(20, 0, "You Made\nToo Many\nBonds...");
            endwin();
            exit(1);
        }
        if (hydrogen == 0) { 
            ions[numIons - 1] = ((cation << 16) | (anion << 8) | 0xFF);
        } else {
            ions[numIons - 1] = ((cation << 16) | anion);
        }
    } else {
        penalize();
        return;
    }

    score += (tempScore * catMult * anMult);

    setSelectionPlayed();
}

void penalize() {
    incorrect = true;
    score -= 6;
}

void setSelectionPlayed() {
    char numMoved = 0;
    char * cards = malloc(sizeof(char) * numSelected);
    for (int i = 0; i < numSelected; i++) {
        cards[i] = deck[selected[i]];
    }

    for (int i = hand; (i + numMoved < played); i++) {
        while (isSelected(i + numMoved)) {
            numMoved++;
            
        }
        deck[i] = deck[i + numMoved];
    }

    played -= numMoved;
    for (int i = 0; i < numMoved; i++) {
        deck[played + i] = cards[i];
    }
    numSelected = 0;

    if (highlight >= played) {
        highlight = played - 1;
    }
}

void discardSel() {
    if (!drawing) {
        char temp = deck[highlight];
        for (int i = highlight; i > discard; i--) {
            deck[i] = deck[i - 1];
        }
        deck[discard] = temp;
        hand++;
        numSelected = 0;
        highlight = discard;
        discard -= 3;
        drawing = true;
        roundNum++;
    }
}