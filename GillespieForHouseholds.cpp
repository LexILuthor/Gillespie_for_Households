//
// Created by popcorn on 01/01/2021.
//

#include <iostream>
#include <vector>
#include<cstdlib>
#include <random>
#include <time.h>
#include "myFunctions.h"
#include "GillespieForHouseholds.h"
#include <fstream>
#include <iomanip>

std::vector<std::vector<int> >
gillespie_for_Households(int nSteps, int N, int number_of_Households, int number_of_people_in_one_Household,
                         double beta1, double beta2, double threshold_above_which_one_to_two,
                         double threshold_under_which_two_to_one, double betaH, double ny, double gamma,
                         std::vector<double> &temp, std::vector<double> &time_lockdown,
                         std::default_random_engine &generator) {


    std::vector<std::vector<int> > SEIR(4, std::vector<int>(1, 0));
    double move = (double) 1 / N;

    //setting the initial conditions with N-1 susceptible 1 infected and zero exposed and recovered
    initializeSEIRandTemp(SEIR, temp, N);

    //the sum of (number of susceptible)*(number of infected) over all household
    int sumsHiH = number_of_people_in_one_Household - 1;


    //the matrix "household_with_Susceptible_Infected_Exposed" will contain in the position [s,i,e] the number of households with i susceptible people, i infected and e exposed
    std::vector<std::vector<std::vector<int>>> household_with_Susceptible_Infected_Exposed(
            number_of_people_in_one_Household + 1, std::vector<std::vector<int>>(number_of_people_in_one_Household + 1,
                                                                                 std::vector<int>(
                                                                                         number_of_people_in_one_Household +
                                                                                         1, 0)));

    //setting the initial condition of the matrix "household_with_Susceptible_Infected_Exposed"
    initialize_household_with_Susceptible_Infected_Exposed(household_with_Susceptible_Infected_Exposed,
                                                           number_of_Households, number_of_people_in_one_Household);

    double beta = beta1;

    std::exponential_distribution<double> exp_distribution(1);
    std::uniform_real_distribution<double> uniform_Real_Distribution(0.0, 1.0);



    //------------------------------------------------------------------------------------------------------------------

    //output for debugging
    std::ofstream outfile("../Output/gillespie_Household.txt");
    if (!outfile.is_open()) {
        std::cout << "Unable to open file";
    }
    outfile.precision(4);


    //------------------------------------------------------------------------------------------------------------------


    // here we simulate the process
    int j = 1;
    while (j < nSteps) {
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

        //change beta when we have 10% of the population recovered

        if (i >= (N / 100) * threshold_above_which_one_to_two && beta != beta2) {
            beta = beta2;
            std::cout << "beta decrease at time t= " << temp.back() << "\n";
            time_lockdown.push_back(temp.back());
        } else if (i < (N / 100) * threshold_under_which_two_to_one && beta != beta1) {
            beta = beta1;
            std::cout << "beta increase at time t= " << temp.back() << "\n";
            time_lockdown.push_back(temp.back());
        }


        // compute the parameter lambda of the exponential and the probabilities of
        // S->E, E->I, I->R

        double se = beta * s * i * move;
        double seH = betaH * (double) sumsHiH / (double) number_of_people_in_one_Household;
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
        double event = exp_distribution(generator);


        event = event / lambda;
        temp.push_back(temp.back() + event);


        //------------------------------------------------------------------------------------------------------------------

        //output for debugging

        if (j < 100) {
            outfile << "time: "  << temp.back() <<  ",\t \t" << "lambda: " << lambda << ",\t \t";
        }


        //------------------------------------------------------------------------------------------------------------------


        //Randomly decide which event happened
        //double tmp = (double) rand() / ((double) RAND_MAX);
        double tmp = uniform_Real_Distribution(generator);

        if (tmp < se) {
            //new Exposed from a contact outside the household
            std::vector<int> v = new_Exposed_outside_the_household(SEIR, household_with_Susceptible_Infected_Exposed,
                                                                   sumsHiH, j, generator);

            //----------------------------------------------------------------------------------------------------------

            //output for debugging

            if (j < 100) {
                outfile << "EO , household s= " << v[0] << ", e= " << v[1] << ", i= "
                        << v[2] << ",\n";
            }

            //----------------------------------------------------------------------------------------------------------

        } else if (tmp < (se + seH)) {
            //new Exposed from a contact within the household
            std::vector<int> v = new_exposed_inside_the_household(SEIR, household_with_Susceptible_Infected_Exposed,
                                                                  sumsHiH, j, generator);

            //----------------------------------------------------------------------------------------------------------

            //output for debugging

            if (j < 100) {
                outfile << "EI , household s= " << v[0] << ", e= " << v[1] << ", i= "
                        << v[2] << ",\n";
            }

            //----------------------------------------------------------------------------------------------------------
        } else if (tmp < (se + seH + ei)) {
            //new infected
            std::vector<int> v = new_Infected(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j, generator);

            //----------------------------------------------------------------------------------------------------------

            //output for debugging

            if (j < 100) {
                outfile << "IN , household s= " << v[0] << ", e= " << v[1] << ", i= "
                        << v[2] << ",\n";
            }

            //----------------------------------------------------------------------------------------------------------
        } else {
            //new Recovered
            std::vector<int> v = new_Recovered(SEIR, household_with_Susceptible_Infected_Exposed, sumsHiH, j,
                                               generator);

            //----------------------------------------------------------------------------------------------------------

            //output for debugging

            if (j < 100) {
                outfile << "RE , household s= " << v[0] << ", e= " << v[1] << ", i= "
                        << v[2] << ",\n";
            }

            //----------------------------------------------------------------------------------------------------------
        }
        j++;
    }

    //--------------------------------------------------------------------------------------------------------------

    //write debugging file

    outfile.close();


    //--------------------------------------------------------------------------------------------------------------

    return SEIR;

}