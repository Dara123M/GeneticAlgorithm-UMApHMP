#include"../headers/gen.hpp"

Chromosome::Chromosome(int n, int p, double alpha,
                     double gama, double delta):m_n(n), m_p(p),
                                                 m_alpha(alpha), m_gama(gama),
                                                  m_delta(delta){
                                                    
                                                  }


void Chromosome::make_first_code(){

        this->m_code.resize(this->m_n);
        
        for(int i=0; i<this->m_n; i++){
            this->m_code[i] = 0;
        }   

        for(int i = 0; i <this->m_p; i++){
            int random_index = rand() % this->m_n;
            if(this->m_code[random_index]==1){
                i--;
            }else
                this->m_code[random_index] = 1;
        }
        
}

void Chromosome::set_new_code(vector<int> code, int n, int p, double alpha, double gama, double delta){
        
        this->m_n = n;
        this->m_p = p;
        this->m_alpha = alpha;
        this->m_delta = delta;
        this->m_gama = gama;
       
        this->m_code.resize(n);

        for(int i=0; i<this->m_n;i++){
            this->m_code[i] = code[i];
        }


      
    }


void Chromosome::form_graph(vector<vector<double>> &c, vector<vector<double>>& w, vector<vector<double>>& dist){
    dist.resize(2*this->m_n + this->m_p);

    for(int i=0; i<2*this->m_n+this->m_p; i++){
        dist[i].resize(2*this->m_n + this->m_p);
    }


    vector<int> indexes(2*this->m_n+this->m_p);

    for(int i=0; i<this->m_n; i++){
        indexes[i] = i;
    }
    for(int i=0, j = 0; i<this->m_n; i++){
        if(this->m_code[i]){
            indexes[this->m_n+j] = i;
            j++;
        }
    }

    for(int i=this->m_n+this->m_p; i<2*this->m_n+this->m_p; i++){
        indexes[i] = i-this->m_n-this->m_p;
    }


    for(int i=0; i<this->m_n; i++){
        for(int j=0; j<this->m_n; j++){
            dist[i][j] = dist[this->m_n+this->m_p+i][j] = dist[i][this->m_n+this->m_p+j] = dist[this->m_n+this->m_p+i][this->m_n+this->m_p+j] = INFINITY;                 
        }
    }

   for(int i=0; i<2*this->m_n+this->m_p; i++){
        for(int j=this->m_n; j<this->m_n+this->m_p; j++){
            dist[i][j] = c[indexes[i]][indexes[j]];
            dist[j][i] = c[indexes[j]][indexes[i]];
           
            
             if((this->m_code[indexes[i]] == 1) && (this->m_code[indexes[j]] == 1)){
                dist[i][j] *= this->m_alpha;
                dist[j][i] *= this->m_alpha;
            }else if((this->m_code[indexes[i]] == 0) && (this->m_code[indexes[j]]==1)){
                dist[i][j] *= this->m_gama;
                dist[j][i] *= this->m_delta;
            }else if(this->m_code[indexes[i]] ==0 && this->m_code[indexes[j]]== 0){
                dist[i][j] *= this->m_delta;
                dist[j][i] *= this->m_gama;
            
            } 
        }
    }

}

void  Chromosome::floyd_warshall(vector<vector<double>> &dist){
    
    for(int k = this->m_n; k <this->m_n+this->m_p; k++){
        for(int i = 0; i < this->m_n+this->m_p; i++){
            for(int j = 0; j < this->m_n+this->m_p; j++){
                if(dist[i][k]==INFINITY || dist[k][j]==INFINITY)
                    continue;
                if(dist[i][j] > dist[i][k]+dist[k][j] ){
                    
                    dist[i][j] = dist[i][k] + dist[k][j];

                }
            }
        }
        
    }
    

}
bool Chromosome::operator ==(Chromosome const &c2){
        bool ind = true;

        for(int i=0; i<this->m_n; i++){
            ind = ind && this->m_code[i] == c2.m_code[i];
        }
        return ind;
}


void Chromosome::calculate_fitness(vector<vector<double>>& c, vector<vector<double>> &w){
    vector<vector<double>> dist;

    form_graph(c, w, dist);

    floyd_warshall(dist);

    this->m_fitness = 0.0;
    for(int i = 0; i<this->m_n; i++){
        for(int j = 0; j<this->m_n; j++){
           this->m_fitness += w[i][j]*dist[i][j];  
        }
    }

    for(unsigned i=0; i<dist.size(); i++){
        dist[i].clear();

    }

    dist.clear();
}

double Chromosome::fitness(){
    return this->m_fitness;
}


void Chromosome::mutate(vector<int>indexes){

    int i=0;
    for(; i<this->m_n ; i++){
        double random_number = (rand()%100)/100.0;
        
        double co = (find(indexes.begin(), indexes.end(), i) == indexes.end()) ? 0.4 : 1.0;

        if(random_number < co/this->m_n){
            this->m_code[i] =this->m_code[i] == 1 ? 0 : 1;
            break;
        }  
    }
     
      int p = this->sum(this->m_code);
      int bit_to_change = p < this->m_p ? 1 : 0;
      int op = p < this->m_p ? 1 : -1;
  
      while(p != this->m_p){
          int random_index = rand()%this->m_n;
          if(i == random_index || this->m_code[random_index] == bit_to_change)
              continue;
          this->m_code[random_index] = bit_to_change;
          p += op;
      }
  
   

}

void Chromosome::mutateD(){

    int random_index1 = rand()%this->m_n;
    int random_index2 = rand()%this->m_n;
    while(this->m_code[random_index1] == this->m_code[random_index2]){
        random_index2 = rand()%this->m_n;
    }
    
    this->m_code[random_index1] = this->m_code[random_index1] == 1? 0 : 1;
    this->m_code[random_index2] = this->m_code[random_index2] == 1? 0 : 1;
}

vector<int> Chromosome::code() const{
        return m_code;
}

int Chromosome::sum(vector<int> code) {
        int s = 0;
        for(int i: code)
            s+=i;
        return s;
}

void Chromosome::print(){

        for (int &c: this->m_code){
            cout << c << " ";
        }
        cout << endl;
       
        cout << this->m_fitness << endl;
        
}
Chromosome::~Chromosome(){
   this->m_code.clear();  
}
int Chromosome::get_n() const{
    return this->m_n;
}
int Chromosome::get_p() const{
    return this->m_p;
}
double Chromosome::get_alpha() const {
    return this->m_alpha;
}
double Chromosome::get_gama() const{
    return this->m_gama;
}
double Chromosome::get_delta() const{
    return this->m_delta;
}
void Chromosome::set_fitness(double fitness){
    this->m_fitness = fitness;
}






