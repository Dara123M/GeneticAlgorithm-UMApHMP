#ifndef __GENETIC_HPP__
#define __GENETIC_HPP__ 1

#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;


class Chromosome {

public:

    Chromosome(int n, int p, 
    double alpha, double gama, 
    double delta);

    Chromosome(){}

    
    void print();
    
    bool operator ==(Chromosome const &c2);
    
    void calculate_fitness(vector<vector<double>>& c, vector<vector<double>> &w);

    double fitness();

    vector<int> code() const;

    void floyd_warshall(vector<vector<double>>& dist);
    void form_graph(vector<vector<double>> &c, vector<vector<double>>& w, vector<vector<double>>& dist);

    int sum(vector<int> code);

    ~Chromosome();
    int get_n() const;
    int get_p() const;
    double get_alpha() const;
    double get_gama() const;
    double get_delta() const;
   
    void set_new_code(vector<int> code, int n, int p, double alpha, double gama, double delta);
    void mutate(vector<int> indexes);
    void mutateD();
    void make_first_code();
    void set_fitness(double fitness);
    

private:
    vector<int> m_code;
    int m_n, m_p;
    double m_alpha, m_gama, m_delta, m_fitness;
};


#endif