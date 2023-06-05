#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__ 1
#include<vector>
#include<memory>
#include"gen.hpp"

using namespace std;

/*population functions*/
void createPopulation(int num_unit, vector<unique_ptr<Chromosome>>& population, int n, int p, double alpha, double gama, double delta);
void calculateFitness(vector<unique_ptr<Chromosome>> &population, vector<vector<double>>& c, vector<vector<double>>& w);
void printPopulation(vector<unique_ptr<Chromosome>> &population, int index);
void reproduce(vector<unique_ptr<Chromosome>>& population, vector<unique_ptr<Chromosome>>& new_population, int elite_size, int n, int p, double alpha, double gama, double delta, float f, int k1, int k2, vector<int> &indexes_frozen);
void crossover(Chromosome parent1, Chromosome* parent2, vector<int>& child1, vector<int>& child2, int n);
vector<int> find_frozen_bits(vector<unique_ptr<Chromosome>> &population, int n);
int selection(vector<unique_ptr<Chromosome>>& population, int f, int except);
void removeDuplicates(vector<unique_ptr<Chromosome>>& population);

/*shuffle function*/
template<class RandomIterator>

RandomIterator random_unique(RandomIterator begin, RandomIterator end, size_t num_random);
 
 
/*local search*/
void localSearch(unique_ptr<Chromosome> &current, int num_iterations, vector<vector<double>> &c, vector<vector<double>> &w);



#endif