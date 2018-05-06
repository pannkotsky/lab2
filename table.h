//
// Created by Valerii Kovalchuk on 5/6/18.
//

#ifndef LAB2_TABLE_H
#define LAB2_TABLE_H

#define TOP_LEFT "\u250c"
#define UP_RIGHT "\u2510"
#define BOTTOM_LEFT "\u2514"
#define BOTTOM_RIGHT "\u2518"
#define VERTICAL_LEFT "\u251c"
#define VERTICAL_RIGHT "\u2524"
#define HORIZONTAL_TOP "\u252c"
#define HORIZONTAL_BOTTOM "\u2534"
#define CROSS "\u253c"
#define VERTICAL "\u2502"
#define HORIZONTAL "\u2500"


void printN(const char *s, int n) {
    for (int i = 0; i < n; i++) {
        printw(s);
    }
}


void printTableTop(int n_columns, int column_sizes[]) {
    int i;
    printw(TOP_LEFT);
    for (i = 0; i < n_columns - 1; i++) {
        printN(HORIZONTAL, column_sizes[i]);
        printw(HORIZONTAL_TOP);
    }
    printN(HORIZONTAL, column_sizes[i]);
    printw(UP_RIGHT);
    printw("\n");
}


void printTableMiddle(int n_columns, int column_sizes[]) {
    int i;
    printw(VERTICAL_LEFT);
    for (i = 0; i < n_columns - 1; i++) {
        printN(HORIZONTAL, column_sizes[i]);
        printw(CROSS);
    }
    printN(HORIZONTAL, column_sizes[i]);
    printw(VERTICAL_RIGHT);
    printw("\n");
}


void printTableBottom(int n_columns, int column_sizes[]) {
    int i;
    printw(BOTTOM_LEFT);
    for (i = 0; i < n_columns - 1; i++) {
        printN(HORIZONTAL, column_sizes[i]);
        printw(HORIZONTAL_BOTTOM);
    }
    printN(HORIZONTAL, column_sizes[i]);
    printw(BOTTOM_RIGHT);
    printw("\n");
}


#endif //LAB2_TABLE_H
