#include <iostream>
#include <vector>
#include "myFunctions.h"
#include "GillespieForHouseholds.h"

int main() {


    std::string inputpath = "../InputOutput/Input_Gillespie_Household.txt";
    std::string outputpath = "../InputOutput/gillespie_Household.csv";


    //Number of steps
    int nSteps;

    // number of Households
    int number_of_Households;

    // number of people in one Household
    int number_of_people_in_one_Household;

    //S->E the initial beta
    double beta1;

    //S->E after the lockdown (automatically actived when 10% of the population is recovered)
    double beta2;

    //S->E in the household
    double betaH;

    // E-> I
    double ny;

    // I->R
    double gamma;


    read_Parameters_From_File(inputpath, nSteps, number_of_Households, number_of_people_in_one_Household, beta1, beta2,
                              betaH, ny, gamma);

    int N = number_of_Households * number_of_people_in_one_Household;


    // Gillespie algorithm.
    // SEIR is a matrix that contains the data relative to the number of infected recovred etc..
    // tmp is the vector of the time (each entry is the time at which an event occurred)
    std::vector<double> temp;
    std::vector<std::vector<int> > SEIR = gillespie_for_Households(nSteps, N, number_of_Households,
                                                                   number_of_people_in_one_Household, beta1,beta2, betaH, ny,
                                                                   gamma, temp);


    write_the_csv_file(outputpath, SEIR, temp);
    return 0;

}