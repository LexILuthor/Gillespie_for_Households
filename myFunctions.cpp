//
// Created by popcorn on 01/01/2021.
//


#include <iostream>
#include <vector>
#include "myFunctions.h"


void initializeSEIRandTemp(std::vector<std::vector<int> > &SEIR, std::vector<double> &temp, int &N) {
    SEIR[0][0] = N - 1;
    SEIR[1][0] = 0;
    SEIR[2][0] = 1;
    SEIR[3][0] = 0;
    temp.push_back(0);

}

void new_Exposed(std::vector<std::vector<int> > &SEIR, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1] - 1);
    SEIR[1].push_back(SEIR[1][j - 1] + 1);
    SEIR[2].push_back(SEIR[2][j - 1]);
    SEIR[3].push_back(SEIR[3][j - 1]);
}

void new_Infected(std::vector<std::vector<int> > &SEIR, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1]);
    SEIR[1].push_back(SEIR[1][j - 1] - 1);
    SEIR[2].push_back(SEIR[2][j - 1] + 1);
    SEIR[3].push_back(SEIR[3][j - 1]);
}

void new_Recovered(std::vector<std::vector<int> > &SEIR, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1]);
    SEIR[1].push_back(SEIR[1][j - 1]);
    SEIR[2].push_back(SEIR[2][j - 1] - 1);
    SEIR[3].push_back(SEIR[3][j - 1] + 1);
}