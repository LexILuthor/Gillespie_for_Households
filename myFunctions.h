//
// Created by popcorn on 01/01/2021.
//

#ifndef GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H
#define GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H

#endif //GILLESPIE_FOR_HOUSEHOLDS_MYFUNCTIONS_H


void new_Exposed_outside_the_household(std::vector<std::vector<int>> &SEIR,
                                       std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                                       int &sumsHiH, int &j);

void new_exposed_inside_the_household(std::vector<std::vector<int>> &SEIR,
                                      std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                                      int &sumsHiH, int &j);

void new_Infected(std::vector<std::vector<int>> &SEIR,
                  std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                  int &sumsHiH, int &j);

void new_Recovered(std::vector<std::vector<int>> &SEIR,
                   std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                   int &sumsHiH, int &j);

void initializeSEIRandTemp(std::vector<std::vector<int>> &SEIR, std::vector<double> &temp, int &N);

void read_Parameters_From_File(std::string inputpath, int &nSteps, int &number_of_Households,
                               int &number_of_people_in_one_Household, double &beta, double &betaH, double &ny,
                               double &gamma);

void write_the_csv_file(std::string outputpath, std::vector<std::vector<int> > &SEIR, std::vector<double> &temp);

void initialize_household_with_Susceptible_Infected_Exposed(
        std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
        int number_of_Households,
        int number_of_people_in_one_Household);

double generateUnif_from_zeroExcluded_to(double to);