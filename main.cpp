#include <iostream>
#include <vector>
#include <random>
#include <time.h>

#include "myFunctions.h"
#include "GillespieForHouseholds.h"

int main() {


    std::string inputpath = "../InputOutput/Input_Gillespie_Household.txt";
    std::string outputpath = "../InputOutput/gillespie_Household";


    //Number of steps
    int nSteps;

    // number of Households
    int number_of_Households;

    // number of people in one Household
    int number_of_people_in_one_Household;

    //S->E the initial beta
    double beta1;

    //S->E after the lockdown (automatically actived when a certain % of the population is recovered)
    double beta2;

    //the % above which the general contacts happens at ratio beta2
    double threshold_above_which_one_to_two;

    //the % under which the general contacts happens at ratio beta1
    double threshold_under_which_two_to_one;

    //S->E in the household
    double betaH;

    // E-> I
    double ny;

    // I->R
    double gamma;

    int tot_simulations = 11;

    //Here you can change the seed of the generator
    //std::default_random_engine generator(time(NULL));
    std::default_random_engine generator(0);
    //srand(time(0));
    srand(5);
    //std::default_random_engine generator;

    read_Parameters_From_File(inputpath, nSteps, number_of_Households, number_of_people_in_one_Household, beta1, beta2,
                              threshold_above_which_one_to_two, threshold_under_which_two_to_one,
                              betaH, ny, gamma);

    if (beta1 != beta2) {
        outputpath = "../InputOutput/gillespie_Household_lockdown";
    }

    int N = number_of_Households * number_of_people_in_one_Household;


    // Gillespie algorithm.
    // SEIR is a matrix that contains the data relative to the number of infected recovred etc..
    // tmp is the vector of the time (each entry is the time at which an event occurred)
    for (int i = 0; i < tot_simulations; i++) {
        std::vector<double> tempo;
        std::vector<double> time_lockdown;
        std::vector<std::vector<int> > SEIR = gillespie_for_Households(nSteps, N, number_of_Households,
                                                                       number_of_people_in_one_Household, beta1, beta2,
                                                                       threshold_above_which_one_to_two,
                                                                       threshold_under_which_two_to_one, betaH, ny,
                                                                       gamma, tempo, time_lockdown, generator);

        if (beta1 != beta2) {
            write_lock_down_files(outputpath + std::to_string(i) + "lock_down_time" + ".txt", time_lockdown);
        }
        write_the_csv_file(outputpath + std::to_string(i) + ".csv", SEIR, tempo);
        std::cout << i << "\n";
    }
    return 0;

}