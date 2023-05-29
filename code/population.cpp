#include"../headers/population.hpp"


void createPopulation(int num_unit, vector<unique_ptr<Chromosome>>& population, int n, int p, double alpha, double gama, double delta){
    population.resize(num_unit);
    int i = 0;
    while( i<num_unit){

        population[i] = make_unique<Chromosome>(n, p, alpha, gama, delta);
        population[i]->make_first_code();
        
        i++;
        
    }

}

void calculateFitness(vector<unique_ptr<Chromosome>> &population, vector<vector<double>>& c, vector<vector<double>>& w){

    for(unsigned i = 0; i < population.size(); i++){
        population[i]->calculate_fitness(c, w);
    }
}


void printPopulation(vector<unique_ptr<Chromosome>> &population, int index){
        cout << "generation " << index << endl;
       
       if(index==0){
            auto min = min_element(population.begin(), population.end(), [](unique_ptr<Chromosome>& p1,  unique_ptr<Chromosome>& p2){
                 return p1->fitness() < p2->fitness();
            });

            (*min)->print();
        

            return;
        }
       

        population[0]->print();
        
}



void crossover(Chromosome* parent1, Chromosome* parent2, vector<int>& child1, vector<int>& child2, int n){
    for(int i=0; i<n; i++){
        child1[i] = parent1->code()[i];
        child2[i] = parent2->code()[i];    
    }
    int i = n-1, j = 0;
    while(i > j){
        while( j < n-1 && !(parent1->code()[j] == 1 && parent2->code()[j]==0)){
          
            j++;
        }
        while(i>0 && !(parent1->code()[i] == 0 && parent2->code()[i]==1)){
            
            i--;
        }
        if(i <= j)
            break;
        
        child1[j] = child2[i] = 0;
        child2[j] = child1[i] = 1;
        i--, j++;
    }  
}


int selection(vector<unique_ptr<Chromosome>>& population, int f, int except){
    vector<int> indexes;
    for(unsigned i=0; i < population.size(); i++){
        if(i != (unsigned)except)
            indexes.push_back(i);
    }
    random_unique(indexes.begin(), indexes.end(), f);
    int best_id = indexes[0];
    double best_fitness = INFINITY;
    for(int i = 0; i<f; i++){
        if(population[indexes[i]]->fitness() < best_fitness){
            best_fitness = population[indexes[i]]->fitness();
            best_id = indexes[i];
        }
    }
    return best_id;
}



void reproduce(vector<unique_ptr<Chromosome>>& population, vector<unique_ptr<Chromosome>>& new_population, int elite_size, int n, int p, double alpha, double gama, double delta, float f, int k1, int k2, vector<int> &indexes_frozen){
    
    int non_elite_size = population.size() - elite_size;


    vector<unique_ptr<Chromosome>> population_copy_to_sort(population.size());

    vector<unique_ptr<Chromosome>> elite(elite_size);

    vector<unique_ptr<Chromosome>> non_elite(non_elite_size);
    
    for(unsigned i=0; i<population.size(); i++){
        population_copy_to_sort[i] = move(population[i]);
    }
  
    sort(population_copy_to_sort.begin(), population_copy_to_sort.end(), [](unique_ptr<Chromosome> const& p1, unique_ptr<Chromosome> const& p2){ 
        return p1->fitness() < p2->fitness();
    });
    
    for(int i=0; i< elite_size; i++){
        elite[i] = move(population_copy_to_sort[i]);
    }

    for(int i=0; i<non_elite_size; i++){
        non_elite[i] = move(population_copy_to_sort[i+elite_size]);
    }
    
    population_copy_to_sort.clear();
   
    vector<unique_ptr<Chromosome>> first_group(k1), second_group(k2);

    for(int i=0; i<k1; i++){
        first_group[i] = move(non_elite[i]);
    } 
    for(int i=0; i<k2; i++)
    {
        second_group[i] = move(non_elite[i+k1]);
    }
    vector<unique_ptr<Chromosome>> new_members(non_elite_size);
  
    for(int j = 0; j< k1; j+=2){
        
        int id_p1 = selection(first_group, round(f), -1);
      

        int id_p2  = selection(first_group, round(f), id_p1);
      
        vector<int> c1(n);
        vector<int> c2(n);
        crossover(first_group[id_p1].get(), first_group[id_p2].get(), c1, c2, n);
    
        new_members[j] = make_unique<Chromosome>();
        new_members[j]->set_new_code( c1, n, p, alpha, gama, delta);
        
        new_members[j+1] = make_unique<Chromosome>();
        new_members[j+1]->set_new_code( c2, n, p, alpha, gama, delta);
        
    }

    for(int j = 0; j< k2; j+=2){
        
        int id_p1 = selection(second_group, round(f)+1, -1); 

        int id_p2 = selection(second_group, round(f)+1, id_p1);
        
        vector<int> c1(n);
        vector<int> c2(n);
        crossover(second_group[id_p1].get(), second_group[id_p2].get(), c1, c2, n);

        new_members[k1+j] = make_unique<Chromosome>();
        new_members[k1+j]->set_new_code( c1, n, p, alpha, gama, delta);
        new_members[k1+j+1] = make_unique<Chromosome>();
        new_members[k1+j+1]->set_new_code( c2, n, p, alpha, gama, delta);
     
    }

    
    for(int i=0; i<non_elite_size; i++){
        new_members[i]->mutate(indexes_frozen);
    }

    for(int i=0; i<elite_size; i++){
        new_population[i] = move(elite[i]);
    }

    for(int i=0; i<non_elite_size; i++){
        new_population[i+elite_size] = move(new_members[i]);
    }

    first_group.clear();
    second_group.clear();
    elite.clear();
    new_members.clear();
    
}

void removeDuplicates(vector<unique_ptr<Chromosome>>& population){
    for(unsigned i = 0; i<population.size(); i++ ){
        
        for(unsigned j = i+1; j < population.size(); j++){
            if(*population[i] == *population[j]){
                population[j]->mutateD();
            }
        }

    }
    
}

vector<int> find_frozen_bits(vector<unique_ptr<Chromosome>>& population, unsigned int n){
    vector<int> indexes;
    for(unsigned i = 0; i < n; i++){
        unsigned int sum = 0;
        for(unsigned i = 0; i<population.size(); i++){
            sum += population[i]->code()[i];
        }

        if(int(population.size()*0.8) > sum || int(population.size()*0.2) < sum)
            indexes.push_back(i);
    }

    return indexes;
}


template<class RandomIterator>
RandomIterator random_unique(RandomIterator begin, RandomIterator end, size_t num_random) {
    size_t left = distance(begin, end);
    while (num_random--) {
        RandomIterator r = begin;
        advance(r, rand()%left);
        swap(*begin, *r);
        ++begin;
        --left;
    }
    return begin;
}

void localSearch(unique_ptr<Chromosome> &current, int num_iterations, vector<vector<double>>& c, vector<vector<double>>& w){

    unique_ptr<Chromosome> to_change = make_unique<Chromosome>();
    to_change->set_new_code(current->code(), current->get_n(), current->get_p(), current->get_alpha(), current->get_gama(), current->get_delta());
    to_change->set_fitness(current->fitness());
    for(int i=0; i<num_iterations; i++){
        to_change->mutateD();
        to_change->calculate_fitness(c, w);

        if(to_change->fitness() < current->fitness()){
            current = move(to_change);
            to_change = make_unique<Chromosome>();
            to_change->set_new_code(current->code(), current->get_n(), current->get_p(), current->get_alpha(), current->get_gama(), current->get_delta());
            to_change->set_fitness(current->fitness());
    
        }
    }

}