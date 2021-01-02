//
// Created by popcorn on 01/01/2021.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "myFunctions.h"


void new_Exposed_outside_the_household(std::vector<std::vector<int> > &SEIR,
                                       std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                                       int &sumsHiH, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1] - 1);
    SEIR[1].push_back(SEIR[1][j - 1] + 1);
    SEIR[2].push_back(SEIR[2][j - 1]);
    SEIR[3].push_back(SEIR[3][j - 1]);

    //update households with susceptible based only on how many susceptible an house has
    //update also sumsHiH
    // generate a random number and decide which household will change
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, SEIR[0][j - 1]);

    double randomUnif = distribution(generator);
    int prec[3] = {0, 0, 0};
    int size = household_with_Susceptible_Infected_Exposed[0].size();
    int cumulativeSum = 0;

    for (int e = 0; e < size; e++) {

        for (int i = 0; i < size - e; i++) {

            for (int s = 0; s < size - (e + i); s++) {
                if (randomUnif <= cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * s) &&
                    randomUnif > cumulativeSum) {
                    //allora abbiamo estratto il numero (prec[0], prec[1],prec[2])
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1]][prec[2]]--;
                    household_with_Susceptible_Infected_Exposed[prec[0] - 1][prec[1]][prec[2] + 1]++;

                    // this is the rewrite of:
                    // sumsHiH = sumsHiH - (prec[0] * prec[1]) + ((prec[0] - 1) * prec[1] )
                    sumsHiH = sumsHiH - prec[1];
                    goto skip;

                }
                cumulativeSum = cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * s);
                prec[0] = s;
                prec[1] = i;
                prec[2] = e;
            }
        }
    }
    skip:;
}


void new_exposed_inside_the_household(std::vector<std::vector<int>> &SEIR,
                                      std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                                      int &sumsHiH, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1] - 1);
    SEIR[1].push_back(SEIR[1][j - 1] + 1);
    SEIR[2].push_back(SEIR[2][j - 1]);
    SEIR[3].push_back(SEIR[3][j - 1]);

    //update households with susceptible based on how many susceptible and infected an house has
    //update also sumsHiH
    // generate a random number and decide which household will change
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, sumsHiH);

    double randomUnif = distribution(generator);
    int prec[3] = {0, 0, 0};
    int size = household_with_Susceptible_Infected_Exposed[0].size();
    int cumulativeSum = 0;

    for (int e = 0; e < size; e++) {

        for (int i = 0; i < size - e; i++) {

            for (int s = 0; s < size - (e + i); s++) {

                if (randomUnif <=
                    cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * s * i) &&
                    randomUnif > cumulativeSum) {

                    //allora abbiamo estratto il numero (prec[0], prec[1],prec[2])
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1]][prec[2]]--;
                    household_with_Susceptible_Infected_Exposed[prec[0] - 1][prec[1]][prec[2] + 1]++;

                    // this is the rewrite of:
                    // sumsHiH = sumsHiH - (prec[0] * prec[1]) + ((prec[0] - 1) * prec[1] )
                    sumsHiH = sumsHiH - prec[1];
                    goto skip;

                }
                cumulativeSum = cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * s * i);
                prec[0] = s;
                prec[1] = i;
                prec[2] = e;
            }
        }
    }
    skip:;
}

void new_Infected(std::vector<std::vector<int> > &SEIR,
                  std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                  int &sumsHiH, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1]);
    SEIR[1].push_back(SEIR[1][j - 1] - 1);
    SEIR[2].push_back(SEIR[2][j - 1] + 1);
    SEIR[3].push_back(SEIR[3][j - 1]);

    //update households with susceptible based only on how many exposed an house has
    //update also sumsHiH
    // generate a random number and decide which household will change
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, SEIR[1][j - 1]);

    double randomUnif = distribution(generator);
    int prec[3] = {0, 0, 0};
    int size = household_with_Susceptible_Infected_Exposed[0].size();
    int cumulativeSum = 0;

    for (int e = 0; e < size; e++) {

        for (int i = 0; i < size - e; i++) {

            for (int s = 0; s < size - (e + i); s++) {
                if (randomUnif <= cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * e) &&
                    randomUnif > cumulativeSum) {
                    //allora abbiamo estratto il numero (prec[0], prec[1],prec[2])
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1]][prec[2]]--;
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1] + 1][prec[2] - 1]++;

                    // this is the rewrite of:
                    // sumsHiH = sumsHiH - (prec[0] * prec[1]) + (prec[0] * (prec[1]+1) )
                    sumsHiH = sumsHiH - prec[0];
                    goto skip;

                }
                cumulativeSum = cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * e);
                prec[0] = s;
                prec[1] = i;
                prec[2] = e;
            }
        }
    }
    skip:;
}

void new_Recovered(std::vector<std::vector<int> > &SEIR,
                   std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
                   int &sumsHiH, int &j) {
    SEIR[0].push_back(SEIR[0][j - 1]);
    SEIR[1].push_back(SEIR[1][j - 1]);
    SEIR[2].push_back(SEIR[2][j - 1] - 1);
    SEIR[3].push_back(SEIR[3][j - 1] + 1);

    //update households with susceptible based only on how many infected an house has
    //update also sumsHiH
    // generate a random number and decide which household will change
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, SEIR[2][j - 1]);

    double randomUnif = distribution(generator);
    int prec[3] = {0, 0, 0};
    int size = household_with_Susceptible_Infected_Exposed[0].size();
    int cumulativeSum = 0;

    for (int e = 0; e < size; e++) {

        for (int i = 0; i < size - e; i++) {

            for (int s = 0; s < size - (e + i); s++) {
                if (randomUnif <= cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * i) &&
                    randomUnif > cumulativeSum) {
                    //allora abbiamo estratto il numero (prec[0], prec[1],prec[2])
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1]][prec[2]]--;
                    household_with_Susceptible_Infected_Exposed[prec[0]][prec[1] - 1][prec[2]]++;

                    // this is the rewrite of:
                    // sumsHiH = sumsHiH - (prec[0] * prec[1]) + (prec[0] * (prec[1]-1) )
                    sumsHiH = sumsHiH + prec[0];
                    goto skip;

                }
                cumulativeSum = cumulativeSum + (household_with_Susceptible_Infected_Exposed[s][i][e] * i);
                prec[0] = s;
                prec[1] = i;
                prec[2] = e;
            }
        }
    }
    skip:;

}


void initializeSEIRandTemp(std::vector<std::vector<int> > &SEIR, std::vector<double> &temp, int &N) {
    SEIR[0][0] = N - 1;
    SEIR[1][0] = 0;
    SEIR[2][0] = 1;
    SEIR[3][0] = 0;
    temp.push_back(0);

}

void read_Parameters_From_File(std::string inputpath, int &nSteps, int &number_of_Households,
                               int &number_of_people_in_one_Household, double &beta, double &betaH, double &ny,
                               double &gamma) {

    std::string line;
    std::ifstream infile(inputpath);
    if (infile.is_open()) {

        //number of steps
        getline(infile, line, ':');
        getline(infile, line);
        nSteps = std::stoi(line);

        //number of Households
        getline(infile, line, ':');
        getline(infile, line);
        number_of_Households = std::stoi(line);

        // number of people in one Household
        getline(infile, line, ':');
        getline(infile, line);
        number_of_people_in_one_Household = std::stoi(line);


        //beta
        getline(infile, line, ':');
        getline(infile, line);
        beta = std::stod(line);

        //betaH
        getline(infile, line, ':');
        getline(infile, line);
        betaH = std::stod(line);


        //ny
        getline(infile, line, ':');
        getline(infile, line);
        ny = std::stod(line);


        //gamma
        getline(infile, line, ':');
        getline(infile, line);
        gamma = std::stod(line);

        infile.close();
    } else std::cout << "Unable to open file";
}

void write_the_csv_file(std::string outputpath, std::vector<std::vector<int> > &SEIR, std::vector<double> &temp) {
    std::ofstream outfile(outputpath);
    if (!outfile.is_open()) {
        std::cout << "Unable to open file";
    } else {
        for (int i = 0; i < temp.size(); i++) {

            outfile << SEIR[0][i] << ",\t" << SEIR[1][i] << ",\t" << SEIR[2][i] << ",\t" << SEIR[3][i] << ",\t"
                    << temp[i] << "\n";
        }
        outfile.close();
    }
}

void initialize_household_with_Susceptible_Infected_Exposed(
        std::vector<std::vector<std::vector<int>>> &household_with_Susceptible_Infected_Exposed,
        int number_of_Households, int number_of_people_in_one_Household) {
    household_with_Susceptible_Infected_Exposed[number_of_people_in_one_Household][0][0] = number_of_Households - 1;
    household_with_Susceptible_Infected_Exposed[number_of_people_in_one_Household - 1][1][0] = 1;
}