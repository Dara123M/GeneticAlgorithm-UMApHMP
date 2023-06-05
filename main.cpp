#include"headers/population.hpp"
#include"headers/loading.hpp"
#include<string.h>
#include<iomanip>
#include<time.h>
#include<chrono>

using namespace chrono;
#define NUM_UNITS 150
#define NUM_ITERS 5000
#define NUM_ITERS_LS 50
#define ELITE_SIZE 20
#define FIRST_GROUP_SIZE 70
#define SECOND_GROUP_SIZE 60
#define TOURNAMENT_SIZE 5.6
#define MILLISECONDS 1e-3
#define INFINITY_M 1e9
#define MIN_ITERS (int(NUM_ITERS*0.3))
int main(int argc, char **argv){

     if(argc!=3){
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
    
    cout << setprecision(precision) << fixed;
   
    
    double min_fitness = INFINITY_M;
    int counter = 0;
    vector<int> indexes_frozen;
    int i=0;
    auto start = high_resolution_clock::now();
    createPopulation(NUM_UNITS, population, n, p, alpha, gama, delta);

    for(; i<NUM_ITERS; i++){
        calculateFitness(population, c, T);
        printPopulation(population, i);

        indexes_frozen = find_frozen_bits(population, n);
        reproduce(population, new_population, ELITE_SIZE, n, p, alpha, gama, delta, TOURNAMENT_SIZE, FIRST_GROUP_SIZE, SECOND_GROUP_SIZE, indexes_frozen);
        for(int i =0; i<NUM_UNITS; i++){
            population[i] = move(new_population[i]);
        }
        removeDuplicates(population);
        //localSearch(population[0], NUM_ITERS_LS, c, T);
        
        new_population.clear();  
        indexes_frozen.clear();

        if(min_fitness > population[0]->fitness()){
            counter = 0;
            min_fitness = population[0]->fitness();
        }
        counter++;

        if(counter >= MIN_ITERS)
            break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    population[0]->calculate_fitness(c, T);
    cout << "the best one" << endl;
    population[0]->print();
    fstream output(argv[2],ios_base::app);
    output << setprecision(3) << fixed;
    output << "the best one" << endl;
    output << population[0]->fitness() << endl;
    output << "iterations done: " << i+1 << " out of: "<< NUM_ITERS << endl;
    output << "iterations theshold: " << MIN_ITERS << endl;
    output << "duration (seconds): " << duration.count()*MILLISECONDS << endl << endl;
    population.clear();
    output.close();
    return 0;
}