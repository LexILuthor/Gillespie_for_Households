//
// Created by popcorn on 01/01/2021.
//

#ifndef GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H
#define GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H

#endif //GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H


void initializeSEIRandTemp(std::vector <std::vector<int>> &SEIR, std::vector<double> &temp, int &N);

void new_Exposed(std::vector <std::vector<int>> &SEIR, int &j);

void new_Infected(std::vector <std::vector<int>> &SEIR, int &j);

void new_Recovered(std::vector <std::vector<int>> &SEIR, int &j);