#include"../headers/loading.hpp"

void readAP(char** argv, vector<vector<double>>& c, 
vector<vector<double>>& T, int& n, int& p, 
double& alpha, double& gama, double& delta)
{
	ifstream input(argv[1]);
	input >> n >> p >> alpha >> gama >> delta;
	vector<double> x(n);
	vector<double> y(n);
	for (int i = 0; i < n; i++) {
		input >> x[i] >> y[i];
	}
	c.resize(n);
	for (int i = 0; i < n; i++) {
		c[i].resize(n);
		for (int j = 0; j < n; j++) {
			double xSquare = (x[i] - x[j]) * (x[i] - x[j]);
			double ySquare = (y[i] - y[j]) * (y[i] - y[j]);
			c[i][j] = sqrt(xSquare + ySquare)/1000;
		}
	}
	T.resize(n);
	for (int i = 0; i < n; i++) {
		T[i].resize(n);
		for (int j = 0; j < n; j++) {
			input >> T[i][j];
		}
	}
	input.close();

}
void readCAB(char** argv, vector<vector<double>>& c, vector<vector<double>>& T, int& n, int& p, double& alpha, double& gama, double& delta)
{
	ifstream input(argv[1]);
	input >> n >> p >> alpha >> gama >> delta;
	T.resize(n);

    double sum_T = 0.0;
	for (int i = 0; i < n; i++) {
		T[i].resize(n);
		for (int j = 0; j < n; j++) {
			input >> T[i][j];
            sum_T += T[i][j];
		}
	}

    for(int i = 0; i<n; i++){
        for(int j=0; j<n; j++){
            T[i][j] /= sum_T;
        }
    }
	c.resize(n);
	for (int i = 0; i < n; i++) {
		c[i].resize(n);
		for (int j = 0; j < n; j++) {
			input >> c[i][j];
		}
	}
	input.close();
}
