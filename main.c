#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "weightedRandom.h"

int NUMBER_OF_ROLLS = 100000000;

int ROLL_NUMBER = 0, ROLL_SINCE_LAST_4 = 0, ROLL_SINCE_LAST_5 = 0;
int choices[3] = {3, 4, 5};
int weightsNoPity[3] = {943, 51, 6};
int weightsPity4[3] = {0, 994, 6};
int weightsPity5_SOFT[3] = {625, 51, 324};
int weightsPity5_HARD[3] = {0, 0, 1000};

int pull() {
    int choice;

    ROLL_NUMBER++;
    if (ROLL_SINCE_LAST_5 == 90)
        choice = randomNum(choices, weightsPity5_HARD, 3, 1000);
    else if (ROLL_SINCE_LAST_4 == 10)
        choice = randomNum(choices, weightsPity4, 3, 1000);
    else if (ROLL_SINCE_LAST_5 >= 75)
        choice = randomNum(choices, weightsPity5_SOFT, 3, 1000);
    else
        choice = randomNum(choices, weightsNoPity, 3, 1000);

    if (choice==5) {
        ROLL_SINCE_LAST_5 = 0;
        ROLL_SINCE_LAST_4 = 0;
    }
    if (choice==4) {
        ROLL_SINCE_LAST_5++;
        ROLL_SINCE_LAST_4 = 0;
    } else {
        ROLL_SINCE_LAST_5++;
        ROLL_SINCE_LAST_4++;
    }

    return choice;
}

int main() {
    time_t t;
    // Initialising RNG
    srand((unsigned) time(&t));
    int p, n3=0, n4=0, n5=0;

    for (int i = 0; i < NUMBER_OF_ROLLS; i++) {
        p = pull();
        if (p==3) n3++;
        if (p==4) n4++;
        if (p==5) n5++;
    }
    printf("NUMBER OF ROLLS = %d\n3* PULLS = %d\n4* PULLS = %d\n5* PULLS = %d", NUMBER_OF_ROLLS, n3, n4, n5);
}
