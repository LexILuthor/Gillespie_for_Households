//
// Created by popcorn on 01/01/2021.
//

#include <iostream>
#include <vector>
#include<cstdlib>
#include <random>
#include "myFunctions.h"
#include "GillespieForHouseholds.h"

std::vector<std::vector<int> >
gillespie_for_Households(int nSteps, int N, int number_of_Households, int number_of_people_in_one_Household,
                         double beta, double betaH, double ny, double gamma, std::vector<double> &temp) {
    //Here you can change the seed of the generator
    std::default_random_engine generator(0);


    std::vector<std::vector<int> > SEIR(4, std::vector<int>(1, 0));
    double move = (double) 1 / N;

    //setting the initial conditions with N-1 susceptible 1 infected and zero exposed and recovered
    initializeSEIRandTemp(SEIR, temp, N);

    //the
    int sumsHiH = number_of_people_in_one_Household - 1;


    //the matrix "household_with_Susceptible_Infected_Exposed" will contain in the position (i,j) the number of households with i susceptible people and j infected people
    std::vector<std::vector<std::vector<int>>> household_with_Susceptible_Infected_Exposed(
            number_of_people_in_one_Household + 1, std::vector<std::vector<int>>(number_of_people_in_one_Household + 1,
                                                                                 std::vector<int>(
                                                                                         number_of_people_in_one_Household +
                                                                                         1, 0)));
    //setting the initial condition of the matrix "household_with_Susceptible_Infected_Exposed"
    initialize_household_with_Susceptible_Infected_Exposed(household_with_Susceptible_Infected_Exposed,
                                                           number_of_Households,
                                                           number_of_people_in_one_Household);


    // here we simulate the process
    int j = 1;
    while (j < nSteps) {
        std::cout << j << "\n";
        //number of Susceptible
        int s = SEIR[0][j - 1];

        //number of Exposed
        int e = SEIR[1][j - 1];

        //Number of Infected
        int i = SEIR[2][j - 1];

        //number of Recovered
        int r = SEIR[3][j - 1];


        if (r == N) {
            //everyone recovered
            return SEIR;
        }


        // compute the parameter lambda of the exponential and the probabilities of
        // S->E, E->I, I->R
        double se = beta * s * i * move;
        //problem here what do we divde for?
        double seH = betaH * sumsHiH / number_of_people_in_one_Household;
        double ei = ny * e;
        double ir = gamma * i;
        double lambda = (se + seH + ei + ir);
        if (lambda == 0) {
            break;
        }
        se = se / lambda;
        seH = seH / lambda;
        ei = ei / lambda;
        ir = ir / lambda;


        //generate the time of the next event with an exponential with parameter lambda
        std::exponential_distribution<double> exp_distribution(lambda);
        double event = exp_distribution(generator);
        temp.push_back(temp.back() + event);


        //Randomly decide which event happened
        double tmp = rand() / ((double) RAND_MAX + 1);
        if (tmp < se) {
            //new Exposed from a contact outside the household
            new_Exposed_outside_the_household(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j);
        } else if (tmp < (se + seH)) {
            //new Exposed from a contact within the household
            new_exposed_inside_the_household(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j);
        } else if (tmp < (se + seH + ei)) {
            //new infected
            new_Infected(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j);
        } else {
            //new Recovered
            new_Recovered(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j);
        }
        j++;
    }

    return SEIR;

}