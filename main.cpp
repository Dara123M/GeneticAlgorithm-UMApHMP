#include"population.hpp"
#include"loading.hpp"
#include<string.h>
#include<iomanip>
#include<time.h>

#define NUM_UNITS 150
#define NUM_ITERS 2000
#define NUM_ITERS_LS 1000
#define ELITE_SIZE 20
#define FIRST_GROUP_SIZE 70
#define SECOND_GROUP_SIZE 60
#define TOURNAMENT_SIZE 5.6
int main(int argc, char **argv){

     if(argc!=2){
        cerr << "no file"<< endl;
        exit(EXIT_FAILURE);
    }
    
    srand((unsigned)time(NULL));


    int n, p, precision = 2;
    double alpha, gama, delta;
    vector<vector<double>> c, T;
    if(strstr(argv[1], "AP")!=NULL){
        readAP(argv, c, T, n, p, alpha, gama,delta);
    }else if(strstr(argv[1], "CAB")!=NULL){
        readCAB(argv, c, T, n, p, alpha, gama, delta);
        precision = 3;
    }else{
        cerr << "bad format" << endl;
        exit(EXIT_FAILURE);
    }
    vector<unique_ptr<Chromosome>> population(NUM_UNITS), new_population(NUM_UNITS);
    
    createPopulation(NUM_UNITS, population, n, p, alpha, gama, delta);
    cout << setprecision(precision) << fixed;
   
   
   vector<int> indexes_frozen;
    for(int i=0; i<NUM_ITERS; i++){
        calculateFitness(population, c, T);
        printPopulation(population, i);

        indexes_frozen = find_frozen_bits(population, n);
        reproduce(population, new_population, ELITE_SIZE, n, p, alpha, gama, delta, TOURNAMENT_SIZE, FIRST_GROUP_SIZE, SECOND_GROUP_SIZE, indexes_frozen);
        for(int i =0; i<NUM_UNITS; i++){
            population[i] = move(new_population[i]);
        }
        removeDuplicates(population);
        localSearch(population[0], NUM_ITERS_LS, c, T);
        
        new_population.clear();  
        indexes_frozen.clear();
    }

    population[0]->calculate_fitness(c, T);
    cout << "the best one" << endl;
    population[0]->print();
    
    population.clear();
    return 0;
}