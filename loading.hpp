#ifndef __LOADING_HPP__
#define __LOADING_HPP__ 1
#include<fstream>
#include<vector>
#include<cmath>

using namespace std;
/*loading functions*/
void readAP(char** argv, vector<vector<double>>& c, vector<vector<double>>& T, 
int& n, int& p, double& alpha, double& gama, double& delta);
void readCAB(char** argv, vector<vector<double>>& c, vector<vector<double>>& T, int& n, int& p, double& alpha, double& gama, double& delta);

#endif