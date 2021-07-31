#include "weightedRandom.h"
#include <stdlib.h>

int randomNum(int *choices, int *weights, int numChoices, int sumOfWeights) {
    int rnd = rand() % sumOfWeights;
    for (int i=0; i<numChoices-1; i++) {
        if (rnd < weights[i])
            return choices[i];
        rnd -= weights[i];
    }
    return choices[numChoices-1];
}
